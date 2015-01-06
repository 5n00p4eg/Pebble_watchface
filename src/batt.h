#pragma once
#include <pebble.h>
#include "layout.h"
  
struct batt_settings {
  struct spacing margin;
  struct spacing padding;
  int    orientation;
  GColor color_margin;
  GColor color_padding;
  GColor color_bounds;
  bool   term;
  int    outline_width;
  GColor outline_color;
  struct spacing outline_padding;
};  
  
void battery_state_update(BatteryChargeState charge);

void batt_init();
void batt_deinit();

void batt_set_settings(struct batt_settings sets);
struct batt_settings batt_get_settings();
struct batt_settings batt_get_default_settings();

void batt_main_window_load(Window *window);
void batt_main_window_unload(Window *window);
void batt_layer_draw(struct Layer *layer, GContext *ctx);