#include <AlashUltrasonic.h>

#if defined(ESP32) || defined(ESP8266)
const uint8_t TRIGGER_PIN = 5;   // на ESP нет пинов A4/A5: используем GPIO
const uint8_t ECHO_PIN = 4;
#else
const uint8_t TRIGGER_PIN = A5;
const uint8_t ECHO_PIN = A4;
#endif
AlashUltrasonic sensor(TRIGGER_PIN, ECHO_PIN);

void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  float distance = sensor.getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
}
