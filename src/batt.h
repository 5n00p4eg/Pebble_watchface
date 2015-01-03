#pragma once


void battery_state_update(BatteryChargeState charge);

void batt_init();
void batt_deinit();

void batt_main_window_load(Window *window);
void batt_main_window_unload(Window *window);
void batt_layer_draw(struct Layer *layer, GContext *ctx);