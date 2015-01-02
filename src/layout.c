#include <pebble.h>
#include "layout.h"

#define C_DISP_WIDTH  144
#define C_DIST_HEIGHT 168
GRect get_layout_rect(int region) {
  /*
   *  ___TIME___
   *  ___BAR____
   *  weat|_____
   *  her_|_____
   */
 
  switch (region) {
    case C_REG_CLOCK:
      return GRect(0, 0, 144, 44);
      break;
    case C_REG_BAR:
      return GRect(0, 45, 144, 24);
      break;
    case C_REG_WEATHER:
      return GRect(0, 70, 72, 100);
      break;
    default:
      return GRect(0, 0, 144, 168);
  }
}