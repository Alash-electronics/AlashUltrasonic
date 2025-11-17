#include <AlashUltrasonic.h>

// Параметры для разных типов подключения
const uint8_t TRIGGER_PIN = 7;  // GPIO trigger
const uint8_t ECHO_PIN = 8;     // GPIO echo
const uint8_t I2C_ADDRESS = 0x57; // I2C адрес
const uint8_t RX_PIN = 3;       // UART RX
const uint8_t TX_PIN = 2;       // UART TX
const uint8_t ONE_WIRE_PIN = A5; // 1-Wire пин

// Создание объектов для разных типов подключения
AlashUltrasonic sensorGPIO(TRIGGER_PIN, ECHO_PIN);           // GPIO режим
AlashUltrasonic sensorI2C(I2C_ADDRESS);                      // I2C режим
AlashUltrasonic sensorUART(RX_PIN, TX_PIN, UART_MODE);       // UART режим
AlashUltrasonic sensorOneWire(ONE_WIRE_PIN, ONEWIRE_MODE);   // 1-Wire режим

void setup() {
  Serial.begin(9600);
  Serial.println("AlashUltrasonic - Все режимы подключения");
  
  // Инициализация всех датчиков
  sensorGPIO.begin();
  sensorI2C.begin();
  sensorUART.begin();
  sensorOneWire.begin();
}

void loop() {
  Serial.println("=== Измерения расстояния ===");
  
  // GPIO измерение
  float distanceGPIO = sensorGPIO.getDistance();
  Serial.print("GPIO (пины ");
  Serial.print(TRIGGER_PIN);
  Serial.print(", ");
  Serial.print(ECHO_PIN);
  Serial.print("): ");
  Serial.print(distanceGPIO);
  Serial.println(" см");
  
  // I2C измерение
  float distanceI2C = sensorI2C.getDistance();
  Serial.print("I2C (адрес 0x");
  Serial.print(I2C_ADDRESS, HEX);
  Serial.print("): ");
  Serial.print(distanceI2C);
  Serial.println(" см");
  
  // UART измерение
  float distanceUART = sensorUART.getDistance();
  Serial.print("UART (пины ");
  Serial.print(RX_PIN);
  Serial.print(", ");
  Serial.print(TX_PIN);
  Serial.print("): ");
  Serial.print(distanceUART);
  Serial.println(" см");
  
  // 1-Wire измерение
  float distanceOneWire = sensorOneWire.getDistance();
  Serial.print("1-Wire (пин ");
  Serial.print(ONE_WIRE_PIN);
  Serial.print("): ");
  Serial.print(distanceOneWire);
  Serial.println(" см");
  
  Serial.println();
  delay(2000);
} 