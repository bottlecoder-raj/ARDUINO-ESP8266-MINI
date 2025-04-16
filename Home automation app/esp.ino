#include <ESP8266WiFi.h>



WiFiClient client;

WiFiServer server(80);



void setup() {

  Serial.begin(9600);

  WiFi.begin("Raj_4g", "66665555");



  while (WiFi.status() != WL_CONNECTED) {

    delay(200);

    Serial.print(".");

  }



  Serial.println("\nConnected to WiFi");

  Serial.println(WiFi.localIP());

  server.begin();

}



void loop() {

  client = server.available();



  if (client) {

    String request = client.readStringUntil('\r');

    Serial.print(request);



   


  client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");
client.println();

client.println("<!DOCTYPE html><html><head><title>Home Automation</title>");

// ADD THIS LINE ↓
client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");

client.println("<style>body{background:#000;color:#fff;text-align:center;font-family:sans-serif}.button{display:inline-block;padding:12px 20px;margin:10px;background:#4CAF50;color:white;text-decoration:none;border-radius:6px}</style>");
client.println("</head><body><h1>ESP8266 Home Control</h1>");
client.println("<a class='button' href='/led1on'>Switch 1 ON</a>");
client.println("<a class='button' href='/led1off'>Switch 1 OFF</a>");
client.println("<a class='button' href='/led2on'>Switch 2 ON</a>");
client.println("<a class='button' href='/led2off'>Switch 2 OFF</a>");
client.println("<a class='button' href='/on'>ALL ON</a>");
client.println("<a class='button' href='/off'>ALL OFF</a>");
client.println("</body></html>");

client.stop();

  }}
