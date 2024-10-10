#include "ui_ex3.h"
#include <lvgl.h>
#include <Arduino.h>

//***********************************
// EJERCICIO 1
//***********************************
/*
Obtener información del usuario mediante un teclado numérico.
Con esto, crearemos un locker básico que se puede usar para proteger la pantalla de usuarios no autorizados 
o realizar acciones solo si ingresa una contraseña específica.
*/
// Change this variable to set your unique pass code required to unlock the screen
String pass_code = "12345";

void lv_create_unlock_screen(void);

static void text_area_event_handler(lv_event_t * e) {
  lv_obj_t * text_area = (lv_obj_t*) lv_event_get_target(e);
  LV_UNUSED(text_area);
  LV_LOG_USER("Enter was pressed. The current text is: %s", lv_textarea_get_text(text_area));

  if(pass_code==String(lv_textarea_get_text(text_area))){
    Serial.println(int(lv_textarea_get_text(text_area)));
    lv_create_unlock_screen();
    LV_LOG_USER("Pass code is correct.");
  }
  else {
    lv_obj_t * msg_box = lv_msgbox_create(NULL);
    lv_msgbox_add_title(msg_box, "WRONG PASS CODE");
    lv_msgbox_add_close_button(msg_box);
    LV_LOG_USER("Wrong pass code. Try again.");
  }
}

static void button_matrix_event_handler(lv_event_t * e) {
  lv_obj_t * obj = (lv_obj_t*) lv_event_get_target(e);
  lv_obj_t * text_area = (lv_obj_t*) lv_event_get_user_data(e);
  const char * txt = lv_buttonmatrix_get_button_text(obj, lv_buttonmatrix_get_selected_button(obj));

  if(lv_strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) {
    lv_textarea_delete_char(text_area);
  }
  else if(lv_strcmp(txt, LV_SYMBOL_OK) == 0) {
    lv_obj_send_event(text_area, LV_EVENT_READY, NULL);
  }
  else {
    lv_textarea_add_text(text_area, txt);
  }
}

// Callback that is triggered when the toggle switch changes state
static void toggle_switch_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = (lv_obj_t*) lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
    LV_UNUSED(obj);
    LV_LOG_USER("State: %s", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
  }
}

void lv_create_ui_e3_1(void)
{
  // Clear screen
  lv_obj_clean(lv_scr_act());

  lv_obj_t * text_area = lv_textarea_create(lv_screen_active());
  lv_textarea_set_one_line(text_area, true);
  lv_obj_align(text_area, LV_ALIGN_TOP_MID, 0, 60);
  lv_textarea_set_password_mode(text_area, true);

  lv_obj_t * text_label = lv_label_create(lv_screen_active());
  lv_label_set_text(text_label, "ENTER PASS CODE TO UNLOCK");
  lv_obj_align_to(text_label, text_area, LV_ALIGN_TOP_MID, 0, -50);

  lv_obj_add_event_cb(text_area, text_area_event_handler, LV_EVENT_READY, text_area);
  lv_obj_add_state(text_area, LV_STATE_FOCUSED); // To be sure the cursor is visible

  static const char * keypad[]= {  "1", "2", "3", "\n",
                                   "4", "5", "6", "\n",
                                   "7", "8", "9", "\n",
                                   LV_SYMBOL_BACKSPACE, "0", LV_SYMBOL_OK, ""
                                };

  lv_obj_t * button_matrix = lv_buttonmatrix_create(lv_screen_active());
  lv_obj_set_size(button_matrix, 320, 320);
  lv_obj_align(button_matrix, LV_ALIGN_BOTTOM_MID, 0, -10);
  lv_obj_add_event_cb(button_matrix, button_matrix_event_handler, LV_EVENT_VALUE_CHANGED, text_area);
  lv_obj_remove_flag(button_matrix, LV_OBJ_FLAG_CLICK_FOCUSABLE); // To keep the text area focused on button clicks
  lv_buttonmatrix_set_map(button_matrix, keypad);

}

static void float_button_event_cb(lv_event_t * e) {
  lv_create_ui_e3_1();
}

void lv_create_unlock_screen(void) {
  // Clear screen
  lv_obj_clean(lv_scr_act());
  // Create a toggle switch (toggle_switch)
  lv_obj_t * toggle_switch = lv_switch_create(lv_screen_active());
  lv_obj_add_event_cb(toggle_switch, toggle_switch_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_flag(toggle_switch, LV_OBJ_FLAG_EVENT_BUBBLE);
  lv_obj_align(toggle_switch, LV_ALIGN_CENTER, 0, 0);

  // Create floating button
  lv_obj_t * float_button = lv_button_create(lv_screen_active());
  lv_obj_set_size(float_button, 40, 40);
  lv_obj_add_flag(float_button, LV_OBJ_FLAG_FLOATING);
  lv_obj_align(float_button, LV_ALIGN_BOTTOM_LEFT, 15, -15);
  lv_obj_add_event_cb(float_button, float_button_event_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_set_style_radius(float_button, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_bg_image_src(float_button, LV_SYMBOL_CLOSE, 0);
  lv_obj_set_style_text_font(float_button, lv_theme_get_font_large(float_button), 0);
  lv_obj_set_style_bg_color(float_button, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
}

