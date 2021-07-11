//
// A color sensor example.
//

#include "ColorSensor.h"
ColorSensor sensor;

/*
 * Dimmed led by pwm
 * Refresh rate about 100 Hz needed to 'look' continuous.
 */
class DimmedLed {
  int potiPin = 0;
  int pwmPin = 9;
  unsigned long last_millis;
public:
  unsigned int duty;
  unsigned long duration;
  int begin() { last_millis = millis(); return 1;}
  void loop() {
    duty = map ( analogRead(potiPin) , 0 , 1023 , 0 , 190 );
    analogWrite(pwmPin, duty);
    unsigned long next_millis = millis();
    duration = millis() - last_millis;
    last_millis = next_millis;
  }
};

DimmedLed light;

#define SENSOR_STATE_ERROR 0
#define SENSOR_STATE_INIT 1
#define SENSOR_STATE_MEASURE 2
#define SENSOR_STATE_READ 3

int sensor_state = SENSOR_STATE_INIT;

void setup() {
  Serial.begin(115200);
  while (! Serial) ;

  sensor_state = SENSOR_STATE_INIT;
  
  // start the engine
  if (! sensor.begin()) {
    Serial.println(F("Failed to setup sensor!"));
    sensor_state = SENSOR_STATE_ERROR;
  }
  if (! light.begin()) {
    Serial.println(F("Failed to setup light!"));
    sensor_state = SENSOR_STATE_ERROR;
  }
}

unsigned long last_millis;

int need_measure(unsigned long limit) {
    unsigned long next_millis = millis();
    unsigned long duration = millis() - last_millis;
    if (duration < limit)
      return 0;
    last_millis = next_millis;
    return 1;
}
void loop() {
  // dimmed light
  light.loop();
  Serial.print(F("Duration ")); Serial.print(light.duration); Serial.println(F(" [ms]")); 
  Serial.print(F("Duty     ")); Serial.print(light.duty); Serial.println(F(" [0..190]")); 
  
  // FSM to run the sensor
  switch (sensor_state) {
    case SENSOR_STATE_INIT:
      last_millis = millis();
      sensor_state = SENSOR_STATE_MEASURE;
      break;
    case SENSOR_STATE_MEASURE:
      if (need_measure(1000))
       sensor_state = SENSOR_STATE_READ;
      break;
    case SENSOR_STATE_READ:
      sensor.read();
      /* add some trace info */
      Serial.print(F("Color ")); 
      Serial.print(sensor.red()); Serial.print(F(", "));
      Serial.print(sensor.green()); Serial.print(F(", "));
      Serial.print(sensor.blue()); Serial.print(F(", "));
      Serial.print(sensor.clear()); Serial.println();

      sensor_state = SENSOR_STATE_INIT;
      break;
    case SENSOR_STATE_ERROR:
      Serial.println(F("**error detected: stopped!"));
      delay(1000);
      break;
    default:
      Serial.println(F("invalid state!"));
      delay(1000);
      break;
  }
  
}
