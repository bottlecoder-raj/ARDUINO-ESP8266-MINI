/*pin connection
Sensor to Arduino
vcc on pin 8
trig pin to pin 9 
echo pin on pin 10
gnd pin on 11

then compile and run the program 
open the serial monitor and it's READY!!!!!
*/
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch;

void setup() {

pinMode(trigPin, OUTPUT);
pinMode(8, OUTPUT);
pinMode(11, OUTPUT);
pinMode(echoPin, INPUT);
Serial.begin(9600);
}

void loop() {
digitalWrite(8, HIGH);
digitalWrite(11, LOW);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;
distanceInch = duration*0.0133/2;

Serial.print("Distance: "); // Prints string "Distance" on the LCD
Serial.print(distanceCm); // Prints the distance value from the sensor
Serial.print("  cm    ");
delay(100);


Serial.println();
}
