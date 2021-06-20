//
// A (little) brick by color sorter
//
// Components:
// * selector: selects a brick and moves it to the detector and ejector.
// * detector: detects the color of a brick and maps oit to a color number
// * ejector: moves a brick to a bucket based on the color number
//

#include "ColorSelector.h"
#include "ColorDetector.h"
#include "ColorEjector.h"

// the components used by the sorter
#define SELECTOR_PIN 4
ColorSelector selector(SELECTOR_PIN);
ColorDetector detector;
#define EJECTOR_PIN 5
ColorEjector ejector(EJECTOR_PIN);

#define SORTER_STATE_ERROR 0
#define SORTER_STATE_INIT 1
#define SORTER_STATE_SELECT_FUNNEL 2
#define SORTER_STATE_SELECT_DETECT 3
#define SORTER_STATE_DETECT 4
#define SORTER_STATE_EJECT 5
int sorter_state = SORTER_STATE_INIT;

void setup() {
  Serial.begin(115200);
  while (! Serial) ;

  // start the engine
  if (! selector.begin()) {
    Serial.println(F("Failed to setup selector!"));
    sorter_state = SORTER_STATE_ERROR;
  }
  if (! detector.begin()) {
    Serial.println(F("Failed to setup detector!"));
    sorter_state = SORTER_STATE_ERROR;
  }
  if (! ejector.begin()) {
    Serial.println(F("Failed to setup ejector!"));
    sorter_state = SORTER_STATE_ERROR;
  }
}

void loop() {
  // FSM to run the sorter
  switch (sorter_state) {
    case SORTER_STATE_INIT:
      selector.home();
      sorter_state = SORTER_STATE_SELECT_FUNNEL;
      break;
    case SORTER_STATE_SELECT_FUNNEL:
      selector.funnel();
      // TODO: wait for brick dropped from funnel
      delay(400);
      sorter_state = SORTER_STATE_SELECT_DETECT;
      break;
    case SORTER_STATE_SELECT_DETECT:
      selector.detector();
      sorter_state = SORTER_STATE_DETECT;
      break;
    case SORTER_STATE_DETECT:
      if (detector.bucketAvailable()) {
        sorter_state = SORTER_STATE_EJECT;
      }
      break;
    case SORTER_STATE_EJECT:
      ejector.select(detector.bucket());
      selector.ejector();
      sorter_state = SORTER_STATE_INIT;
      // TODO: wait for brick dropped to ejector
      delay(400);
      break;
    case SORTER_STATE_ERROR:
      Serial.println(F("**error detected: stopped!"));
      break;
    default:
      Serial.println(F("invalid state!"));
      break;
  }
  Serial.print(selector.pos() / 5); Serial.print(", ");
  Serial.print(detector.bucket()); Serial.print(", ");
  Serial.print(ejector.pos() / 5); Serial.println();
  
}
