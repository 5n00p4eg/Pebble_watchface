#include <pebble.h>
#include "app_msg.h"
#include "layout.h"
#include "batt.h"
#include "weather.h"
#include "clock.h"
#include "date.h"

/*
TODO LIST:
* Add weather icons.
*/
  
static Window      *s_main_window;

/*
 *  Every minute actions.  
 */
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time(); //TODO: Rename to clock_tick
  app_msg_tick(tick_time, units_changed);
  date_tick(tick_time, units_changed);
}

static void main_window_load(Window *window) {
  
  //TODO: Move layout date to this point, modules don't need to know where it's layer placed.
  time_main_window_load(window);
  date_main_window_load(window);
  batt_main_window_load(window);
  weather_main_window_load(window);
}

static void main_window_unload(Window *window) {
  //Destroy time
  time_main_window_unload(window);
  date_main_window_load(window);
  batt_main_window_unload(window);
  //Destroy weather
  weather_main_window_unload(window);
  
}


static void init() {
  //Register callback for evey-minute running
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  batt_init();
  //TODO: Set battery settings 
  struct batt_settings bat_sets = batt_get_default_settings();
  bat_sets.margin = get_spacing_each(1,1,1,3);
  bat_sets.color_margin = GColorWhite;
  batt_set_settings(bat_sets);
  app_msg_init();
  
  s_main_window = window_create();
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_main_window, true);
  
  update_time(); //TODO: Move to clock_init();
  
  date_init();
}

static void deinit() {
  window_destroy(s_main_window);
  
  tick_timer_service_unsubscribe();
  
  batt_deinit();
  app_msg_deinit();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
  
