// This code turns your NodeMCU into a standalone web server.
// It serves a webpage that displays real-time sensor values with a fast refresh rate.
// The HTML is stored in PROGMEM for better memory efficiency.

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> // Using the WebServer library is better for handling different URLs
#define LED LED_BUILTIN
// --- IMPORTANT: UPDATE THESE VALUES ---
const char* ssid = "Raj_4g";        // Your WiFi network name (SSID)
const char* password = "55556666"; // Your WiFi password
// ---

// Create a web server object on port 80
ESP8266WebServer server(80);

// Global variable to hold the latest sensor reading.
// 'volatile' is used because this variable is modified in the main loop
// and accessed by the server's request handler.
volatile int currentSensorValue = 0;

// --- HTML Page stored in Program Memory (PROGMEM) to save RAM ---
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang='en'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>NodeMCU Real-Time Data</title>
    <style>
      body { font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Helvetica, Arial, sans-serif; display: flex; align-items: center; justify-content: center; height: 100vh; margin: 0; background-color: #f0f2f5; }
      .card { text-align: center; background-color: white; padding: 2rem 2.5rem; border-radius: 12px; box-shadow: 0 4px 12px rgba(0,0,0,0.1); }
      h1 { color: #1d4ed8; margin-top: 0; }
      .sensor-value { font-size: 4rem; font-weight: bold; color: #1e3a8a; margin: 1rem 0; }
    </style>
</head>
<body>
    <div class='card'>
      <h1>Live Data</h1>
      <p>Receiving data directly from the device.</p>
      <p id='sensorValue' class='sensor-value'>--</p>
      <p style='color: #6b7280; font-size: 0.8rem;'>Updating every 10ms.</p>
    </div>

    <script>
      // Fetch sensor data every 10 milliseconds
      setInterval(function() {
        fetch('/data')
          .then(response => response.text())
          .then(data => {
            document.getElementById('sensorValue').innerText = data;
          }).catch(error => console.error('Error fetching data:', error));
      }, 10);
    </script>
</body>
</html>
)=====";

// This function is called when a browser requests the root page ("/")
void handleRoot() {
  // Send the HTML page stored in PROGMEM
  server.send_P(200, "text/html", MAIN_page);
}

// This function is called when the JavaScript on the page requests "/data"
void handleData() {
  // Send the most recently read sensor value back as plain text.
  // The reading now happens in the main loop(), not here.
  server.send(200, "text/plain", String(currentSensorValue));
}

void setup() {
  Serial.begin(115200);
  pinMode(D6, INPUT_PULLUP); // Corrected from INPUT_PULLUP for ESP8266 core
  pinMode(LED, OUTPUT); // Corrected from INPUT_PULLUP for ESP8266 core
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // --- Define the URL handlers ---
  server.on("/", handleRoot);
  server.on("/data", handleData);

  server.begin();
  Serial.println("Server started.");
  Serial.print("Use this URL to connect: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  // This function checks for incoming browser requests and directs them
  // to the correct handler function. It needs to be called as often as possible.
  server.handleClient();

  // --- Independent Sensor Reading ---
  // This code block runs continuously, regardless of whether a client is connected.
  // It reads the sensor and updates the global variable.
  currentSensorValue = digitalRead(D6);
  
  // Optional: Print the value to the Serial Monitor to show it's working.
  // We add a small delay to avoid spamming the monitor too quickly.
  Serial.print("Sensor value is now: ");
  Serial.println(currentSensorValue);
  if(currentSensorValue ==1){
    digitalWrite(LED,0);
  }
  else{
    digitalWrite(LED,1);
  }
  //delay(200); // Read sensor approximately 5 times per second.
}

