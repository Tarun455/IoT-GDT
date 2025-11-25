/* 
 *  Frugal IoT example - SOIL Sensor, with SHT
 * 
 * Optional: SENSOR_SHT_ADDRESS - defaults to 0x44, (note the D1 shields default to 0x45)
 */

// defines SENSOR_SHT_ADDRESS if dont define here or in platformio.ini
#include "Frugal-IoT.h"


// Change the parameters here to match your ... 
// organization, project, id, description
System_Frugal frugal_iot("varta", "developers", "Agriculture", "Agriculture Sensor"); 

void setup() {
  frugal_iot.pre_setup(); // Encapsulate setting up and starting serial and read main config

  // Override MQTT host, username and password if you have an "organization" other than "dev" (developers)
  frugal_iot.configure_mqtt("frugaliot.naturalinnovation.org", "varta", "notverysecret");

  // Configure power handling - type, cycle_ms, wake_ms 
  // power will be awake wake_ms then for the rest of cycle_ms be in a mode defined by type 
  // Loop= awake all the time; 
  // Light = Light Sleep; 
  // LightWiFi=Light + WiFi on (not working); 
  // Modem=Modem sleep - works but negligable power saving
  // Deep - works but slow recovery and slow response to UX so do not use except for multi minute cycles. 
  frugal_iot.configure_power(Power_Deep, 3600000, 20000);   //wake up for 20 seconds, once an hour

  // system_oled and actuator_ledbuiltin added automatically on boards that have them.

  // Add local wifis here, or see instructions in the wiki for adding via the /data
  frugal_iot.wifi->addWiFi(F("Tk"),F("9418036195"));
  
  // Add sensors, actuators and controls
  frugal_iot.sensors->add(new Sensor_SHT("SHT", SENSOR_SHT_ADDRESS, &I2C_WIRE, true));

  // Soil sensor 0%=4095 100%=0 pin=3 smooth=0 color=brown
  frugal_iot.sensors->add(new Sensor_Soil("soil", "Soil", 32, 4095, -100.0/4095, "brown", true));
  
  ControlHysterisis* cb = new ControlHysterisis("controlhysterisis", "Control", 50, 1, 0, 100);
  frugal_iot.controls->add(cb);
  cb->outputs[0]->wireTo(frugal_iot.messages->path("ledbuiltin/on"));

  // DS18B20 sensor for soil temperature
  frugal_iot.sensors->add(new Sensor_DS18B20("ds18b20", "Soil Temperature", 5, 0, true));

  // Dont change below here - should be after setup the actuators, controls and sensors
  frugal_iot.setup(); // Has to be after setup sensors and actuators and controls and sysetm
  Serial.println(F("FrugalIoT Starting Loop"));
}

void loop() {
  frugal_iot.loop(); // Should be running watchdog.loop which will call esp_task_wdt_reset()
}

