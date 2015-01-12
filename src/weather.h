#pragma once

TextLayer   *s_weather_layer;
TextLayer   *s_weather_icon_layer;

void weather_main_window_load(Window *window);
void weather_main_window_unload(Window *window);

char weather_icon_2_char(char icon[]);

void weather_app_msg_recive(Tuple *t);
