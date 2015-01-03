#pragma once

#define C_REG_CLOCK   0
#define C_REG_BAR     1
#define C_REG_WEATHER 2
#define C_REG_SPACE   3

GRect get_layout_rect(int region);


//This struct can be used for some paddigs, pargins etc.
struct spacing {
  int top;
  int bottom;
  int left;
  int rigth;
};

struct spacing get_spacing_all(int all_spacing);
struct spacing get_spacing_duo(int vert_spacing, int hor_spacing);
struct spacing get_spacing_each(int top_spacing, int bot_spacing, int left_spacing, int right_spacing);

GRect layout_make_padding(GRect base, struct spacing padding);
