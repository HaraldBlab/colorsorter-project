#ifndef ColorSensor_h
#define ColorSensor_h

#include <Arduino.h>
// I2C device with address 39
#include "Adafruit_APDS9960.h"

// ColorSensor: measures the color of a single brick
// 
// * read: reads a live color value
// * r,g,b: access to the color values read
//
class ColorSensor {
private:
  int delay_ms = 5;
  Adafruit_APDS9960 sensor;
public:
  uint16_t r, g, b, c;
public:
  ColorSensor() {}
  int begin() { 
    int ret = sensor.begin(); 
    if (ret != 0) {
      sensor.enableColor(true);
    }
    return ret;
  }
  void read() {
    while (! sensor.colorDataReady()) {
      delay(delay_ms);
    }
    sensor.getColorData(&r, &g, &b, &c);
  }
};
#endif
