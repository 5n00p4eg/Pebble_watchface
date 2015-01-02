#include <pebble.h>
#include "app_msg.h"
#include "layout.h"
#include "batt.h"
#include "weather.h"
#include "clock.h"

/*
TODO LIST:
* Add battery indicator
* Add weather icons.
*/
  
static Window      *s_main_window;

/*
 *  Every minute actions.  
 */
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
  app_msg_tick(tick_time, units_changed);
}

static void main_window_load(Window *window) {  
  time_main_window_load(window);
  weather_main_window_load(window);
}

static void main_window_unload(Window *window) {
  //Destroy time
  time_main_window_unload(window);
  //Destroy weather
  weather_main_window_unload(window);
  
}


static void init() {
  //Register callback for evey-minute running
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  batt_init();
  app_msg_init();
  
  s_main_window = window_create();
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_main_window, true);
  
  update_time();
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
  