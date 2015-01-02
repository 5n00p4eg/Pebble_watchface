#pragma once

#define KEY_TEMPERATURE 0 //TODO: Think about location of this definition.
#define KEY_CONDITIONS 1  //TODO: Think about location of this definition.
  
void app_msg_init();
void app_msg_deinit();

void app_msg_tick(struct tm *tick_time, TimeUnits units_changed);