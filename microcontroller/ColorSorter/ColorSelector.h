#ifndef ColorSelector_h
#define ColorSelector_h

#include <Arduino.h>
#include "ColorServo.h"

// ColorSelector: selects a brick and moves it to the detector and ejector.
// known positions:
// * funnel
// * detector
// * ejector
// * home
class ColorSelector : public ColorServo {
private:
  int homePos_deg = 0;
  int funnelPos_deg = 5+5;
  int detectorPos_deg = 95+10;
  int ejectorPos_deg = 170;
public:
  ColorSelector(int pin) : ColorServo(pin) {}
  void home() { dec(homePos_deg, 2); }
  void funnel() { inc(funnelPos_deg, 1); }
  void detector() { inc(detectorPos_deg, 1); }
  void ejector() { inc(ejectorPos_deg, 1); }
};

#endif
