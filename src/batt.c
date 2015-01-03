#include <pebble.h>
#include "batt.h"
#include "layout.h"

static Layer *batt_layer;
static BatteryChargeState batt_state;
  
void battery_state_update(BatteryChargeState charge) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Update batt state");
  batt_state = charge;
  layer_mark_dirty(batt_layer);
}

void batt_init() {
  //Register callback for battery state changes.
  battery_state_service_subscribe(battery_state_update);
}

void batt_deinit() {
  battery_state_service_unsubscribe(); //TODO: MOVE TO batt module.
}

//Build window

void batt_main_window_load(Window *window) {
  GRect frame = get_layout_rect(C_REG_SPACE); 
  batt_layer = layer_create(frame);
  layer_set_update_proc(batt_layer, batt_layer_draw);
  layer_add_child(window_get_root_layer(window), batt_layer);
}
void batt_main_window_unload(Window *window) {
  layer_destroy(batt_layer);
}

//Render battery
void batt_layer_draw(struct Layer *layer, GContext *ctx) {
  APP_LOG(APP_LOG_LEVEL_INFO, "BATT_LAYER_DRAW");
  //Get bounds for render area.
  GRect bounds = layer_get_bounds(layer);
  //Grab framebuffer
  //GBitmap *fb = graphics_capture_frame_buffer(ctx);
  
  APP_LOG(APP_LOG_LEVEL_INFO, "OX:%i, OY:%i, SW:%i, SH:%i", bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  
  //Push framebuffer
  //graphics_release_frame_buffer(ctx, fb);
}

void batt_render(BatteryChargeState charge) {
  // Ideally module can automatically define options based on avaliable space
  // Test cases:
  //  1x1 px
  //  1x168
  //  144x1
  //  10x168
  //  144x10
  //TODO: Add more cases.
  
  
  //Define geometry/options:
  // Padding
  // Orientation (auto/p/l);
  // width
  // height
  // Outline or not
  // Show text or bars.
  // Spaces between bars and outline.
  // Spaces between bars.
  // Coloring
  
  //Calculations
  // Enough space to make padding ?
  // Enough space to show outline ?
  // Enough space tho show bars ?
  // How mny bars ?
  // bar size ?
  // Can show half bars ?
  
  //BG
  
  //Draw outline
  
  //charge or not
  
  //Batt level
  // 0, 20, 40, 60, 80, 100 - Full rectangles
  // 10, 30, 50, 70, 90     - Half rectangles
  // Count full
  // Count half
  
  //Update layer.
}