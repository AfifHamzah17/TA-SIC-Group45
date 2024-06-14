#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

#define DHTPIN D1          // DHT11 sensor pin
#define DHTTYPE DHT11      // DHT11 sensor type

const char* ssid = "ANFI HOME"; // Your Wi-Fi network SSID
const char* password = "08052022"; // Your Wi-Fi network password
const char* serverName = "http://192.168.100.8:5000/api/data"; // Your server address

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  delay(30000); // Wait for 30 seconds
  float temperature = dht.readTemperature(); // Read temperature value from DHT11 sensor
  float humidity = dht.readHumidity(); // Read humidity value from DHT11 sensor

  // Create JSON payload
  String payload = "{\"temp\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";

  // Create HTTP client
  WiFiClient client;

  // Create HTTP request
  HTTPClient http;
  http.begin(client, serverName);

  // Add headers
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", "SIC45"); // Add X-API-Key header

  // Send HTTP POST request
  int httpCode = http.POST(payload);

  // Check for response
  if (httpCode > 0) {
    Serial.println("Data sent successfully");
    Serial.println(httpCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.println("Error sending data");
  }

  // Close HTTP connection
  http.end();
}
