#include <Arduino.h>
#include <DHT.h>

// DHT11 sensor configuration
#define DHTPIN 26     // GPIO 26 for DHT11 data pin
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\nESP32 DHT11 Humidity & Temperature Sensor");
  Serial.println("==========================================");
  
  // Initialize DHT sensor
  dht.begin();
  Serial.println("DHT11 sensor initialized on GPIO 26");
  Serial.println("Starting measurements...\n");
}

void loop() {
  // Wait 2 seconds between measurements (DHT11 requires minimum 1 second)
  delay(2000);
  
  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("ERROR: Failed to read from DHT11 sensor!");
    return;
  }
  
  // Display readings
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% | Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
}
