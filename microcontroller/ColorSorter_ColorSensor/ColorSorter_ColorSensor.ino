//
// A color sensor example.
//

#include "ColorSensor.h"
ColorSensor sensor;

#define SENSOR_STATE_ERROR 0
#define SENSOR_STATE_INIT 1
#define SENSOR_STATE_READ 2

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
}

void loop() {
  // FSM to run the sensor
  switch (sensor_state) {
    case SENSOR_STATE_INIT:
      sensor_state = SENSOR_STATE_READ;
      break;
    case SENSOR_STATE_READ:
      sensor.read();
      /* add some trace infor */
      Serial.print(sensor.red()); Serial.print(", ");
      Serial.print(sensor.green()); Serial.print(", ");
      Serial.print(sensor.blue()); Serial.print(", ");
      Serial.print(sensor.clear()); Serial.println();
      delay(500);
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
