#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> // Using the WebServer library is better for handling different URLs

// --- IMPORTANT: UPDATE THESE VALUES ---
const char* ssid = "/*****";        // Your WiFi network name (SSID)
const char* password = "*****"; // Your WiFi password
// ---

// Create a web server object on port 80
ESP8266WebServer server(80);

// This function is called when a browser requests the root page ("/")
void handleRoot() {
  // Build the main HTML content in a single String variable.
  // This page includes JavaScript to fetch updates automatically.
  String html = "<!DOCTYPE html>";
  html += "<html lang='en'>";
  html += "<head>";
    html += "<meta charset='UTF-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<title>NodeMCU Real-Time Data</title>";
    html += "<style>";
      html += "body { font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Helvetica, Arial, sans-serif; display: flex; align-items: center; justify-content: center; height: 100vh; margin: 0; background-color: #f0f2f5; }";
      html += ".card { text-align: center; background-color: white; padding: 2rem; border-radius: 12px; box-shadow: 0 4px 12px rgba(0,0,0,0.1); }";
      html += "h1 { color: #1d4ed8; }";
      html += ".sensor-value { font-size: 4rem; font-weight: bold; color: #1e3a8a; margin: 1rem 0; }";
    html += "</style>";
  html += "</head>";
  html += "<body>";
    html += "<div class='card'>";
      html += "<h1>Live Data from NodeMCU</h1>";
      html += "<p>Receiving data directly from the device.</p>";
      // The initial value is 0, but JavaScript will update it immediately.
      html += "<p id='sensorValue' class='sensor-value'>--</p>";
      html += "<p style='color: #6b7280; font-size: 0.8rem;'>This page updates in real-time.</p>";
    html += "</div>";
    // --- JavaScript for real-time updates ---
    html += "<script>";
      // This function runs every 1 second to get new data
      html += "setInterval(function() {";
        // fetch('/data') asks the NodeMCU for the latest sensor reading
        html += "fetch('/data')";
          html += ".then(response => response.text())"; // Get the response as plain text
          html += ".then(data => {";
            // Find the HTML element with the id 'sensorValue' and update its content
            html += "document.getElementById('sensorValue').innerText = data;";
          html += "}).catch(error => console.error('Error fetching data:', error));"; // Handle errors
      html += "}, 10);"; // 1000 milliseconds = 1 second
    html += "</script>";
  html += "</body>";
  html += "</html>";

  // Send the complete HTML page to the browser
  server.send(200, "text/html", html);
}

// This function is called when the JavaScript on the page requests "/data"
void handleData() {
  // Read the current sensor value
  int sensorValue = digitalRead(D6);
  Serial.print("Data requested. Sending: ");
  Serial.println(sensorValue);
  if(sensorValue == 1){
    digitalWrite(LED_BUILTIN,0);
  }
  else{
    digitalWrite(LED_BUILTIN,1);
  }
  
  // Send just the sensor value back as plain text.
  // The String() is required to convert the number to text.
  server.send(200, "text/plain", String(sensorValue));
}

void setup() {
  Serial.begin(115200);
  pinMode(D6, INPUT_PULLUP);
  pinMode(LED_BUILTIN,OUTPUT);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // --- Define the URL handlers ---
  // When a browser asks for the main page, call the handleRoot function.
  server.on("/", handleRoot);
  // When the JavaScript asks for "/data", call the handleData function.
  server.on("/data", handleData);

  server.begin();
  Serial.println("Server started.");
  Serial.print("Use this URL to connect: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  // This function checks for incoming browser requests and directs them
  // to the correct handler function (handleRoot or handleData).
  server.handleClient();
}

