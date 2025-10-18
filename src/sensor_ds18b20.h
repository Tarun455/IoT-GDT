#ifndef SENSOR_DS18B20_H
#define SENSOR_DS18B20_H

#include "sensor_float.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class Sensor_DS18B20 : public Sensor_Float {
public:
    Sensor_DS18B20(const char* id, const char* name, uint8_t pin, bool retain);

protected:
    // Override the readFloat method from the base class
    float readFloat() override;
    void setup() override;

private:
    OneWire _oneWire;
    DallasTemperature _sensors;
};

#endif // SENSOR_DS18B20_H