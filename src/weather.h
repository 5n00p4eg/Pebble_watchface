#pragma once


void weather_main_window_load(Window *window);
void weather_main_window_unload(Window *window);

void weather_icon_2_char(char* ret, const char icon[]);

void weather_app_msg_recive(Tuple *t);
