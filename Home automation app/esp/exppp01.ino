#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);


void setup() {
  Serial.begin(9600); // To Arduino via TX pin
  WiFi.begin("DESKTOP-IOT", "12345678");

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print("..");
  }

  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());

  server.begin();


}

void loop() {
  client = server.available(); // Check if a client is connected

  if (client) {
    String request = client.readStringUntil('\r');
    Serial.print(request);  // 🔁 Send to Arduino



    // Send a basic HTTP response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<html><body><h1>ESP8266 Received</h1></body></html>");
    client.stop(); // Close the connection
  }
}
