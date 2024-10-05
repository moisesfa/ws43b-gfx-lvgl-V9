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
    const char degree_symbol[] = "\u00B0C";
  
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

//***********************************
//EJERCICIO 2
//***********************************
/*
Mostraremos la temperatura y humedad simuladas, no sólo en etiquetas de texto 
sino también en barras verticales. 
*/

static lv_obj_t * text_label_temp_value;
// Set the temperature value in the bar and text label
static void set_temp_e2(void * bar, int32_t v) {
  
  float randomDec, sim_temp;
  long randInt;
  randInt = random(0,50);   // a random integer from -90 to 90
  randomDec = random(0, 100) / 100.0; // a random decimal number from 0.00 to 0.99
  sim_temp = randInt + randomDec;   
  const char degree_symbol[] = "\u00B0C";
  
  lv_bar_set_value((lv_obj_t*) bar, sim_temp, LV_ANIM_ON);
    
  String sim_temp_text = String(sim_temp) + degree_symbol;
  lv_label_set_text(text_label_temp_value, sim_temp_text.c_str());
  Serial.print("Temperature: ");
  Serial.println(sim_temp_text);
}

static lv_obj_t * text_label_humidity;
// Set the humidity value in the bar and text label
static void set_humi_e2(void * bar_humi, int32_t v) {
  // Get the latest humidity reading
  float randomDec, sim_humi;
  long randInt;
  randInt = random(0,100);   // a random integer from -90 to 90
  randomDec = random(0, 100) / 100.0; // a random decimal number from 0.00 to 0.99
  sim_humi = randInt + randomDec;   
 
  lv_bar_set_value((lv_obj_t*) bar_humi, sim_humi, LV_ANIM_ON);

  String bme_humi_text = String(sim_humi) + "%";
  lv_label_set_text(text_label_humidity, bme_humi_text.c_str());
  Serial.print("Humidity: ");
  Serial.println(bme_humi_text);
}


void lv_create_ui_e2_2(void)
{
  // Create a text label "TEMP."
  lv_obj_t * text_label_temp = lv_label_create(lv_screen_active());
  lv_label_set_long_mode(text_label_temp, LV_LABEL_LONG_WRAP);
  lv_label_set_text(text_label_temp, "TEMP.");
  lv_obj_set_width(text_label_temp, 150);
  lv_obj_set_style_text_align(text_label_temp, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(text_label_temp, LV_ALIGN_LEFT_MID, 30, -30);

  // Create a text label in font size 24 to display the latest temperature reading
  text_label_temp_value = lv_label_create(lv_screen_active());
  lv_label_set_long_mode(text_label_temp_value, LV_LABEL_LONG_WRAP);
  lv_label_set_text(text_label_temp_value, "--.--");
  lv_obj_set_width(text_label_temp_value, 150);
  lv_obj_set_style_text_align(text_label_temp_value, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(text_label_temp_value, LV_ALIGN_LEFT_MID, 30, 20);
  static lv_style_t style_temp;
  lv_style_init(&style_temp);
  lv_style_set_text_font(&style_temp, &lv_font_montserrat_24);
  lv_obj_add_style(text_label_temp_value, &style_temp, 0); 

  // Create a vertical bar aligned on the left side to display the temperature value
  static lv_style_t style_indic_temp;
  lv_style_init(&style_indic_temp);
  lv_style_set_bg_opa(&style_indic_temp, LV_OPA_COVER);
  lv_style_set_bg_color(&style_indic_temp, lv_palette_main(LV_PALETTE_RED));
  lv_style_set_bg_grad_color(&style_indic_temp, lv_palette_main(LV_PALETTE_LIGHT_BLUE));
  lv_style_set_bg_grad_dir(&style_indic_temp, LV_GRAD_DIR_VER);
  lv_obj_t * bar = lv_bar_create(lv_screen_active());
  lv_obj_add_style(bar, &style_indic_temp, LV_PART_INDICATOR);
  lv_obj_set_size(bar, 20, 200);
  lv_obj_align(bar, LV_ALIGN_LEFT_MID, 20, 0);
  lv_bar_set_range(bar, 0, 50);

  // Create an animation to update the bar and text label with the latest temperature value every 10 seconds
  lv_anim_t a_temp;
  lv_anim_init(&a_temp);
  lv_anim_set_exec_cb(&a_temp, set_temp_e2);
  lv_anim_set_duration(&a_temp, 1000000);
  lv_anim_set_playback_duration(&a_temp, 1000000);
  lv_anim_set_var(&a_temp, bar);
  lv_anim_set_values(&a_temp, 0, 50);
  lv_anim_set_repeat_count(&a_temp, LV_ANIM_REPEAT_INFINITE);
  lv_anim_start(&a_temp);

  // Create a text label "HUMI."
  lv_obj_t * text_label_humi = lv_label_create(lv_screen_active());
  lv_label_set_long_mode(text_label_humi, LV_LABEL_LONG_WRAP);    // Breaks the long lines
  lv_label_set_text(text_label_humi, "HUMI.");
  lv_obj_set_width(text_label_humi, 150);    // Set smaller width to make the lines wrap
  lv_obj_set_style_text_align(text_label_humi, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(text_label_humi, LV_ALIGN_CENTER, 90, -30);

  // Create a text label in font size 24 to display the latest humidity reading
  text_label_humidity = lv_label_create(lv_screen_active());
  lv_label_set_long_mode(text_label_humidity, LV_LABEL_LONG_WRAP);
  lv_label_set_text(text_label_humidity, "--.--");
  lv_obj_set_width(text_label_humidity, 150);
  lv_obj_set_style_text_align(text_label_humidity, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(text_label_humidity, LV_ALIGN_CENTER, 90, 20);
  static lv_style_t style_humi;
  lv_style_init(&style_humi);
  lv_style_set_text_font(&style_humi, &lv_font_montserrat_24);
  lv_obj_add_style(text_label_humidity, &style_humi, 0);

  // Create a vertical bar aligned on the right side to display the humidity value
  static lv_style_t style_indic_humi;
  lv_style_init(&style_indic_humi);
  lv_style_set_bg_opa(&style_indic_humi, LV_OPA_COVER);
  lv_style_set_bg_color(&style_indic_humi, lv_palette_main(LV_PALETTE_BLUE));
  lv_style_set_bg_grad_color(&style_indic_humi, lv_palette_main(LV_PALETTE_CYAN));
  lv_style_set_bg_grad_dir(&style_indic_humi, LV_GRAD_DIR_VER);
  lv_obj_t * bar_humi = lv_bar_create(lv_screen_active());
  lv_obj_add_style(bar_humi, &style_indic_humi, LV_PART_INDICATOR);
  lv_obj_set_size(bar_humi, 20, 200);
  lv_obj_align(bar_humi, LV_ALIGN_CENTER, 20, 0);
  lv_bar_set_range(bar_humi, 0, 100);

  // Create an animation to update the bar and text label with the latest humidity value every 10 seconds
  lv_anim_t a_humi;
  lv_anim_init(&a_humi);
  lv_anim_set_exec_cb(&a_humi, set_humi_e2);
  lv_anim_set_duration(&a_humi, 1000000);
  lv_anim_set_playback_duration(&a_humi, 1000000);
  lv_anim_set_var(&a_humi, bar_humi);
  lv_anim_set_values(&a_humi, 0, 100);
  lv_anim_set_repeat_count(&a_humi, LV_ANIM_REPEAT_INFINITE);
  lv_anim_start(&a_humi);

}
