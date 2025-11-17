#include <AlashUltrasonic.h>

// Параметры для 1-Wire
const uint8_t ONE_WIRE_PIN = A5;

AlashUltrasonic sensorOneWire(ONE_WIRE_PIN, ONEWIRE_MODE);

void setup() {
  Serial.begin(9600);
  sensorOneWire.begin();
}

void loop() {
  // Использование датчика через 1-Wire
  float distanceOneWire = sensorOneWire.getDistance();
  Serial.print("Distance (1-Wire): ");
  Serial.print(distanceOneWire);
  Serial.println(" cm");
  
  delay(1000);
}
