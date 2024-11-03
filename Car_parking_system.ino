/* Hi this RAJ  the author for this code
THIS IS A CODE FOR ARDUINO CAR PARKING SYSTEM
REQUIREMENTS:
ARDUINO UNO
LCD DISPLAY WITH I2C MODULE
SERVO MOTOR
2 IR SENSORS

ATTACHMENTS:
SERVO OUT TO PIN 9
IR SENSOR1 TO 6
IR SENSOR2 TO 7
I2C WITH SDA,SCL ON BOARD


THANKYOU!!! 
*/


#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);   
#include <Servo.h> 
Servo myservo;
int slot = 5;           //Total number of parking Slots
int R2=6;
int R1=7;

void setup() {
    Serial.begin(9600); 
    lcd.init(); //initialize the lcd
    lcd.backlight(); //open the backlight

//SENSORS
pinMode(R1, INPUT);
pinMode(R2, INPUT);

//SERVO
 myservo.attach(9);
 myservo.write(170);

 //LCD DISPLAY INTRO
lcd.setCursor (0,0);
lcd.print("     ARDUINO    ");
lcd.setCursor (0,1);
lcd.print(" PARKING SYSTEM ");
delay (2000);
lcd.clear();  
 lcd.setCursor (0,0);
lcd.print("    WELCOME   ");  
lcd.setCursor (0,1);
lcd.print("SLOTS LEFT: "); 
lcd.print(slot);

}

void loop() {

  // put your main code here, to run repeatedly:
if( slot<5 && digitalRead (R1) ==0 && digitalRead (R2) == 1){
  slot=slot+1;
 
  myservo.write(170);
  lcd.setCursor (0,0);
lcd.print("    WELCOME   ");  
lcd.setCursor (0,1);
lcd.print("SLOTS LEFT: "); 
lcd.print(slot);
myservo.write(90);
  delay(2000);
   myservo.write(170);

}
 else if(slot>=0  && digitalRead (R2) ==0 && digitalRead (R1) == 1){
  slot=slot-1;

myservo.write(170);
lcd.setCursor (0,0);
lcd.print("    WELCOME   ");  
lcd.setCursor (0,1);
lcd.print("SLOTS LEFT: "); 
lcd.print(slot);
myservo.write(90);
delay(2000);
myservo.write(170);

}
else if(slot<=0){
lcd.setCursor (0,0);
lcd.print("    SORRY :(    ");  
lcd.setCursor (0,1);
lcd.print("  Parking Full  "); 
delay (3000);
lcd.clear(); 
}

}