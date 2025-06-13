#include <DHT.h>

// Define pins
#define DHTPIN 2       // DHT11 data pin
#define DHTTYPE DHT11  // DHT11 sensor type

#define IN1 4
#define IN2 5
#define ENA 6

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Set direction
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void loop() {
  float temp = dht.readTemperature(); // Celsius by default

  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println(" °C");

  // Control motor speed
  if (temp < 25.0) {
    analogWrite(ENA, 0); // Motor OFF
  } else if (temp < 27.0) {
    analogWrite(ENA, 100); // Slow
  } else if (temp < 30.0) {
    analogWrite(ENA, 180); // Medium
  } else {
    analogWrite(ENA, 255); // Fast
  }

  delay(1000); // Read every 1 second
}
