#include <pebble.h>
#include "weather.h"
#include "layout.h"
#include "app_msg.h"


TextLayer   *s_weather_layer;
TextLayer   *s_weather_icon_layer;

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
  s_weather_icons = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_WEATHER_42));
  s_weather_icon_layer = text_layer_create(get_layout_rect(C_REG_WEATHER_ICON));

  text_layer_set_font(s_weather_icon_layer, s_weather_icons);
  text_layer_set_text_color(s_weather_icon_layer, GColorBlack);
  text_layer_set_text(s_weather_icon_layer, "\uF03E");  
  
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
  

  // Update icon
  static char icon_char[4];
  weather_icon_2_char(icon_char, icon_buffer);
//text_layer_set_text(s_weather_icon_layer, icon_char);
  text_layer_set_text(s_weather_icon_layer, icon_char);
  
}

static bool str_eq(const char* f, const char* s) {
  if (strcmp(f,s) == 0 ) {
    return true;
  } else {
    return false;
  }
}

void weather_icon_2_char(char* ret, const char icon[]) {
  //TODO: Fill all codes from:
  //http://openweathermap.org/weather-conditions
  //
  APP_LOG(APP_LOG_LEVEL_INFO, "Conv str:%s", icon);
//  if (str_eq(icon, "02n")) { strcpy(ret, ""); return; }
  if (str_eq(icon, "01d"))                        { strcpy(ret, "\uF00D"); return; }
  if (str_eq(icon, "01n"))                        { strcpy(ret, "\uF02E"); return; }
  if (str_eq(icon, "02d"))                        { strcpy(ret, "\uF002"); return; }
  if (str_eq(icon, "02n"))                        { strcpy(ret, "\uF086"); return; }
  if (str_eq(icon, "03d") || str_eq(icon, "03n")) { strcpy(ret, "\uF041"); return; } 
  if (str_eq(icon, "04d") || str_eq(icon, "04n")) { strcpy(ret, "\uF013"); return; }
  if (str_eq(icon, "09d") || str_eq(icon, "09n")) { strcpy(ret, "\uF017"); return; }
  if (str_eq(icon, "10d"))                        { strcpy(ret, "\uF006"); return; }
  if (str_eq(icon, "10n"))                        { strcpy(ret, "\uF026"); return; }
  if (str_eq(icon, "11d") || str_eq(icon, "11n")) { strcpy(ret, "\uF01D"); return; }
  if (str_eq(icon, "13d") || str_eq(icon, "13n")) { strcpy(ret, "\uF01B"); return; }
  if (str_eq(icon, "50d") || str_eq(icon, "50n")) { strcpy(ret, "\uF014"); return; }

  strcpy(ret, "\uF03E");

  //strcpy(ret, "\uF040");
}
