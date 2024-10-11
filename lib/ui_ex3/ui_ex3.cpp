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
// Cambio de la fuente por defecto en archivo lv_conf.h para que todo se vea mas grande
/*Always set a default font*/
//#define LV_FONT_DEFAULT &lv_font_montserrat_30


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
    lv_obj_set_size(msg_box, 500, 45);
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
  lv_obj_align_to(text_label, text_area, LV_ALIGN_TOP_MID, 0, -60);

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

//***********************************
// EJERCICIO 2
//***********************************
/*
Crear un cuadro de selección para la entrada del usuario. En el cuadro de selección, 
insertará un valor de temperatura umbral. Ese valor umbral determinará el estado de una salida. 
Puede usar este proyecto como punto de partida para construir un termostato.
*/
#define TEMP_THRES_MIN -10
#define TEMP_THRES_MAX 40
#define TEMP_THRES_DEFAULT 25

float current_thres = TEMP_THRES_DEFAULT;

static lv_obj_t * spinbox;

static void lv_spinbox_increment_event_cb(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
    lv_spinbox_increment(spinbox);
  }
  current_thres = (float)lv_spinbox_get_value(spinbox);
}

static void lv_spinbox_decrement_event_cb(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
    lv_spinbox_decrement(spinbox);
  }
  current_thres = (float)lv_spinbox_get_value(spinbox);
}

// Set the temperature value in the text label
static void set_temp(void * text_label_temp_value, int32_t v) {
  
  // Get the latest temperature reading in Celsius 
  float randomDec, sim_temp;
  long randInt;
  randInt = random(-10,40);   // a random integer from -90 to 90
  randomDec = random(0, 100) / 100.0; // a random decimal number from 0.00 to 0.99
  sim_temp = randInt + randomDec;

    //float bme_temp = bme.readTemperature();
    if(sim_temp <= 10.0) {
      lv_obj_set_style_text_color((lv_obj_t*) text_label_temp_value, lv_palette_main(LV_PALETTE_BLUE), 0);
    }
    else if(sim_temp > 10.0 && sim_temp <= 29.0) {
      lv_obj_set_style_text_color((lv_obj_t*) text_label_temp_value, lv_palette_main(LV_PALETTE_GREEN), 0);
    }
    else {
      lv_obj_set_style_text_color((lv_obj_t*) text_label_temp_value, lv_palette_main(LV_PALETTE_RED), 0);
    }
  
  if(int(sim_temp) >= current_thres) {
    LV_LOG_USER("Threshold value %d <= sim_temp", (int)current_thres);
    //digitalWrite(PIN, HIGH);
  }
  else {
    LV_LOG_USER("Threshold value %d < sim_temp", (int)current_thres);
    //digitalWrite(PIN, LOW);
  }
  
  const char degree_symbol[] = "\u00BAC";
 
  String sim_temp_text = String(sim_temp) + degree_symbol;
  lv_label_set_text((lv_obj_t*) text_label_temp_value, sim_temp_text.c_str());
  Serial.print("Temperature: ");
  Serial.println(sim_temp_text);
}

void lv_create_ui_e3_2(void)
{
 // Create a text label "TEMPERATURE"
  lv_obj_t * text_label_temp = lv_label_create(lv_screen_active());
  lv_label_set_text(text_label_temp, "TEMPERATURE");
  lv_obj_set_style_text_align(text_label_temp, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(text_label_temp, LV_ALIGN_TOP_MID, 0, 40);

  // Create a text label in font size 36 to display the latest temperature reading
  lv_obj_t * text_label_temp_value = lv_label_create(lv_screen_active());
  lv_label_set_text(text_label_temp_value, "--.--");
  lv_obj_set_style_text_align(text_label_temp_value, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(text_label_temp_value, LV_ALIGN_CENTER, 0, -50);

  LV_FONT_DECLARE(lv_font_alibaba_sans_bold_160);
  static lv_style_t style_temp;
  lv_style_init(&style_temp);
  lv_style_set_text_font(&style_temp, &lv_font_alibaba_sans_bold_160);
  lv_obj_add_style(text_label_temp_value, &style_temp, 0);

  // Create an animation to update the text label with the latest temperature value every 10 seconds
  lv_anim_t a_temp;
  lv_anim_init(&a_temp);
  lv_anim_set_exec_cb(&a_temp, set_temp);
  lv_anim_set_duration(&a_temp, 1000000);
  lv_anim_set_playback_duration(&a_temp, 1000000);
  lv_anim_set_var(&a_temp, text_label_temp_value);
  lv_anim_set_values(&a_temp, 0, 100);
  lv_anim_set_repeat_count(&a_temp, LV_ANIM_REPEAT_INFINITE);
  lv_anim_start(&a_temp);

  // Create a text label "SET THRESHOLD"
  lv_obj_t * text_label_threshold = lv_label_create(lv_screen_active());
  lv_label_set_text(text_label_threshold, "SET THRESHOLD");
  lv_obj_set_style_text_align(text_label_threshold, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(text_label_threshold, LV_ALIGN_CENTER, 0, 80);
  // Create a spinbox
  spinbox = lv_spinbox_create(lv_screen_active());
  lv_spinbox_set_range(spinbox, TEMP_THRES_MIN, TEMP_THRES_MAX);
  lv_spinbox_set_digit_format(spinbox, 2, 0);
  lv_spinbox_step_prev(spinbox);
  lv_spinbox_set_cursor_pos(spinbox, 0);
  lv_spinbox_set_value(spinbox, TEMP_THRES_DEFAULT);
  lv_obj_set_width(spinbox, 120);
  //lv_obj_set_height(spinbox, 100);
  lv_obj_set_style_text_font(spinbox, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_align(spinbox, LV_ALIGN_BOTTOM_MID, 0, -40);
  LV_LOG_USER("Threshold value %d", (int)lv_spinbox_get_value(spinbox));

  // Create two buttons to increment or decrement the threshold value
  int32_t spinbox_height = lv_obj_get_height(spinbox);
  lv_obj_t * button = lv_button_create(lv_screen_active());
  lv_obj_set_size(button, spinbox_height*2, spinbox_height);
  lv_obj_align_to(button, spinbox, LV_ALIGN_OUT_RIGHT_BOTTOM, 5, 0);
  lv_obj_set_style_bg_image_src(button, LV_SYMBOL_PLUS, 0);
  lv_obj_add_event_cb(button, lv_spinbox_increment_event_cb, LV_EVENT_ALL,  NULL);
  button = lv_button_create(lv_screen_active());
  lv_obj_set_size(button, spinbox_height*2, spinbox_height);
  lv_obj_align_to(button, spinbox, LV_ALIGN_OUT_LEFT_BOTTOM, -5, 0);
  lv_obj_set_style_bg_image_src(button, LV_SYMBOL_MINUS, 0);
  lv_obj_add_event_cb(button, lv_spinbox_decrement_event_cb, LV_EVENT_ALL, NULL);
}
