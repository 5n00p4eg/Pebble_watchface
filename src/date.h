#pragma once


void date_main_window_load(Window *window);
void date_main_window_unload(Window *window);
void date_tick(struct tm *tick_time, TimeUnits units_changed);
void date_init();