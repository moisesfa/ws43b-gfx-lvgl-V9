#include "ui_ex1.h"
#include <lvgl.h>
#include <Arduino_GFX_Library.h>

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}

void lv_example_button_1(void)
{
    lv_obj_t * label;

    lv_obj_t * btn1 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);
    lv_obj_remove_flag(btn1, LV_OBJ_FLAG_PRESS_LOCK);

    label = lv_label_create(btn1);
    lv_label_set_text(label, "Button");
    lv_obj_center(label);

    lv_obj_t * btn2 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_height(btn2, LV_SIZE_CONTENT);

    label = lv_label_create(btn2);
    lv_label_set_text(label, "Toggle");
    lv_obj_center(label);

}

void ui_example1(void)
{
    /* Option 1: Create a simple label
     * ---------------------
     */
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello Arduino, I'm LVGL!(V" GFX_STR(LVGL_VERSION_MAJOR) "." GFX_STR(LVGL_VERSION_MINOR) "." GFX_STR(LVGL_VERSION_PATCH) ")");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_example_button_1();
    
}

static void btn3_event_cb(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * label = (lv_obj_t*) lv_event_get_user_data(e);
  
  if(code == LV_EVENT_CLICKED) {
    static uint8_t counter = 0;
    counter++;
    lv_label_set_text_fmt(label, "Counter: %d", counter);
    LV_LOG_USER("Counter: %d", counter);
  }
  
}

void ui_example2(void)
{
// Create a Button 
  lv_obj_t * btn3 = lv_button_create(lv_screen_active());    
  lv_obj_set_size(btn3, 120, 50);                                  // Set the btn3 size
  lv_obj_align(btn3, LV_ALIGN_CENTER, 0, 0);
  
  // Add a label to the btn3
  lv_obj_t * btn3_label = lv_label_create(btn3);     
  lv_label_set_text(btn3_label, "Click here!");        // Set the labels text
  lv_obj_center(btn3_label);

  lv_obj_t * tl_counter = lv_label_create(lv_screen_active());
  lv_label_set_text(tl_counter, "Counter: 0");
  lv_obj_align(tl_counter, LV_ALIGN_BOTTOM_MID, 0, -70);

  /// Establece el tipo y tamaño de fuente. Más información: // https://docs.lvgl.io/master/overview/font.html
  static lv_style_t style_text_label; 
  lv_style_init(&style_text_label); 
  lv_style_set_text_font(&style_text_label, &lv_font_montserrat_34); 
  lv_obj_add_style(tl_counter, &style_text_label, 0);

  lv_obj_add_event_cb(btn3, btn3_event_cb, LV_EVENT_ALL, tl_counter);  // Assign a callback to the button
}
