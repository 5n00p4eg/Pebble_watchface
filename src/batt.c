#include <pebble.h>
#include "batt.h"
#include "layout.h"

// ??????? What to  do ? :)
#define C_BATT_ORIENT_A -1
#define C_BATT_ORIENT_PT 1
#define C_BATT_ORIENT_PB 2
#define C_BATT_ORIENT_PD C_BATT_ORIENT_PT
#define C_BATT_ORIENT_LL 3
#define C_BATT_ORIENT_LR 4
#define C_BATT_ORIENT_LD C_BATT_ORIENT_LL
#define C_BATT_ORIENT_S  C_BATT_ORIENT_PD
  
static Layer *batt_layer;
static BatteryChargeState batt_state;

struct batt_settings {
  struct spacing margin;
  struct spacing padding;
  int    orientation;
  GColor color_margin;
  GColor color_padding;
  GColor color_bounds;
  bool   term;
  int    outline_width;
  GColor outline_color;
  struct spacing outline_padding;
};

static struct batt_settings settings;

void battery_state_update(BatteryChargeState charge) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Update batt state");
  batt_state = charge;
  layer_mark_dirty(batt_layer);
}

void batt_init() {
  //Register callback for battery state changes.
  battery_state_service_subscribe(battery_state_update);
  
  settings.margin          = get_spacing_each(50, 10, 10, 10);
  settings.padding         = get_spacing_all(3);
  settings.orientation     = C_BATT_ORIENT_A; //Auto
  settings.color_margin    = GColorBlack;
  settings.color_padding   = GColorWhite;
  settings.color_bounds    = GColorWhite;
  settings.outline_width   = 3;
  settings.outline_color   = GColorBlack;
  settings.outline_padding = get_spacing_all(2);
  settings.term            = true;
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
  
  //Fill margin
  graphics_context_set_fill_color(ctx, settings.color_margin);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  //Update bounds after margin
  bounds = layout_make_padding(bounds, settings.margin);
  
  //Fill padding
  graphics_context_set_fill_color(ctx, settings.color_padding);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  //Update bounds after padding
  bounds = layout_make_padding(bounds, settings.padding);
  
  //TODO:Check for free space.  
  
  //Fill bounds
  graphics_context_set_fill_color(ctx, settings.color_bounds);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  
  //Select orientation
  if (settings.orientation == C_BATT_ORIENT_A) {
    if (bounds.size.w > bounds.size.h) {
      settings.orientation = C_BATT_ORIENT_LD;
    } else if (bounds.size.h > bounds.size.w) {
      settings.orientation = C_BATT_ORIENT_PD;
    } else {
      settings.orientation = C_BATT_ORIENT_S;
    }
  }
  
  //Outline
  GRect outline_rect = bounds;
  //GRect outline_rect = layout_make_padding(bounds; get_spacing_all(settings.outline_width));
  
  if (settings.term) {
    //TODO: Round corners
    int term_width  = 0;
    int term_height = 0;
    GRect term_rect;
    GAlign term_align;
    if (settings.orientation == C_BATT_ORIENT_PB || settings.orientation == C_BATT_ORIENT_PT) {
      term_width  = bounds.size.w / 3;  //TODO: Use smarter algorithm.
      term_height = bounds.size.h / 10;
    } else {
      term_height = bounds.size.h / 3;
      term_width = bounds.size.w / 10; 
    }
    term_rect = GRect(0,0, term_width, term_height);
    
    switch (settings.orientation) {
      case C_BATT_ORIENT_PT:
        term_align = GAlignTop;
        outline_rect = layout_make_padding(outline_rect, get_spacing_each(term_height, 0, 0, 0));
        break;
      case C_BATT_ORIENT_PB:
        term_align = GAlignBottom;
        outline_rect = layout_make_padding(outline_rect, get_spacing_each(0, term_height, 0, 0));
        break;
      case C_BATT_ORIENT_LL:
        term_align = GAlignLeft;
        outline_rect = layout_make_padding(outline_rect, get_spacing_each(0, 0, term_width, 0));
        break;
      case C_BATT_ORIENT_LR:
        term_align = GAlignRight;
        outline_rect = layout_make_padding(outline_rect, get_spacing_each(0, 0, 0, term_width));
        break;
      default:
        term_align = GAlignTop; //See C_BATT_ORIENT_D constant.
        outline_rect = layout_make_padding(outline_rect, get_spacing_each(term_height, 0, 0, 0));
    }
    grect_align(&term_rect, &bounds, term_align, true);
    APP_LOG(APP_LOG_LEVEL_INFO, "TERM_RECT: OX:%i, OY:%i, SW:%i, SH:%i", term_rect.origin.x, term_rect.origin.y, term_rect.size.w, term_rect.size.h);
    graphics_context_set_fill_color(ctx, settings.outline_color);
    //Todo: add option to select between fill and draw.
    graphics_fill_rect(ctx, term_rect, 0, GCornerNone);
    
  }
  
  //Make outline.
  // Enough space to show outline ?
  graphics_context_set_stroke_color (ctx, settings.outline_color);
  for (int i = settings.outline_width; i>0; i--) {
    graphics_draw_rect(ctx, outline_rect);
    outline_rect = layout_make_padding(outline_rect, get_spacing_all(1));
  }
  
  
  APP_LOG(APP_LOG_LEVEL_INFO, "BOUNDS: OX:%i, OY:%i, SW:%i, SH:%i", bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h);
  /*
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  */

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
  // width
  // height
  // Outline or not
  // Show text or bars.
  // Spaces between bars and outline.
  // Spaces between bars.
  // Coloring
  
  //Calculations
  // Enough space to make padding ?

  // Enough space tho show bars ?
  // How mny bars ?
  // bar size ?
  // Can show half bars ?
  
 
  //Draw outline
  
  //charge or not
  
  //Batt level
  // 0, 20, 40, 60, 80, 100 - Full rectangles
  // 10, 30, 50, 70, 90     - Half rectangles
  // Count full
  // Count half
  
  //Update layer.
}