#ifndef ColorEjector_h
#define ColorEjector_h

#include <Arduino.h>
#include "ColorServo.h"

// ColorEjector: moves a brick to a bucket based on the color number
// knows the posotion of a bucket by number.
class ColorEjector : public ColorServo {
private:
  int bucketStep_deg = 10;
public:
  ColorEjector(int pin) : ColorServo(pin) { }
  int begin() { servo.attach(servoPin); return 1; }
  int select(int bucket) { 
    int endPos_deg = bucket*bucketStep_deg; 
    if (endPos_deg > pos_deg)
      inc(endPos_deg, 1);
    else
      dec(endPos_deg, 1);
    return bucket; 
  }
};

#endif
