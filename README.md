# Updated Frugal IoT Environment & Soil Monitoring System

A comprehensive soil monitoring solution built with the Frugal-IoT framework for ESP32/ESP8266 microcontrollers. This project monitors soil moisture, ambient temperature/humidity, and soil temperature with wireless connectivity and control capabilities.

## Features

- **Soil Moisture Monitoring**: Analog sensor with configurable range (0-100%)
- **Environmental Sensing**: SHT30 temperature and humidity sensor via I2C
- **Soil Temperature**: DS18B20 waterproof temperature sensor
- **Wireless Connectivity**: WiFi with MQTT publishing
- **Control System**: Hysteresis-based control with LED feedback
- **Multi-Board Support**: Compatible with various ESP32/ESP8266 development boards
- **Power Management**: Configurable sleep modes for battery operation
- **LoRa Mesh**: Optional LoRaMesher support on compatible boards

## Hardware Requirements

### Core Components
- ESP32 or ESP8266 development board
- Soil moisture sensor (analog)
- SHT30 temperature/humidity sensor
- DS18B20 waterproof temperature sensor

### Supported Boards
- **ESP32-C3**: Lolin C3 Pico, C3 Mini
- **ESP32-S2**: Lolin S2 Mini  
- **ESP8266**: D1 Mini, D1 Mini Pro
- **LoRa Boards**: TTGO LoRa32 v2.1, LilyGo T3-S3

## Pin Configuration

| Component | Pin | Notes |
|-----------|-----|-------|
| Soil Moisture | GPIO 32 | Analog input |
| DS18B20 | GPIO 5 | OneWire with 4.7kΩ pullup |
| SHT30 |I2C (SDA → GPIO 21,SCL → GPIO 22)| Default address 0x44 (configurable to 0x45) |

## Installation

### Prerequisites
- [PlatformIO](https://platformio.org/) installed
- [Frugal-IoT library](https://github.com/frugal-iot/frugal-iot) 

### Setup
1. Clone this repository
2. Open in PlatformIO IDE or VS Code with PlatformIO extension
3. Select your target board environment
4. Build and upload

### Library Dependencies
The following libraries are automatically managed by PlatformIO:
- Frugal-IoT (main framework)
- DallasTemperature (DS18B20 sensor)
- OneWire (DS18B20 communication)
- SHT85 (included in Frugal-IoT)

## Configuration

### WiFi Setup
Add your WiFi credentials in `main.cpp`:
```cpp
frugal_iot.wifi->addWiFi(F("your_ssid"), F("your_password"));
```

### MQTT Configuration
The system connects to the default Frugal-IoT MQTT broker:
- **Host**: frugaliot.naturalinnovation.org
- **Username**: dev
- **Password**: public

### Sensor Calibration
Adjust soil moisture sensor calibration in `main.cpp`:
```cpp
// Parameters: id, name, pin, dry_value, scale_factor, color, retain
frugal_iot.sensors->add(new Sensor_Soil("soil", "Soil", 3, 4095, -100.0/4095, "brown", true));
```

### Power Management
Configure reading intervals and power modes:
```cpp
// Parameters: mode, cycle_ms, wake_ms
frugal_iot.configure_power(Power_Loop, 30000, 30000); // 30-second intervals, always awake
```

## Build Environments

Select the appropriate environment for your board:

```bash
# ESP32-C3 Pico
pio run -e c3_pico

# ESP32-S2 Mini
pio run -e s2_mini

# ESP8266 D1 Mini
pio run -e d1_mini

# TTGO LoRa (with mesh support)
pio run -e ttgo

# LilyGo T3-S3 (with mesh support)
pio run -e t3s3
```

## Data Output

The system publishes sensor data via MQTT with the following topics structure:
- Soil moisture percentage
- Ambient temperature (°C)
- Ambient humidity (%)
- Soil temperature (°C)

## Control Features

- **Hysteresis Control**: Automatic LED control based on soil moisture levels
- **Threshold**: 50% moisture with 1% hysteresis
- **Visual Feedback**: Built-in LED indicates system status

## Development

### Debug Flags
Enable debugging by uncommenting flags in `platformio.ini`:
```ini
-D SYSTEM_FRUGAL_DEBUG
-D SYSTEM_MQTT_DEBUG  
-D SENSOR_SOIL_DEBUG
```

### Custom Sensors
The project includes a custom DS18B20 sensor implementation in:
- `src/sensor_ds18b20.h`
- `src/sensor_ds18b20.cpp`

## Troubleshooting

### Common Issues
1. **Sensor not detected**: Check wiring and I2C address
2. **WiFi connection fails**: Verify credentials and signal strength
3. **MQTT not connecting**: Check network connectivity and broker settings
4. **DS18B20 reading errors**: Ensure 4.7kΩ pullup resistor is connected

### Serial Monitor
Monitor output at 460800 baud for debugging information.

## License

This project uses the Frugal-IoT framework. Please refer to the framework's license terms.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

## Support

For issues related to:
- **Hardware setup**: Check wiring diagrams and pin configurations
- **Frugal-IoT framework**: Refer to the [official documentation](https://github.com/frugal-iot/frugal-iot)
- **PlatformIO**: Visit [PlatformIO documentation](https://docs.platformio.org/)