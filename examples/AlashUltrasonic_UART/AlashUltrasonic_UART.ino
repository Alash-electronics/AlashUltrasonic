#include <AlashUltrasonic.h>

// Параметры для UART
const uint8_t RX_PIN = 3; // Подключите Echo_TX_SDA
const uint8_t TX_PIN = 2; // Подключите Trig_RX_SCL_I/O

AlashUltrasonic sensorUART(RX_PIN, TX_PIN, UART_MODE); // (Echo_TX_SDA, Trig_RX_SCL_I/O)

void setup() {
  Serial.begin(9600);
  sensorUART.begin();
}
void loop() {  
  // Использование датчика через UART
  float distanceUART = sensorUART.getDistance();
  Serial.print("Distance (UART): ");
  Serial.print(distanceUART);
  Serial.println(" cm");
  delay(1000);
}