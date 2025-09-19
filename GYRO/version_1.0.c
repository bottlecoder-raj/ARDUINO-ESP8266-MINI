#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const float ACCEL_SENS = 16384.0; // LSB/g
const float GYRO_SENS = 131.0;    // LSB/(°/s)

float gyroBiasX = 0, gyroBiasY = 0, gyroBiasZ = 0;
const int CAL_SAMPLES = 200;

float angleX = 0, angleY = 0, angleZ = 0; // Orientation in degrees
unsigned long lastTime;

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);    // SDA=D2, SCL=D1 for ESP8266
  Wire.setClock(400000); // Fast I2C

  Serial.println("Initializing MPU6050...");
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  Serial.println("Calibrating gyro...");
  calibrateGyro();
  Serial.println("Calibration done.");

  lastTime = millis();
}

void loop() {
  int16_t ax_raw, ay_raw, az_raw, gx_raw, gy_raw, gz_raw;
  mpu.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx_raw, &gy_raw, &gz_raw);

  // Convert raw to actual units
  float ax = ax_raw / ACCEL_SENS;
  float ay = ay_raw / ACCEL_SENS;
  float az = az_raw / ACCEL_SENS;

  float gx = (gx_raw - gyroBiasX) / GYRO_SENS; // °/s
  float gy = (gy_raw - gyroBiasY) / GYRO_SENS;
  float gz = (gz_raw - gyroBiasZ) / GYRO_SENS;

  // Time delta
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;

  // Accelerometer angles
  float accelRoll  = atan2(ay, az) * 180.0 / PI;
  float accelPitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

  // Complementary filter
  const float alpha = 0.98;
  angleX = alpha * (angleX + gx * dt) + (1 - alpha) * accelRoll;
  angleY = alpha * (angleY + gy * dt) + (1 - alpha) * accelPitch;

  // Integrate gyro for yaw
  angleZ += gz * dt;

  // Print for Serial Plotter: "X:<val> Y:<val> Z:<val>"
  Serial.print("X:"); Serial.print(angleX, 2);
  Serial.print(" Y:"); Serial.print(angleY, 2);
  Serial.print(" Z:"); Serial.println(angleZ, 2);

  delay(20); // ~50Hz
}

void calibrateGyro() {
  long sx = 0, sy = 0, sz = 0;
  int16_t ax, ay, az, gx, gy, gz;
  for (int i = 0; i < CAL_SAMPLES; i++) {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    sx += gx; sy += gy; sz += gz;
    delay(5);
  }
  gyroBiasX = sx / (float)CAL_SAMPLES;
  gyroBiasY = sy / (float)CAL_SAMPLES;
  gyroBiasZ = sz / (float)CAL_SAMPLES;
}
