#include "ui_ex2.h"
#include <lvgl.h>
#include <Arduino.h>

//***********************************
//EJERCICIO 1
//***********************************
/* Mostraremos la temperatura del sensor SIMULADO en la pantalla mediante una etiqueta de texto. 
El color del texto variará según el rango de temperatura:

• Temperatura < 10°C (50°F): la temperatura se mostrará en color azul;
• 10°C (50°F) < temperatura < 29°C (84,2°F): la temperatura se mostrará en color verde;
• temperatura > 29°C (84,2°F): la temperatura se mostrará en color rojo.
*/
// Set the temperature value in the bar and text label
static void set_temp(void * text_label_temp_value, int32_t v) {
  // Get the latest temperature reading in Celsius or Fahrenheit
    float randomDec, sim_temp;
    long randInt;
    randInt = random(0,50);   // a random integer from -90 to 90
    randomDec = random(0, 100) / 100.0; // a random decimal number from 0.00 to 0.99
    sim_temp = randInt + randomDec; 

    //loat sim_temp = 1.0 * random(0, 50);
    if (sim_temp <= 10.0) {
      lv_obj_set_style_text_color((lv_obj_t*) text_label_temp_value, lv_palette_main(LV_PALETTE_BLUE), 0);
    }
    else if(sim_temp > 10.0 && sim_temp <= 29.0) {
      lv_obj_set_style_text_color((lv_obj_t*) text_label_temp_value, lv_palette_main(LV_PALETTE_GREEN), 0);
    }
    else {
      lv_obj_set_style_text_color((lv_obj_t*) text_label_temp_value, lv_palette_main(LV_PALETTE_RED), 0);
    }
    const char degree_symbol[] = "\u00B0F";
  
  String sim_temp_text = String(sim_temp) + degree_symbol;
  lv_label_set_text((lv_obj_t*) text_label_temp_value, sim_temp_text.c_str());
  Serial.print("Temperature: ");
  Serial.println(sim_temp_text);
}

void lv_create_ui_e2_1(void)
{
// Create a text label "TEMPERATURE"
  lv_obj_t * text_label_temp = lv_label_create(lv_screen_active());
  lv_label_set_text(text_label_temp, "TEMPERATURE");
  lv_obj_set_style_text_align(text_label_temp, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(text_label_temp, LV_ALIGN_CENTER, 0, -50);

  static lv_style_t style_lb_temp;
  lv_style_init(&style_lb_temp);
  lv_style_set_text_font(&style_lb_temp, &lv_font_montserrat_32);
  lv_obj_add_style(text_label_temp, &style_lb_temp, 0);

  // Create a text label in font size 36 to display the latest temperature reading
  lv_obj_t * text_label_temp_value = lv_label_create(lv_screen_active());
  lv_label_set_text(text_label_temp_value, "--.--");
  lv_obj_set_style_text_align(text_label_temp_value, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(text_label_temp_value, LV_ALIGN_CENTER, 0, 30);

  static lv_style_t style_temp;
  lv_style_init(&style_temp);
  lv_style_set_text_font(&style_temp, &lv_font_montserrat_48);
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
}