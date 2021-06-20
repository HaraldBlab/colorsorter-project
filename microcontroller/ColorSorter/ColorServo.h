#ifndef ColorServo_h
#define ColorServo_h

#include <Arduino.h>
#include <Servo.h>
// ColorServo: basic servo handling.
class ColorServo {
protected:
  int delay_ms = 15;
  int pos_deg = 0;
  int servoPin;
  Servo servo;
public:
  ColorServo(int pin) { servoPin = pin; }
  int begin() { servo.attach(servoPin); return 1; }
  int pos() { return pos_deg; }
protected:
  void inc(int step_deg) { servo.write(pos_deg); delay(delay_ms); pos_deg += step_deg; }
  void inc(int stopPos_deg, int step_deg) {
    while(pos_deg < stopPos_deg)
      inc(step_deg); 
    pos_deg = stopPos_deg;
  }
  void dec(int step_deg) { servo.write(pos_deg); delay(delay_ms); pos_deg -= step_deg; }
  void dec(int stopPos_deg, int step_deg) {
    while(pos_deg > stopPos_deg)
      dec(step_deg); 
    pos_deg = stopPos_deg;}
};

#endif
