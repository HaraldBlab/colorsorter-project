/*
 * ColorMapper - Maps the color of a brick to a list of colors
 */
#ifndef ColorDetector_h
#define ColorDetector_h

#include <Arduino.h>

namespace ColorMapper {
/* color definition */
typedef int color[3]; /* RGB color values */
/* TODO: this map is RBG and not RGB! */
#define red(c)    c[0]
#define green(c)  c[1]
#define blue(c)   c[2]

/*
 * Iron Man Set part list
 * LEGO plate round 1x1 black (4073)
 * see: https://www.bricklink.com/v2/search.page?q=614121#T=A
 * Color name and Id based in bricklink
 * 614126  :  11 : Black
 * 4523159 : 115 : Pearl Gold
 * 6021623 :  63 : Dark Blue
 * 6315782 :  68 : Dark Orange
 * 6315783 :  55 : Sand Blue
 * 6315781 :  69 : Dark Tan
 * 6314247 :  59 : Dark Red 
 * 4216581 :  88 : Reddish Brown
 * 4211525 :  86 : Light Bluish Gray
 * 4210633 :  85 : Dark Bluish Gray
 * 6315780 : 120 : Dark Brown
 * 6167641 : 150 : Medium Nougat 
 * 614101  :   1 : White
 * 4161734 :   2 : Tan 
 * 614121  :   5 : Red
 */
/* 
 *  This is the lego brick color mapping
 *  about colors: https://brickarchitect.com/color/
 *  color table: https://www.bricklink.com/catalogColors.asp
 *  color codes: https://rebrickable.com/colors/ 
 *               use the column 'bricklink' to get the values
 *  uses 'normalized' RGB colors
 *  
 *  TODO: somewhere I read that whize is (224, 224, 224)
 */
const int MAX_SET_COLORS=15;
const uint16_t setColors[MAX_SET_COLORS] = {
  0x05131D,  /*  1:   11 : Black */
  0x6C6E68,  /*  2:   85 : Dark Bluish Gray */
  0xA0A5A9,  /*  3:   86 : Light Bluish Gray */
  0x6074A1,  /*  4:   55 : Sand Blue*/
  0x0A3463,  /*  5:   63 : Dark Blue*/
  0xFFFFFF,  /*  6:    1 : White*/
  0xAA7F2E,  /*  7:  115 : Pearl Gold */
  0xE4CD9E,  /*  8:    2 : Tan  */
  0x958A73,  /*  9:   69 : Dark Tan */
  0xCC702A,  /* 10:  150 : Medium Nougat  */
  0xA95500,  /* 11:   68 : Dark Orange */
  0xC91A09,  /* 12:    5 : Red */
  0x720E0F,  /* 13:   59 : Dark Red   */
  0x582A12,  /* 14:   88 : Reddish Brown*/
  0x352100   /* 15:  120 : Dark Brown */
};

#define RED(x) (setColors[(x)] >> 16)
#define GREEN(x) ((setColors[(x)] >> 8) & 0x0000FF)
#define BLUE(x) (setColors[(x)] & 0x0000FF)

/* List of measured values (ambient lightning unknown! */
const int MAX_BRICKS=16;
color bricks[MAX_BRICKS] = {
  { 0, 0, 0 },  /*  0: blank */
  { RED( 0), GREEN( 0), BLUE( 0) },  /*  1:   11 : Black */
  { RED( 1), GREEN( 1), BLUE( 1) },  /*  2:   85 : Dark Bluish Gray */
  { RED( 2), GREEN( 2), BLUE( 2) },  /*  3:   86 : Light Bluish Gray */
  { RED( 3), GREEN( 3), BLUE( 3) },  /*  4:   55 : Sand Blue*/
  { RED( 4), GREEN( 4), BLUE( 4) },  /*  5:   63 : Dark Blue*/
  { RED( 5), GREEN( 5), BLUE( 5) },  /*  6:    1 : White*/
  { RED( 6), GREEN( 6), BLUE( 6) },  /*  7:  115 : Pearl Gold */
  { RED( 7), GREEN( 7), BLUE( 7) },  /*  8:    2 : Tan  */
  { RED( 8), GREEN( 8), BLUE( 8) },  /*  9:   69 : Dark Tan */
  { RED( 9), GREEN( 9), BLUE( 9) },  /* 10:  150 : Medium Nougat  */
  { RED(10), GREEN(10), BLUE(10) },  /* 11:   68 : Dark Orange */
  { RED(11), GREEN(11), BLUE(11) },  /* 12:    5 : Red */
  { RED(12), GREEN(12), BLUE(12) },  /* 13:   59 : Dark Red   */
  { RED(13), GREEN(13), BLUE(13) },  /* 14:   88 : Reddish Brown*/
  { RED(14), GREEN(14), BLUE(14) }   /* 15:  120 : Dark Brown */
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
