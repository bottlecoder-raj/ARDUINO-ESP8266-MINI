#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
bool motor_status = true;
int sms_stat=0;

// NodeMCU pins for SIM900L
SoftwareSerial sim900(D5, D6);  // RX, TX

#define LED_PIN D0   // GPIO14 - LED connected here

String senderNumber = "+919702789546";

void setup() {
  Serial.begin(115200);
  sim900.begin(9600);
  myservo.attach(D3);
  myservo.write(0);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  Serial.println("Initializing SIM900L...");
  Serial.println(" SIM900L activating...");

  // Text mode for SMS
  sim900.println("AT+CMGF=1");
  delay(500);

  // New SMS indications: deliver directly
  sim900.println("AT+CNMI=1,2,0,0,0");
  delay(500);
  Serial.println(" SIM900L activated...");
  sendSMS(senderNumber, "NodeMCU has started successfully!");


}

void loop() {
  if (sim900.available()) {
    String sms = sim900.readString();
    Serial.println("SMS Received: " + sms);

    sms.toUpperCase(); // make comparison case-insensitive

    if (sms.indexOf("ON") >= 0) {
      delay(500);
      sms_stat+=1;
       Serial.println("IRRIGATION Turned ON");
      if(sms_stat==1){
      sendSMS(senderNumber, "MOTOR is now ON");
      } sms_stat=0;
      Serial.print("STATUS:");
        Serial.println(sms_stat); //motorOn();
      digitalWrite(LED_PIN, LOW);
        myservo.write(180);
        delay(500);
     }
    else if (sms.indexOf("OFF") >= 0) {
      sms_stat+=2;
      Serial.println("IRRIGATION Turned OFF");
      if(sms_stat==2){
      sendSMS(senderNumber, "MOTOR is now OFF");}
      sms_stat=0;
      digitalWrite(LED_PIN, HIGH);
      Serial.print("STATUS:");
      Serial.println(sms_stat); 
      myservo.write(0);
        delay(500);    }
  }
}

// Function to send SMS
void sendSMS(String number, String text) {
  if (number.length() == 0) {
    number = "+919702789546"; // fallback: put your number here
  }

  sim900.println("AT+CMGF=1"); // text mode
  delay(500);
  sim900.print("AT+CMGS=\"");
  sim900.print(number);
  sim900.println("\"");
  delay(500);
  sim900.print(text);
  delay(500);
  sim900.write(26); // Ctrl+Z
  delay(5000);

  Serial.println("Reply sent to " + number);
}
