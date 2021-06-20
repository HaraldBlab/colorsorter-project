#ifndef ColorDetector_h
#define ColorDetector_h

#include <Arduino.h>
#include "ColorSensor.h"
#include "ColorMapper.h"

// ColorDetector: detects the color of a brick and maps oit to a color number
// known operations:
// * measure the color of a brick
// * map a color value ot a color number
class ColorDetector {
private:
  int measure_ms = 400;
  int color_nr = 0;
  ColorSensor sensor;
public:
  ColorDetector() {}
  int begin() { return sensor.begin(); }
  int bucketAvailable() { 
    sensor.read();
    /* add some trace infor */
    Serial.print(sensor.r); Serial.print(", ");
    Serial.print(sensor.g); Serial.print(", ");
    Serial.print(sensor.b); Serial.println();
    
    color_nr = ColorMapper::detect(sensor.r, sensor.g, sensor.b);
    color_nr += 1;
    return 1; }
  int bucket() { return color_nr; }
};

#endif
