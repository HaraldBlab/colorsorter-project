/*
  ColorSorter_ColorMapper - Color Mapper tests
*/

#include "ColorMapper.h"

namespace Assert {
  int num_ok = 0;
  int num_fail = 0;
  int num_total = 0;

  int stats(int result) {
    if (result) num_ok++; else num_fail++;
    num_total++;
  }
  int Validate(int result) {
    stats(result);
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
  for (int i = 0; i < ColorMapper::MAX_BRICKS; i++) {
    int brick = ColorMapper::detect(ColorMapper::bricks[i]);
    Serial.print("brick = ");
    Serial.println(brick);
    Assert::AreEqual(brick, i);
  }
  
  Serial.println("Verifying unknown colors");
  int brick = ColorMapper::detect(17, 217, 117);
  Serial.print("brick = ");
  Serial.println(brick);
  Assert::AreEqual(brick, -1);

  Serial.println("Verifying colors in brick limit");
  for (int i = 0; i < ColorMapper::MAX_BRICKS; i++) {
    ColorMapper::color ref;
    red(ref) = 3 + red(ColorMapper::bricks[i]);
    green(ref) = 3 + green(ColorMapper::bricks[i]);
    blue(ref) = 3 + blue(ColorMapper::bricks[i]);
    int brick = ColorMapper::detect(ref);
    Serial.print("brick = ");
    Serial.println(brick);
    Assert::AreEqual(brick, i);
  }

  Serial.println("Verifying colors outside brick limit");
  for (int i = 0; i < ColorMapper::MAX_BRICKS; i++) {
    ColorMapper::color ref;
    red(ref) = 4 + red(ColorMapper::bricks[i]);
    green(ref) = 4 + green(ColorMapper::bricks[i]);
    blue(ref) = 4 + blue(ColorMapper::bricks[i]);
    int brick = ColorMapper::detect(ref);
    Serial.print("brick = ");
    Serial.println(brick);
    Assert::AreEqual(brick, -1);
  }

  Serial.println("Verifying brick colors distance");
  for (int i = 0; i < ColorMapper::MAX_BRICKS; i++) {
    for (int j = 0; j < ColorMapper::MAX_BRICKS; j++) {
      int distance = ColorMapper::distance(ColorMapper::bricks[i], ColorMapper::bricks[j]);
      int inside = distance < ColorMapper::detect_limit;
      Serial.print(inside ? " X " : " . ");
//      Assert::AreEqual(inside, (i == j) ? 1 : 0);
    }
    Serial.println();
  }

  /* overall statistics */
  Serial.print("total : "); Serial.println(Assert::num_total);
  Serial.print("passed: "); Serial.println(Assert::num_ok);
  Serial.print("failed: "); Serial.println(Assert::num_fail);

}

void loop() {
}
