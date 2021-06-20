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
  int clear_min = 50; /* minimum intensity for rgb conversion */
  float clear_base = 1000.0; /* base intensity for rgb conversion */
  Adafruit_APDS9960 sensor; /* using the color sensor only */
public:
  /* white reference color value to normalized to (255,255,255) */
  uint16_t white_raw_r, white_raw_g, white_raw_b, white_raw_c;  
  uint16_t raw_r, raw_g, raw_b, raw_c;
  uint16_t r, g, b, c;
public:
  ColorSensor() {}
  int begin() { 
    int ret = sensor.begin(); 
    if (ret != 0) {
      sensor.enableColor(true); /* enable no interrupt */
    }
    return ret;
  }
  void read() {
    while (! sensor.colorDataReady()) {
      delay(delay_ms);
    }
    sensor.getColorData(&raw_r, &raw_g, &raw_b, &raw_c);
    normalize();
  }
  int red() { return r; }
  int green() { return g; }
  int blue() { return b; }
  int clear() { return c; }
 private:
   void notcleared() {
      r = raw_r; g = raw_g; b = raw_b; c = raw_c;    
   }
   void interpolate() {
    float cscale = clear_base / float(raw_c);
    r = (int) (float(raw_r) * cscale);
    g = (int) (float(raw_g) * cscale);
    b = (int) (float(raw_b) * cscale);
    c = (int) clear_base;    
   }
   void normalize() {
    if (raw_c < clear_min) {
      /* use raw values if it is not lite up */
      notcleared();
    } else {
      /* linear approach for scaling */
      interpolate();
    }
   }
};
#endif
