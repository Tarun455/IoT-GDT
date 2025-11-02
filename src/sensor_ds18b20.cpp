#include "sensor_ds18b20.h"

// Constructor: setup sensor with temperature range -55 to 125°C, 2 decimal places, orange color
Sensor_DS18B20::Sensor_DS18B20(const char* id, const char* name, uint8_t pin, bool retain)
    : Sensor_Float(id, name, 2, -55, 125, "orange", retain),
      _oneWire(pin),
      _sensors(&_oneWire) {}

// Initialize the sensor
void Sensor_DS18B20::setup() {
    _sensors.begin();
    Serial.println("DS18B20 sensor initialized");
}

// Read temperature from sensor
float Sensor_DS18B20::readFloat() {
    _sensors.requestTemperatures();
    float tempC = _sensors.getTempCByIndex(0);

    // Check if sensor is connected
    if (tempC != DEVICE_DISCONNECTED_C) {
        return tempC;
    }
    return NAN; // Return error if sensor disconnected
}