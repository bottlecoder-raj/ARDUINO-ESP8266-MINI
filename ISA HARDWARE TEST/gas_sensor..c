#define GAS_ANALOG_PIN A5   // MQ sensor AO pin
#define GAS_DIGITAL_PIN 10   // MQ sensor DO pin (optional)

int gasValue = 0;
int gasThreshold = 400;  // Adjust after calibration

void setup() {
  Serial.begin(9600);
  
  pinMode(GAS_DIGITAL_PIN, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  Serial.println("MQ Gas Sensor Initialized...");
  Serial.println("Warming up sensor (20–30 seconds recommended)");
}

void loop() {
  digitalWrite(8, 1);
    digitalWrite(9,0);

  gasValue = analogRead(GAS_ANALOG_PIN);
  int digitalState = digitalRead(GAS_DIGITAL_PIN);

  Serial.print("Gas Analog Value: ");
  Serial.print(gasValue);

  if (gasValue > gasThreshold) {
    Serial.print("  |  GAS DETECTED!");
  }

  Serial.print("  |  Digital Output: ");
  Serial.println(digitalState == LOW ? "GAS DETECTED" : "NORMAL");

  delay(100);
}
