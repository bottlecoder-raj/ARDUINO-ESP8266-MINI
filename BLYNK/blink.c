#define BLYNK_TEMPLATE_ID "TMPL3S7Xeh4RV"
#define BLYNK_TEMPLATE_NAME "BLINK"
#define BLYNK_AUTH_TOKEN "2G1mitU97VtXU69Ph8fvTwxUYF2-UT_c"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Replace with your Wi-Fi credentials
char ssid[] = "Raj_4g";
char pass[] = "55556666";

#define LED_PIN D2  // GPIO4 on NodeMCU

BlynkTimer timer;

bool ledState = false;

// This function toggles LED every second
void blinkLED() {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

  // Start Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Set timer to call blinkLED every 1000ms
  timer.setInterval(1000L, blinkLED);
}

void loop() {
  Blynk.run();     // Run Blynk
  timer.run();     // Run timer
}
