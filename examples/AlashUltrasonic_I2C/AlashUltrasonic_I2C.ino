#include <AlashUltrasonic.h>

// Параметры для GPIO
const uint8_t TRIGGER_PIN = A5;
const uint8_t ECHO_PIN = A4;

// Параметр для I2C
const uint8_t I2C_ADDRESS = 0x57;

// Создание объектов датчика для GPIO и I2C
AlashUltrasonic sensorI2C(I2C_ADDRESS);

void setup() {
  Serial.begin(9600);
  sensorI2C.begin();
}

void loop() {
  // Использование датчика через I2C
  float distanceI2C = sensorI2C.getDistance();
  Serial.print("Distance (I2C): ");
  Serial.print(distanceI2C);
  Serial.println(" cm");
  
  delay(1000);
}
