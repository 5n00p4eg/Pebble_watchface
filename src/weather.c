#include <pebble.h>
#include "weather.h"
#include "layout.h"
#include "app_msg.h"


static GFont        s_weather_font;
static GFont        s_weather_icons;

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

  //Icon
  s_weather_icons = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_WEATHER_24));
  s_weather_icon_layer = text_layer_create(get_layout_rect(C_REG_WEATHER_ICON));

  text_layer_set_font(s_weather_icon_layer, s_weather_icons);
  text_layer_set_text_color(s_weather_icon_layer, GColorBlack);
  text_layer_set_text(s_weather_icon_layer, "\x03e, ....");  
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_weather_icon_layer));
}


void weather_main_window_unload(Window *window) {
  text_layer_destroy(s_weather_layer);
  fonts_unload_custom_font(s_weather_font);

  text_layer_destroy(s_weather_icon_layer);
  fonts_unload_custom_font(s_weather_icons);
}


void weather_app_msg_recive(Tuple *t) {
  // Store incoming information
  static char temperature_buffer[8];
  static char conditions_buffer[32];
  static char weather_layer_buffer[32];
  static char icon_buffer[5];

  switch(t->key) {
    case KEY_TEMPERATURE:
      snprintf(temperature_buffer, sizeof(temperature_buffer), "%dC", (int)t->value->int32);
      break;
    case KEY_CONDITIONS:
      snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
      break;
    case KEY_ICON:
      snprintf(icon_buffer, sizeof(icon_buffer), "%s", t->value->cstring);
      APP_LOG(APP_LOG_LEVEL_INFO, "Icon: %s", icon_buffer);
  } 

  // Assemble full string and display
  snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s, %s", temperature_buffer, conditions_buffer);
  text_layer_set_text(s_weather_layer, weather_layer_buffer);
}


char weather_icon_2_char(char icon[]) {
  char ret;

  if (strcmp(icon, "10n")) ret='\x019'; else
  if (strcmp(icon, "02n")) ret='\x031'; else ret='\?';

  return ret;
}


