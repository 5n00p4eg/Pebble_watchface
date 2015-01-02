#include <pebble.h>
#include "batt.h"

void battery_state_update(BatteryChargeState charge) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Update batt state");
}

void batt_init() {
  //Register callback for battery state changes.
  battery_state_service_subscribe(battery_state_update);
}

void batt_deinit() {
  battery_state_service_unsubscribe(); //TODO: MOVE TO batt module.
}