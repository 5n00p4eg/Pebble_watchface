#include <pebble.h>
#include "date.h"
#include "layout.h"

static Layer      *date_layer;
static TextLayer  *date_text_layer;

void date_update() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  static char buffer[20] = "";
  strftime(buffer, sizeof(buffer), "%a, %D", tick_time);
  
  text_layer_set_text(date_text_layer, buffer);
}

void date_main_window_load(Window *window) {
  date_layer = layer_create(get_layout_rect(C_REG_DATE));
  date_text_layer = text_layer_create(layer_get_bounds(date_layer));
  
  text_layer_set_text_alignment(date_text_layer, GTextAlignmentCenter );  

  layer_add_child(date_layer, text_layer_get_layer(date_text_layer));
  layer_add_child(window_get_root_layer(window), date_layer);

}
void date_main_window_unload(Window *window) {
  text_layer_destroy(date_text_layer);
  layer_destroy(date_layer);
}

void date_tick(struct tm *tick_time, TimeUnits units_changed) {
  if (units_changed == DAY_UNIT) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "DAY CHANGED");
    date_update();
  }
}



void date_init() {
  date_update();
}
