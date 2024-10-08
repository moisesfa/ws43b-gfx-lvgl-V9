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
    const char degree_symbol[] = "\u00BAC";
  
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

  // Create a text label in font custom to display the latest temperature reading
  // https://youtu.be/YCTbiHk1MHM?si=hCYQegxFxTkBYObm
  // https://lvgl.io/tools/fontconverter
  
  lv_obj_t * text_label_temp_value = lv_label_create(lv_screen_active());
  lv_label_set_text(text_label_temp_value, "--.--");
  lv_obj_set_style_text_align(text_label_temp_value, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(text_label_temp_value, LV_ALIGN_CENTER, 0, 50);

  LV_FONT_DECLARE(lv_font_alibaba_sans_bold_120);
  static lv_style_t style_temp;
  lv_style_init(&style_temp);
  lv_style_set_text_font(&style_temp, &lv_font_alibaba_sans_bold_120);
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
// EJERCICIO 2
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

  String sim_humi_text = String(sim_humi) + "%";
  lv_label_set_text(text_label_humidity, sim_humi_text.c_str());
  Serial.print("Humidity: ");
  Serial.println(sim_humi_text);
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

//***********************************
// EJERCICIO 3
//***********************************
/*
Crear una tabla interactiva con LVGL con datos simulados. 
También mostraremos un botón flotante con el ícono de actualización que, al hacer clic, 
actualizará los valores de la tabla.
*/
float data_temp, data_humi, data_pres, data_lumi;

void get_data() {
  float randomDec, sim_humi;
  long randInt;
  
  randInt = random(0,50);   // a random integer from -90 to 90
  randomDec = random(0, 100) / 100.0; // a random decimal number from 0.00 to 0.99
  data_temp = randInt + randomDec; 
  
  randInt = random(0,100);   // a random integer from -90 to 90
  randomDec = random(0, 100) / 100.0; // a random decimal number from 0.00 to 0.99
  data_humi = randInt + randomDec; 
  
  randInt = random(80000,102400);   // a random integer from -90 to 90
  //randomDec = random(0, 100) / 100.0; // a random decimal number from 0.00 to 0.99
  data_pres = randInt + randomDec; 
  
  randInt = random(0,500);   // a random integer from -90 to 90
  randomDec = random(0, 100) / 100.0; // a random decimal number from 0.00 to 0.99
  data_lumi = randInt + randomDec; 

}

static lv_obj_t * table;

static void update_table_values(void) { 
  get_data();

  const char degree_symbol[] = "\u00B0C";
  
  String data_temp_value = String(data_temp) + degree_symbol;
  String data_humi_value = String(data_humi) + "%";
  String data_press_value = String(data_pres / 100.0F) + " hPa";
  String ldr_value = String(data_lumi);
  
  // Fill the first column
  lv_table_set_cell_value(table, 0, 0, "Data");
  lv_table_set_cell_value(table, 1, 0, "Temperature");
  lv_table_set_cell_value(table, 2, 0, "Humidity");
  lv_table_set_cell_value(table, 3, 0, "Pressure");
  lv_table_set_cell_value(table, 4, 0, "Luminosity");  
  // Fill the second column
  lv_table_set_cell_value(table, 0, 1, "Value");
  lv_table_set_cell_value(table, 1, 1, data_temp_value.c_str());
  lv_table_set_cell_value(table, 2, 1, data_humi_value.c_str());
  lv_table_set_cell_value(table, 3, 1, data_press_value.c_str());
  lv_table_set_cell_value(table, 4, 1, ldr_value.c_str());
}

static void float_button_event_cb(lv_event_t * e) {
  update_table_values();
}

static void draw_event_cb(lv_event_t * e) {
  
  lv_draw_task_t * draw_task = lv_event_get_draw_task(e);
  // #define LV_USE_PRIVATE_API		1  en archivo lv_conf.h
  lv_draw_dsc_base_t * base_dsc = (lv_draw_dsc_base_t*) draw_task->draw_dsc;
  // If the cells are drawn
  if(base_dsc->part == LV_PART_ITEMS) {
    uint32_t row = base_dsc->id1;
    uint32_t col = base_dsc->id2;

    // Make the texts in the first cell center aligned
    if(row == 0) {
      lv_draw_label_dsc_t * label_draw_dsc = lv_draw_task_get_label_dsc(draw_task);
      if(label_draw_dsc) {
        label_draw_dsc->align = LV_TEXT_ALIGN_CENTER;
        label_draw_dsc->font = &lv_font_montserrat_22;
        label_draw_dsc->color = lv_color_make(255, 255, 255);;
      }
      lv_draw_fill_dsc_t * fill_draw_dsc = lv_draw_task_get_fill_dsc(draw_task);
      if(fill_draw_dsc) {
        fill_draw_dsc->color = lv_color_mix(lv_palette_main(LV_PALETTE_BLUE), fill_draw_dsc->color, LV_OPA_100);
        fill_draw_dsc->opa = LV_OPA_COVER;
      }
    }
    // In the first column align the texts to the right
    else if(col == 0) {
      lv_draw_label_dsc_t * label_draw_dsc = lv_draw_task_get_label_dsc(draw_task);
      if(label_draw_dsc) {
        label_draw_dsc->align = LV_TEXT_ALIGN_CENTER;
        label_draw_dsc->font = &lv_font_montserrat_22;
        //label_draw_dsc->color = lv_palette_main(LV_PALETTE_BLUE);
        label_draw_dsc->color = lv_color_make(0, 0, 255);;

      }
    }
    else if(col == 1) {
      lv_draw_label_dsc_t * label_draw_dsc = lv_draw_task_get_label_dsc(draw_task);
      if(label_draw_dsc) {
        label_draw_dsc->align = LV_TEXT_ALIGN_CENTER;
        label_draw_dsc->font = &lv_font_montserrat_22;
      }
    }

    // Make every 2nd row gray color
    if((row != 0 && row % 2) == 0) {
      lv_draw_fill_dsc_t * fill_draw_dsc = lv_draw_task_get_fill_dsc(draw_task);
      if(fill_draw_dsc) {
        fill_draw_dsc->color = lv_color_mix(lv_palette_main(LV_PALETTE_GREY), fill_draw_dsc->color, LV_OPA_10);
        fill_draw_dsc->opa = LV_OPA_COVER;
      }
    }
  }
}

void lv_create_ui_e2_3(void) {
  table = lv_table_create(lv_screen_active());

  // Inserts or updates all table values
  update_table_values();

  // Set a smaller height to the table. It will make it scrollable
  lv_obj_set_style_pad_ver(table, 30, LV_PART_ITEMS);
  lv_table_set_column_width(table, 0, 300);
  lv_table_set_column_width(table, 1, 300);
  lv_obj_set_height(table, 400);
  lv_obj_center(table);

  // Add an event callback to apply some custom drawing
  lv_obj_add_event_cb(table, draw_event_cb, LV_EVENT_DRAW_TASK_ADDED, NULL);
  lv_obj_add_flag(table, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);

  // Create floating button
  lv_obj_t * float_button = lv_button_create(lv_screen_active());
  lv_obj_set_size(float_button, 50, 50);
  lv_obj_add_flag(float_button, LV_OBJ_FLAG_FLOATING);
  lv_obj_align(float_button, LV_ALIGN_BOTTOM_RIGHT, -15, -15);
  lv_obj_add_event_cb(float_button, float_button_event_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_set_style_radius(float_button, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_bg_image_src(float_button, LV_SYMBOL_REFRESH, 0);
  lv_obj_set_style_text_font(float_button, lv_theme_get_font_large(float_button), 0);
  lv_obj_set_style_bg_color(float_button, lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN);
}

//***********************************
// EJERCICIO 4
//***********************************
/*
Dibujar un gráfico de líneas para mostrar los datos de un sensor. 
Mostraremos la temperatura de un sensor simulado.
• El gráfico muestra un máximo de 20 puntos de datos.
• Cuando se agrega un nuevo punto a la pantalla, se elimina el punto de datos más antiguo.
• El rango del eje vertical se ajustará automáticamente según los valores actuales trazados en el gráfico.
• Puede tocar junto a los puntos de datos para verificar el valor preciso de un punto;se dibujará una etiqueta con su valor junto a él.
*/
#define SIM_NUM_READINGS 20
float sim_last_readings[SIM_NUM_READINGS] = {-20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0};
float scale_min_temp;
float scale_max_temp;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

// Draw a label on that chart with the value of the pressed point
static void chart_draw_label_cb(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * chart = (lv_obj_t*) lv_event_get_target(e);

  if(code == LV_EVENT_VALUE_CHANGED) {
    lv_obj_invalidate(chart);
  }
  if(code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
    int32_t * s = (int32_t*)lv_event_get_param(e);
    *s = LV_MAX(*s, 20);
  }
  // Draw the label on the chart based on the pressed point
  else if(code == LV_EVENT_DRAW_POST_END) {
    int32_t id = lv_chart_get_pressed_point(chart);
    if(id == LV_CHART_POINT_NONE) return;

    LV_LOG_USER("Selected point %d", (int)id);

    lv_chart_series_t * ser = lv_chart_get_series_next(chart, NULL);
    while(ser) {
      lv_point_t p;
      lv_chart_get_point_pos_by_id(chart, ser, id, &p);

      int32_t * y_array = lv_chart_get_y_array(chart, ser);
      int32_t value = y_array[id];
      char buf[16];
      const char degree_symbol[] = "\u00B0C";

      // Preparing the label text for the selected data point
      //#define LV_USE_FLOAT            1 en lv_con.h
      lv_snprintf(buf, sizeof(buf), LV_SYMBOL_DUMMY " %3.2f %s ", float(sim_last_readings[id]), degree_symbol);

      // Draw the rectangular label that will display the temperature value
      lv_draw_rect_dsc_t draw_rect_dsc;
      lv_draw_rect_dsc_init(&draw_rect_dsc);
      draw_rect_dsc.bg_color = lv_color_black();
      draw_rect_dsc.bg_opa = LV_OPA_60;
      draw_rect_dsc.radius = 2;
      draw_rect_dsc.bg_image_src = buf;
      draw_rect_dsc.bg_image_recolor = lv_color_white();
      // Rectangular label size
      lv_area_t a;
      a.x1 = chart->coords.x1 + p.x - 35;
      a.x2 = chart->coords.x1 + p.x + 35;
      a.y1 = chart->coords.y1 + p.y - 30;
      a.y2 = chart->coords.y1 + p.y - 10;
      lv_layer_t * layer = lv_event_get_layer(e);
      lv_draw_rect(layer, &draw_rect_dsc, &a);
      ser = lv_chart_get_series_next(chart, ser);
    }
  }
  else if(code == LV_EVENT_RELEASED) {
    lv_obj_invalidate(chart);
  }
}

// Get the latest SIM readings
void get_sim_readings(void) {
  
  float randomDec, sim_temp;
  long randInt;
  randInt = random(-20,120);   // a random integer from -90 to 90
  randomDec = random(0, 100) / 100.0; // a random decimal number from 0.00 to 0.99
  sim_temp = randInt + randomDec; 
 
  // Reset scale range (chart y axis) variables
  scale_min_temp = 120.0;
  scale_max_temp = -20.0;

  // Shift values to the left of the array and inserts the latest reading at the end
  for (int i = 0; i < SIM_NUM_READINGS; i++) {
    if(i == (SIM_NUM_READINGS-1) && float(sim_temp) < 120.0) {
      sim_last_readings[i] = float(sim_temp);  // Inserts the new reading at the end
    }
    else {
      sim_last_readings[i] = float(sim_last_readings[i + 1]);  // Shift values to the left of the array
    }
    // Get the min/max value in the array to set the scale range (chart y axis)
    if((float(sim_last_readings[i]) < scale_min_temp) && (float(sim_last_readings[i]) != -20.0 )) {
      scale_min_temp = sim_last_readings[i];
    }
    if((float(sim_last_readings[i]) > scale_max_temp) && (float(sim_last_readings[i]) != -20.0 )) {
      scale_max_temp = sim_last_readings[i];
    }
  }
  Serial.print("Min temp: ");
  Serial.println(float(scale_min_temp));
  Serial.print("Max temp: ");
  Serial.println(float(scale_max_temp));
  Serial.print("SIM last reading: ");
  Serial.println(float(sim_last_readings[SIM_NUM_READINGS-1]));
  lv_create_ui_e2_4();
}

static void float_button_char_event_cb(lv_event_t * e) {
  get_sim_readings();
}

// Draw chart
void lv_create_ui_e2_4(void) {
  // Clear screen
  lv_obj_clean(lv_scr_act());

  // Create a a text label aligned on top
  lv_obj_t * label = lv_label_create(lv_screen_active());
  lv_label_set_text(label, "SIM Temperature Readings");
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

  // Create a container to display the chart and scale
  lv_obj_t * container_row = lv_obj_create(lv_screen_active());
  lv_obj_set_size(container_row, SCREEN_WIDTH-20,  SCREEN_HEIGHT-40);
  lv_obj_align(container_row, LV_ALIGN_BOTTOM_MID, 0, -10);
  // Set the container in a flexbox row layout aligned center
  lv_obj_set_flex_flow(container_row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(container_row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

  // Create a chart
  lv_obj_t * chart = lv_chart_create(container_row);
  lv_obj_set_size(chart, SCREEN_WIDTH-90, SCREEN_HEIGHT-70);
  lv_chart_set_point_count(chart, SIM_NUM_READINGS);
  lv_obj_add_event_cb(chart, chart_draw_label_cb, LV_EVENT_ALL, NULL);
  lv_obj_refresh_ext_draw_size(chart);

  // Add a data series
  lv_chart_series_t * chart_series = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);

  for(int i = 0; i < SIM_NUM_READINGS; i++) {
    if(float(sim_last_readings[i]) != -20.0) { // Ignores default array values
      // Set points in the chart and scale them with an *100 multiplier to remove the 2 floating-point numbers
      chart_series->y_points[i] = float(sim_last_readings[i]) * 100;
    }
  }
  // Set the chart range and also scale it with an *100 multiplier to remove the 2 floating-point numbers
  lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, int(scale_min_temp-1)*100, int(scale_max_temp+1)*100);
  lv_chart_refresh(chart); // Required to update the chart with the new values

  // Create a scale (y axis for the temperature) aligned vertically on the right
  lv_obj_t * scale = lv_scale_create(container_row);
  lv_obj_set_size(scale, 15, SCREEN_HEIGHT-90);
  lv_scale_set_mode(scale, LV_SCALE_MODE_VERTICAL_RIGHT);
  lv_scale_set_label_show(scale, true);
  // Set the scale ticks count 
  lv_scale_set_total_tick_count(scale, int(scale_max_temp+2) - int(scale_min_temp-1));
  if((int(scale_max_temp+2) - int(scale_min_temp-1)) < 10) {
    lv_scale_set_major_tick_every(scale, 1); // set y axis to have 1 tick every 1 degree
  }
  else {
    lv_scale_set_major_tick_every(scale, 10); // set y axis to have 1 tick every 10 degrees
  }
  // Set the scale style and range
  lv_obj_set_style_length(scale, 5, LV_PART_ITEMS);
  lv_obj_set_style_length(scale, 10, LV_PART_INDICATOR);
  lv_scale_set_range(scale, int(scale_min_temp-1), int(scale_max_temp+1));

  // Create floating button
  lv_obj_t * float_button = lv_button_create(lv_screen_active());
  lv_obj_set_size(float_button, 50, 50);
  lv_obj_add_flag(float_button, LV_OBJ_FLAG_FLOATING);
  lv_obj_align(float_button, LV_ALIGN_BOTTOM_RIGHT, -15, -15);
  lv_obj_add_event_cb(float_button, float_button_char_event_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_set_style_radius(float_button, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_bg_image_src(float_button, LV_SYMBOL_REFRESH, 0);
  lv_obj_set_style_text_font(float_button, lv_theme_get_font_large(float_button), 0);
  lv_obj_set_style_bg_color(float_button, lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN);
}