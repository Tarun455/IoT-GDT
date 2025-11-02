# DS18B20 Soil Temperature Sensor Guide

This guide explains how to add and use the DS18B20 waterproof temperature sensor in your Frugal-IoT project for soil temperature monitoring.

## Overview

The DS18B20 is a digital temperature sensor perfect for soil monitoring because:
- Waterproof design suitable for direct soil insertion
- OneWire protocol (only needs one data pin)
- High accuracy (±0.5°C from -10°C to +85°C)
- Wide temperature range (-55°C to +125°C)

## Hardware Setup

### Required Components
- DS18B20 waterproof temperature sensor
- 4.7kΩ pull-up resistor
- Jumper wires

### Wiring
```
DS18B20 Sensor    ESP32/ESP8266
--------------    -------------
Red (VCC)    →    3.3V or 5V
Black (GND)  →    GND
Yellow (Data)→    GPIO pin (e.g., GPIO 2)

Pull-up Resistor: Connect 4.7kΩ between Data line and VCC
```

### Pin Configuration
The default pin is GPIO 2, but you can change it in `main.cpp`:
```cpp
#define SOIL_TEMP_PIN 2  // Change to your preferred GPIO pin
```

## Software Integration

### 1. Add Required Files
Copy these files to your `src/` directory:
- `sensor_ds18b20.h`
- `sensor_ds18b20.cpp`

### 2. Include Dependencies
The required libraries are already included in `platformio.ini`:
```ini
lib_deps = 
    milesburton/DallasTemperature
    paulstoffregen/OneWire
```

### 3. Update main.cpp
Add the sensor to your Frugal-IoT setup:

```cpp
#include "Frugal-IoT.h"
#include "sensor_ds18b20.h"

#define SOIL_TEMP_PIN 2  // Define your GPIO pin

System_Frugal frugal_iot("dev", "developers", "SoilMonitor", "Soil Monitoring System");

void setup() {
    frugal_iot.pre_setup();
    
    // Add other sensors...
    
    // Add DS18B20 soil temperature sensor
    frugal_iot.sensors->add(new Sensor_DS18B20("soil_temp", "Soil Temperature", SOIL_TEMP_PIN, true));
    
    frugal_iot.setup();
}
```

## Sensor Parameters

When creating the sensor instance:
```cpp
new Sensor_DS18B20("soil_temp", "Soil Temperature", SOIL_TEMP_PIN, true)
```

Parameters:
- `"soil_temp"`: Unique sensor ID for MQTT topics
- `"Soil Temperature"`: Display name in UI
- `SOIL_TEMP_PIN`: GPIO pin number
- `true`: Retain MQTT messages (recommended for temperature data)

## MQTT Data Output

The sensor publishes temperature data to MQTT topics:
- Topic format: `{organization}/{project}/{device_id}/soil_temp`
- Data format: Temperature in Celsius (float with 2 decimal places)
- Color coding: Orange in Frugal-IoT dashboard

## Troubleshooting

### Common Issues

**Sensor not detected:**
- Check wiring connections
- Verify 4.7kΩ pull-up resistor is connected
- Ensure sensor is powered (3.3V or 5V)

**Reading -127°C or NAN:**
- Sensor disconnected or faulty
- Check OneWire bus integrity
- Verify pull-up resistor value


### Serial Monitor Output
Enable debugging to see sensor status:
```
DS18B20 sensor initialized
```

### Testing the Sensor
1. Upload the code and open Serial Monitor (460800 baud)
2. Check for initialization message
3. Monitor temperature readings in MQTT or dashboard
4. Test by changing sensor temperature (hold in hand vs. room temperature)

## Multiple Sensors

To use multiple DS18B20 sensors on the same OneWire bus:

```cpp
// Each sensor needs a unique ID and name
frugal_iot.sensors->add(new Sensor_DS18B20("soil_temp_1", "Soil Temp Zone 1", SOIL_TEMP_PIN, true));
frugal_iot.sensors->add(new Sensor_DS18B20("soil_temp_2", "Soil Temp Zone 2", SOIL_TEMP_PIN, true));
```

Note: Current implementation reads from index 0. For multiple sensors, you'll need to modify the code to specify device addresses.


## Integration with Other Sensors


Example complete soil monitoring setup:
```cpp
// Soil moisture
frugal_iot.sensors->add(new Sensor_Soil("soil", "Soil Moisture", 3, 4095, -100.0/4095, "brown", true));

// Air temperature/humidity  
frugal_iot.sensors->add(new Sensor_SHT("SHT", SENSOR_SHT_ADDRESS, &I2C_WIRE, true));

// Soil temperature
frugal_iot.sensors->add(new Sensor_DS18B20("soil_temp", "Soil Temperature", SOIL_TEMP_PIN, true));
```

This provides comprehensive soil and environmental monitoring for agricultural or gardening applications.