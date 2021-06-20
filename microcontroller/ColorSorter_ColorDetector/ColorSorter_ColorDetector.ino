/*
  ColorSorter_ColorDetector - Color Detector
*/

#include "ColorDetector.h"

namespace Assert {
  int Validate(int result) {
    Serial.println(result ? "OK" : "**FAIL**");
    return result;
  }
  int AreEqual(int actual, int expected) {
    Serial.print("Actual: "); Serial.println(actual);
    Serial.print("Expected: "); Serial.println(expected);
    return Validate(actual == expected);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Verifying bricks colors");
  for (int i = 0; i < ColorDetector::MAX_BRICKS; i++) {
    int brick = ColorDetector::detect(ColorDetector::bricks[i]);
    Serial.print("brick = ");
    Serial.println(brick);
    Assert::AreEqual(brick, i);
  }
  
  Serial.println("Verifying unknown colors");
  int brick = ColorDetector::detect(17, 117, 217);
  Serial.print("brick = ");
  Serial.println(brick);
  Assert::AreEqual(brick, -1);

  Serial.println("Verifying colors in brick limit");
  for (int i = 0; i < ColorDetector::MAX_BRICKS; i++) {
    ColorDetector::color ref;
    red(ref) = 3 + red(ColorDetector::bricks[i]);
    green(ref) = 3 + green(ColorDetector::bricks[i]);
    blue(ref) = 3 + blue(ColorDetector::bricks[i]);
    int brick = ColorDetector::detect(ref);
    Serial.print("brick = ");
    Serial.println(brick);
    Assert::AreEqual(brick, i);
  }

  Serial.println("Verifying colors outside brick limit");
  for (int i = 0; i < ColorDetector::MAX_BRICKS; i++) {
    ColorDetector::color ref;
    red(ref) = 4 + red(ColorDetector::bricks[i]);
    green(ref) = 4 + green(ColorDetector::bricks[i]);
    blue(ref) = 4 + blue(ColorDetector::bricks[i]);
    int brick = ColorDetector::detect(ref);
    Serial.print("brick = ");
    Serial.println(brick);
    Assert::AreEqual(brick, -1);
  }

  Serial.println("Verifying brick colors distance");
  for (int i = 0; i < ColorDetector::MAX_BRICKS; i++) {
    for (int j = 0; j < ColorDetector::MAX_BRICKS; j++) {
      int distance = ColorDetector::distance(ColorDetector::bricks[i], ColorDetector::bricks[j]);
      int inside = distance < ColorDetector::detect_limit;
      Serial.print(inside ? " X " : " . ");
//      Assert::AreEqual(inside, (i == j) ? 1 : 0);
    }
    Serial.println();
  }
}

void loop() {
}
