/*
 * ColorDetector - Detect the color of a brick i a list of colors
 */
#ifndef ColorDetector_h
#define ColorDetector_h

#include <Arduino.h>

namespace ColorDetector {
/* color definition */
typedef int color[3]; /* RGB color values */
#define red(c)    c[0]
#define blue(c)   c[1]
#define green(c)  c[2]

/* List of values */
const int MAX_BRICKS=16;
color bricks[MAX_BRICKS] = {
  { 141, 198, 182 },  /*  0: blank */
  { 107, 163, 140 },  /*  1: black */
  { 172, 246, 233 },  /*  2: light grey */
  { 133, 194, 175 },  /*  3: dark grey */
  { 158, 229, 219 },  /*  4: light blue */
  { 131, 200, 183 },  /*  5: dark blue */
  { 317, 406, 397 },  /*  6: white */
  { 236, 307, 273 },  /*  7: light brown */
  { 162, 185, 146 },  /*  8: middle brown */
  { 141, 182, 156 },  /*  9: brown */
  { 149, 175, 149 },  /* 10: darker brown */
  { 158, 183, 155 },  /* 11: orange brown */
  { 178, 178, 159 },  /* 12: red */
  { 132, 167, 144 },  /* 13: red brown */
  { 121, 163, 139 },  /* 14: dark brown */
  { 136, 190, 164 }   /* 15: darkest brown */
};

int distance (color c1, color c2)
{
  int result = 0;
  result += abs(red(c2) - red(c1));
  result += abs(green(c2) - green(c1));
  result += abs(blue(c2) - blue(c1));
  return result;
}
int detect_limit = 10;
int detect(color ref, int limit=detect_limit) {
  int result = -1;
  int best = 256 + 256 + 256;
  for (int i = 0; i < MAX_BRICKS; i++) {
    int actual = distance(bricks[i], ref);
    if (actual > limit)
      continue;
    if (actual > best)
      continue;
     result = i;
     best = actual;
  }
  return result;
}
int detect(int r, int g, int b, int limit=detect_limit) {
  color ref;
  red(ref) = r; green(ref) = g; blue(ref) = b;
  return detect(ref, limit);
}
}
#endif
