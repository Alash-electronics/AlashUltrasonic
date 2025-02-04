#include "AlashUltrasonic.h"

// Конструктор для GPIO
AlashUltrasonic::AlashUltrasonic(uint8_t triggerPin, uint8_t echoPin) {
  _triggerPin = triggerPin;
  _echoPin = echoPin;
  _useI2C = false;
  _useUART = false;
  _useOneWire = false;
  _lastReadTime = 0;
}

// Конструктор для I2C
AlashUltrasonic::AlashUltrasonic(uint8_t i2cAddress) {
  _i2cAddress = i2cAddress;
  _useI2C = true;
  _useUART = false;
  _useOneWire = false;
  _lastReadTime = 0;
}

// Конструктор для UART
AlashUltrasonic::AlashUltrasonic(uint8_t rxPin, uint8_t txPin, bool useUART) {
  _rxPin = rxPin;
  _txPin = txPin;
  _useUART = useUART;
  _useI2C = false;
  _useOneWire = false;
  _lastReadTime = 0;
  _serial = new SoftwareSerial(_rxPin, _txPin);
}

// Конструктор для 1-Wire
AlashUltrasonic::AlashUltrasonic(uint8_t oneWirePin, bool useOneWire) {
  _oneWirePin = oneWirePin;
  _useOneWire = useOneWire;
  _useI2C = false;
  _useUART = false;
  _lastReadTime = 0;
}

// Инициализация
void AlashUltrasonic::begin() {
  if (_useI2C) {
    Wire.begin();
  } else if (_useUART) {
    _serial->begin(9600);
  } else if (_useOneWire) {
    pinMode(_oneWirePin, OUTPUT);
  } else {
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
  }
}

// Измерение расстояния
float AlashUltrasonic::getDistance() {
  if (millis() - _lastReadTime < 30) {
    delay(millis() - _lastReadTime);
  }
  _lastReadTime = millis();

  if (_useI2C) {
    return getDistanceI2C();
  } else if (_useUART) {
    return getDistanceUART();
  } else if (_useOneWire) {
    return getDistanceOneWire();
  } else {
    return getDistanceGPIO();
  }
}

// Измерение расстояния через GPIO
float AlashUltrasonic::getDistanceGPIO() {
  digitalWrite(_triggerPin, HIGH);
  delayMicroseconds(500);
  digitalWrite(_triggerPin, LOW);

  long duration = pulseIn(_echoPin, HIGH);
  return calculateDistance(duration);
}

// Измерение расстояния через I2C
float AlashUltrasonic::getDistanceI2C() {
  Wire.beginTransmission(_i2cAddress);
  Wire.write(0x01);
  Wire.endTransmission();
  
  delay(150);

  byte response[3];
  Wire.requestFrom((uint8_t)_i2cAddress, (uint8_t)3);
  for (byte i = 0; Wire.available() && (i < 3); i++) {
    response[i] = Wire.read();
  }

  float micrometers = ((response[0] * 65536UL) + (response[1] * 256UL) + response[2]);
  return micrometers / 1000000.0 * 100.0;
}

// Измерение расстояния через UART
float AlashUltrasonic::getDistanceUART() {
  _serial->flush();
  _serial->write(0xA0);
  
  delay(150);
  
  byte response[3];
  for (byte i = 0; _serial->available() && (i < 3); i++) {
    response[i] = _serial->read();
  }
  
  float micrometers = ((response[0] * 65536UL) + (response[1] * 256UL) + response[2]);
  return micrometers / 1000000.0 * 100.0;
}

// Измерение расстояния через 1-Wire
float AlashUltrasonic::getDistanceOneWire() {
  pinMode(_oneWirePin, OUTPUT);
  digitalWrite(_oneWirePin, HIGH);
  delayMicroseconds(500);
  digitalWrite(_oneWirePin, LOW);

  pinMode(_oneWirePin, INPUT);
  long duration = pulseIn(_oneWirePin, HIGH);
  float distance = duration * 340.0 / 2.0 / 10000.0;
  return distance;
}

// Преобразование времени в расстояние
float AlashUltrasonic::calculateDistance(long duration) {
  float distance = (duration / 2.0) * 0.0343;
  return distance;
}
