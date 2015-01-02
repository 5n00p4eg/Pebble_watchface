#include <pebble.h>
#include "weather.h"
#include "layout.h"
  
void weather_main_window_load(Window *window) {
  //WEATHER
  s_weather_layer = text_layer_create(get_layout_rect(C_REG_WEATHER));
  s_weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_OPENSANS_REGULAR_20));
  text_layer_set_background_color(s_weather_layer, GColorBlack);
  text_layer_set_text_color(s_weather_layer, GColorWhite);
  text_layer_set_text_alignment(s_weather_layer, GTextAlignmentCenter);
  text_layer_set_font(s_weather_layer, s_weather_font);
  text_layer_set_text(s_weather_layer, "Loading...");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_weather_layer));
}


void weather_main_window_unload(Window *window) {
  text_layer_destroy(s_weather_layer);
  fonts_unload_custom_font(s_weather_font);
}