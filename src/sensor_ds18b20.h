// DS18B20 waterproof temperature sensor for soil monitoring

#ifndef SENSOR_DS18B20_H
#define SENSOR_DS18B20_H

#include "sensor_float.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class Sensor_DS18B20 : public Sensor_Float {
public:
    // Constructor: id, name, pin, retain
    Sensor_DS18B20(const char* id, const char* name, uint8_t pin, bool retain);

protected:
    // Read temperature in Celsius
    float readFloat() override;
    // Initialize sensor
    void setup() override;

private:
    OneWire _oneWire;
    DallasTemperature _sensors;
};

#endif // SENSOR_DS18B20_H