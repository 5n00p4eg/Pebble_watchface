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
    case C_REG_WEATHER:
      return GRect(0, 70, 72, 40);
      break;
    case C_REG_WEATHER_ICON:
      return GRect(0, 110, 72, 168-110);
      break;
    case C_REG_SPACE:
      return GRect(72,70,72,100);
      break;
    case C_REG_DATE:
      return GRect(0, 44, 144, 24);
      break;
    default:
      return GRect(0, 0, 144, 168);
      break;
  }
}


struct spacing get_spacing_all(int all_spacing) {
  struct spacing res =  {all_spacing, all_spacing, all_spacing, all_spacing };
  return res;
}
struct spacing get_spacing_duo(int vert_spacing, int hor_spacing) {
  struct spacing res = {vert_spacing, vert_spacing, hor_spacing, hor_spacing };
  return res;
}
struct spacing get_spacing_each(int top_spacing, int bot_spacing, int left_spacing, int right_spacing) {
  struct spacing res = { top_spacing, bot_spacing, left_spacing, right_spacing };
  return res;
}


GRect layout_make_padding(GRect base, struct spacing padding) {
  int x   = base.origin.x + padding.left;
  int y   = base.origin.y + padding.top;
  int w   = base.size.w   - padding.left - padding.right;
  int h   = base.size.h   - padding.top  - padding.bottom;
  return GRect(x, y, w, h);
}
