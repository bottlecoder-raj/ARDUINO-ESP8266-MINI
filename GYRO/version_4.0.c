#include <Wire.h>
#include <MPU6050.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "0";
const char* password = "0";
String botToken = ".".  // Your Bot Token
String chatId = ".";                                        // Your Chat ID

MPU6050 mpu;
unsigned long idleStart = 0;
unsigned long idleDuration = 0;

const float ACCEL_SENS = 16384.0;  // LSB/g
const float GYRO_SENS = 131.0;     // LSB/(°/s)

float gyroBiasX = 0, gyroBiasY = 0, gyroBiasZ = 0;
const int CAL_SAMPLES = 200;

float angleX = 0, angleY = 0, angleZ = 0;  // Orientation in degrees
unsigned long lastTime;

#define LED_PIN D4


unsigned long previousBlink = 0;
unsigned long blinkInterval = 500;  // default
bool ledState = HIGH;

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);     // SDA=D2, SCL=D1 for ESP8266
  Wire.setClock(400000);  // Fast I2C
  pinMode(LED_PIN, OUTPUT);
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);

  Serial.println("Initializing MPU6050...");
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1)
      ;
  }

  Serial.println("Calibrating gyro...");
  calibrateGyro();
  Serial.println("Calibration done.");

  lastTime = millis();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.println(WiFi.localIP());

   digitalWrite(D0, LOW);
  delay(1000);
  digitalWrite(D0, HIGH);
  delay(500);
  digitalWrite(D0, LOW);
  delay(1000);
  digitalWrite(D0, HIGH);
 
  //WIFI INITIATION..
  WiFiClientSecure client;
  client.setInsecure();  // 👈 Skip certificate validation (easy way)

  HTTPClient http;

  //....................................TELEGRAM BOT
  String url = "https://api.telegram.org/bot" + botToken + "/sendMessage?chat_id=" + chatId + "&text=Hello+from+NodeMCU";

  http.begin(client, url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.printf("HTTP Response code: %d\n", httpCode);
    Serial.println(http.getString());  // Telegram reply
  } else {
    Serial.printf("Request failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();  //TELEGRAM BOT
}

void loop() {
  int16_t ax_raw, ay_raw, az_raw, gx_raw, gy_raw, gz_raw;
  mpu.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx_raw, &gy_raw, &gz_raw);

  // Convert raw to actual units
  float ax = ax_raw / ACCEL_SENS;
  float ay = ay_raw / ACCEL_SENS;
  float az = az_raw / ACCEL_SENS;

  float gx = (gx_raw - gyroBiasX) / GYRO_SENS;  // °/s
  float gy = (gy_raw - gyroBiasY) / GYRO_SENS;
  float gz = (gz_raw - gyroBiasZ) / GYRO_SENS;

  // Time delta
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;

  // Accelerometer angles
  float accelRoll = atan2(ay, az) * 180.0 / PI;
  float accelPitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

  // Complementary filter
  const float alpha = 0.98;
  angleX = alpha * (angleX + gx * dt) + (1 - alpha) * accelRoll;
  angleY = alpha * (angleY + gy * dt) + (1 - alpha) * accelPitch;

  // Integrate gyro for yaw
  angleZ += gz * dt;

  // Print for Serial Plotter: "X:<val> Y:<val> Z:<val>"
  Serial.print("X:");
  Serial.print(angleX, 2);
  //Serial.print(" Y:"); Serial.print(angleY, 2);
  //Serial.print(" Z:"); Serial.println(angleZ, 2);

  // Blink interval based on angleX
  if (angleX < 80) {
    blinkInterval = 70;  // medium speed
    idleDuration = millis() - idleStart;
  } else {
    blinkInterval = 500;  // normal
    idleStart = millis();
  }

  //Non-blocking LED blink using millis()
  if (now - previousBlink >= blinkInterval) {
    previousBlink = now;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
  Serial.print("         Time spent idle before press: ");
  int secs = idleDuration / 1000;
  Serial.print(secs);

  // ---- Telegram Notification ----
  static unsigned long lastNotification = 0;   // store last sent time
  const unsigned long notifyInterval = 20000;  // 20 sec between messages

  unsigned long idleSecs = idleDuration / 1000;

  // If slouching for more than 10 sec AND last message was >30 sec ago
  if (idleSecs >= 10 && (now - lastNotification >= notifyInterval)) {
    WiFiClientSecure client;
    client.setInsecure();  // IMPORTANT for HTTPS

    HTTPClient http;
    String url_message = "https://api.telegram.org/bot" + botToken + "/sendMessage?chat_id=" + chatId + "&text=You+are+slouching";

    http.begin(client, url_message);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("Notification sent! HTTP %d\n", httpCode);
      Serial.println(http.getString());
    } else {
      Serial.printf("Notification failed: %s\n",
                    http.errorToString(httpCode).c_str());
    }
    http.end();

    lastNotification = now;  // update timer
  }

  Serial.println(" s");

  // No delay() here → loop runs fast for sensor updates
}

void calibrateGyro() {
  long sx = 0, sy = 0, sz = 0;
  int16_t ax, ay, az, gx, gy, gz;
  for (int i = 0; i < CAL_SAMPLES; i++) {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    sx += gx;
    sy += gy;
    sz += gz;
    delay(5);
  }
  gyroBiasX = sx / (float)CAL_SAMPLES;
  gyroBiasY = sy / (float)CAL_SAMPLES;
  gyroBiasZ = sz / (float)CAL_SAMPLES;
}
