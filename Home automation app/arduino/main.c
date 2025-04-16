char val;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  if (Serial.available() != 0)  //if communication is going on
  {
    char val = Serial.read();  //Read the data recieved
    Serial.print("Received data:");
    Serial.println(val);
    if (val == 'A') {
      digitalWrite(8, HIGH);
      Serial.println("Switch 1 is ON");
    }
    if (val == 'a') {
      digitalWrite(8, LOW);
      Serial.println("Switch 1 is OFF");
    }
    if (val == 'B') {
      digitalWrite(9, HIGH);
      Serial.println("Switch 2 is ON");
    }
    if (val == 'b') {
      digitalWrite(9, LOW);
      Serial.println("Switch 2 is OFF");
    }
     if (val == 'C'){
    digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      Serial.println("BOTH SWITCHES ON");
    }
    if (val == 'C'){
    digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      Serial.println("BOTH SWITCHES OFF");
    }
  }
}
