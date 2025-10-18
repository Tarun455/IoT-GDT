#include "sensor_ds18b20.h"

Sensor_DS18B20::Sensor_DS18B20(const char* id, const char* name, uint8_t pin, bool retain)
    // Call the base class constructor
    : Sensor_Float(id, name, 2, -55, 125, "orange", retain),
      _oneWire(pin),
      _sensors(&_oneWire) {}

void Sensor_DS18B20::setup() {
    _sensors.begin();
    Serial.println("DS18B20 sensor initialized");
}

float Sensor_DS18B20::readFloat() {
    _sensors.requestTemperatures();
    float tempC = _sensors.getTempCByIndex(0);

    if (tempC != DEVICE_DISCONNECTED_C) {
        return tempC;
    }
    return NAN; // Return Not-a-Number if the reading fails
}