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

//***********************************
//EJERCICIO 1
//***********************************
/* El siguiente código creará un botón básico y una etiqueta de contador 
que aumentará cada vez que toque el botón.*/

static void event_handler_e1(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * label = (lv_obj_t*) lv_event_get_user_data(e);
  
  if(code == LV_EVENT_CLICKED) {
    static uint8_t counter = 0;
    counter++;
    lv_label_set_text_fmt(label, "Counter: %d", counter);
    LV_LOG_USER("Counter: %d", counter);
  }
  
}

void lv_create_ui_e1_1(void)
{
  // Create a Button 
  lv_obj_t * btn = lv_button_create(lv_screen_active());    
  lv_obj_set_size(btn, 220, 80);                                  // Set the btn3 size
  lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
  
  // Add a label to the btn3
  lv_obj_t * btn_label = lv_label_create(btn);     
  lv_label_set_text(btn_label, "Click here!");        // Set the labels text
  lv_obj_center(btn_label);

  lv_obj_t * tl_counter = lv_label_create(lv_screen_active());
  lv_label_set_text(tl_counter, "Counter: 0");
  lv_obj_align(tl_counter, LV_ALIGN_BOTTOM_MID, 0, -70);

  /// Establece el tipo y tamaño de fuente. Más información: // https://docs.lvgl.io/master/overview/font.html
  static lv_style_t style_text_label; 
  lv_style_init(&style_text_label); 
  lv_style_set_text_font(&style_text_label, &lv_font_montserrat_34); 
  lv_obj_add_style(tl_counter, &style_text_label, 0);

  lv_obj_add_event_cb(btn, event_handler_e1, LV_EVENT_ALL, tl_counter);  // Assign a callback to the button
}

//***********************************
//EJERCICIO 2
//***********************************
/* 
Un botón puede detectar diferentes tipos de eventos, no solo un evento del tipo hecho clic.
El siguiente código imprime el tipo de evento detectado por el botón en la pantalla.
*/

static void event_handler_e2(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * label = (lv_obj_t*) lv_event_get_user_data(e);

  switch(code) {
    case LV_EVENT_PRESSED:
      lv_label_set_text(label, "The last button event:\nLV_EVENT_PRESSED");
      break;
    case LV_EVENT_CLICKED:
      lv_label_set_text(label, "The last button event:\nLV_EVENT_CLICKED");
      break;
    case LV_EVENT_LONG_PRESSED:
      lv_label_set_text(label, "The last button event:\nLV_EVENT_LONG_PRESSED");
      break;
    case LV_EVENT_LONG_PRESSED_REPEAT:
      lv_label_set_text(label, "The last button event:\nLV_EVENT_LONG_PRESSED_REPEAT");
      break;
    default:
      break;
  }
}

void lv_create_ui_e1_2(void) {
  // Create a Button 
  lv_obj_t * button = lv_button_create(lv_screen_active());    
  lv_obj_set_size(button, 220, 80);                                  // Set the button size
  lv_obj_align(button, LV_ALIGN_CENTER, 0, -30);
  
  // Add a label to the button
  lv_obj_t * button_label = lv_label_create(button);     
  lv_label_set_text(button_label, "Click here!");        // Set the labels text
  lv_obj_center(button_label);

  lv_obj_t * text_label_event = lv_label_create(lv_screen_active());
  lv_label_set_text(text_label_event, "The last button event:\nNONE");
  lv_obj_align(text_label_event, LV_ALIGN_BOTTOM_MID, 0, -40);

  static lv_style_t style_text_label; 
  lv_style_init(&style_text_label); 
  lv_style_set_text_font(&style_text_label, &lv_font_montserrat_34); 
  lv_obj_add_style(text_label_event, &style_text_label, 0);

  lv_obj_add_event_cb(button, event_handler_e2, LV_EVENT_ALL, text_label_event);  // Assign a callback to the button
}


//***********************************
//EJERCICIO 3
//***********************************
/*
Tipos de botones: botones de dos estados e interruptores de palanca. 
Estos son útiles para encender o apagar algo y mostrar su estado al mismo tiempo.
*/

// Callback that is triggered when button is clicked/toggled
static void event_handler_bt_e3(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * button = (lv_obj_t*) lv_event_get_target(e);
  lv_obj_t * button_label = (lv_obj_t*) lv_event_get_user_data(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
    LV_UNUSED(button);
    LV_LOG_USER("State: %s", lv_obj_has_state(button, LV_STATE_CHECKED) ? "On" : "Off");
    lv_label_set_text_fmt(button_label, "Turn %s", lv_obj_has_state(button, LV_STATE_CHECKED) ? "Off" : "On");
  }
}

// Callback that is triggered when the toggle switch changes state
static void event_handler_ts_e3(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * toggle_switch = (lv_obj_t*) lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
    LV_UNUSED(toggle_switch);
    LV_LOG_USER("State: %s", lv_obj_has_state(toggle_switch, LV_STATE_CHECKED) ? "On" : "Off");
  }
}

void lv_create_ui_e1_3(void) {
  // Create a toggle button (button)
  lv_obj_t * button = lv_button_create(lv_screen_active());
  lv_obj_align(button, LV_ALIGN_CENTER, 0, -40);
  lv_obj_add_flag(button, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_set_height(button, LV_SIZE_CONTENT);
  lv_obj_t * button_label = lv_label_create(button);
  lv_label_set_text(button_label, "Turn On");
  lv_obj_center(button_label);
  lv_obj_add_event_cb(button, event_handler_bt_e3, LV_EVENT_ALL, button_label);
  
  // Create a toggle switch (toggle_switch)
  lv_obj_t * toggle_switch = lv_switch_create(lv_screen_active());
  lv_obj_add_event_cb(toggle_switch, event_handler_ts_e3, LV_EVENT_ALL, NULL);
  lv_obj_add_flag(toggle_switch, LV_OBJ_FLAG_EVENT_BUBBLE);
  lv_obj_align(toggle_switch, LV_ALIGN_CENTER, 0, 40);
}


//***********************************
//EJERCICIO 4
//***********************************
/*
Sabemos cómo crear botones y asociarles funciones de devolución de llamada. 
Los botones creados tienen los estilos LVGL predeterminados. Vamos  
a cambiar el estilo de los botones: color de fondo, ancho, alto, borde, etc.
*/

static lv_style_t style_button;
static lv_style_t style_button_pressed;

static lv_color_t darken(const lv_color_filter_dsc_t * dsc, lv_color_t color, lv_opa_t opa) {
  LV_UNUSED(dsc);
  return lv_color_darken(color, opa);
}

static void event_handler_e4(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * button = (lv_obj_t*) lv_event_get_target(e);
  lv_obj_t * button_label = lv_obj_get_child(button, 0);

  if(code == LV_EVENT_PRESSED) {
    lv_label_set_text(button_label, "Clicked");
    LV_LOG_USER("Button pressed");
  }
  else if(code == LV_EVENT_RELEASED) {
    lv_label_set_text(button_label, "Click here!");
    LV_LOG_USER("Button released");
  }
}

static void style_init(void) {
  // Create a simple button style: https://docs.lvgl.io/master/overview/style.html
  lv_style_init(&style_button);
  lv_style_set_radius(&style_button, 10);
  // Color documentation: https://docs.lvgl.io/master/overview/color.html
  lv_style_set_bg_opa(&style_button, LV_OPA_COVER);  // Set the opacity
  lv_style_set_bg_color(&style_button, lv_palette_lighten(LV_PALETTE_LIGHT_GREEN, 4));  // Set the background color
  // Set a light green background gradient color and direction
  lv_style_set_bg_grad_color(&style_button, lv_palette_main(LV_PALETTE_LIGHT_GREEN));
  lv_style_set_bg_grad_dir(&style_button, LV_GRAD_DIR_VER);

  // Set the border color, opacity, width, shadow (width, offset and opacity)
  lv_style_set_border_color(&style_button, lv_palette_main(LV_PALETTE_LIME));
  lv_style_set_border_opa(&style_button, LV_OPA_80);
  lv_style_set_border_width(&style_button, 2);
  lv_style_set_shadow_width(&style_button, 10);
  lv_style_set_shadow_offset_y(&style_button, 5);
  lv_style_set_shadow_opa(&style_button, LV_OPA_60);
  // Set the text color
  lv_style_set_text_color(&style_button, lv_color_hex(0x181717));

  // Create a style for the button pressed state
  // Use a color filter to simply modify all colors in this state and apply a dark effect
  static lv_color_filter_dsc_t color_filter;
  lv_color_filter_dsc_init(&color_filter, darken);
  lv_style_init(&style_button_pressed);
  lv_style_set_color_filter_dsc(&style_button_pressed, &color_filter);
  lv_style_set_color_filter_opa(&style_button_pressed, LV_OPA_10);
}

void lv_create_ui_e1_4(void) {
  // Initialize the style
  style_init();
  // Create a button and use the new styles
  lv_obj_t * button = lv_button_create(lv_screen_active());
  // Remove the styles coming from the default theme. Note that size and position are also stored as style properties
  // lv_obj_remove_style_all will remove the set size and position too 
  lv_obj_remove_style_all(button);
  lv_obj_set_size(button, 300, 100);
  lv_obj_add_style(button, &style_button, 0);
  lv_obj_add_style(button, &style_button_pressed, LV_STATE_PRESSED);
  lv_obj_align(button, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(button, event_handler_e4, LV_EVENT_ALL, NULL);  // Assign a callback to the button

  // Add a label to the button
  lv_obj_t * button_label = lv_label_create(button);
  lv_label_set_text(button_label, "Click here!");
  lv_obj_center(button_label);

  static lv_style_t style_text_label; 
  lv_style_init(&style_text_label); 
  lv_style_set_text_font(&style_text_label, &lv_font_montserrat_34); 
  lv_obj_add_style(button_label, &style_text_label, 0);

}

//***********************************
//EJERCICIO 5
//***********************************
/*
Crear y diseñar un control deslizante básico y a obtener su valor.
El rango del control deslizante va del 0 % al 100 %. Cuando mueves el control deslizante, 
la etiqueta de texto correspondiente se actualiza con el valor actual del control deslizante. 
*/

// Callback that prints the current slider value on the TFT display and Serial Monitor for debugging purposes
static void event_handler_e5(lv_event_t * e) {
  lv_obj_t * slider = (lv_obj_t*) lv_event_get_target(e);
  lv_obj_t * slider_label = (lv_obj_t*) lv_event_get_user_data(e);
  char buf[8];
  lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
  lv_label_set_text(slider_label, buf);
  LV_LOG_USER("Slider changed to %d%%", (int)lv_slider_get_value(slider));
}

void lv_create_ui_e1_5(void) {
  // Style the range slider
  static lv_style_t style_main;
  lv_style_init(&style_main);
  lv_style_set_bg_opa(&style_main, LV_OPA_COVER);
  lv_style_set_bg_color(&style_main, lv_color_hex(0x737884));
  lv_style_set_radius(&style_main, LV_RADIUS_CIRCLE);
  lv_style_set_pad_ver(&style_main, -2); // Makes the indicator larger
  
  // Style the slider indicator
  static lv_style_t style_indicator;
  lv_style_init(&style_indicator);
  lv_style_set_bg_opa(&style_indicator, LV_OPA_COVER);
  lv_style_set_bg_color(&style_indicator, lv_color_hex(0xffcc00));
  lv_style_set_radius(&style_indicator, LV_RADIUS_CIRCLE);

  // Style the slider knob
  static lv_style_t style_knob;
  lv_style_init(&style_knob);
  lv_style_set_bg_opa(&style_knob, LV_OPA_COVER);
  lv_style_set_bg_color(&style_knob, lv_color_hex(0xcca300));
  lv_style_set_border_color(&style_knob, lv_color_hex(0x997a00));
  lv_style_set_border_width(&style_knob, 2);
  lv_style_set_radius(&style_knob, LV_RADIUS_CIRCLE);
  lv_style_set_pad_all(&style_knob, 15); // Makes the knob larger

  // Create a slider aligned in the center bottom of the TFT display
  lv_obj_t * slider = lv_slider_create(lv_screen_active());
  lv_obj_align(slider, LV_ALIGN_CENTER, 0, -30);
  lv_slider_set_range(slider, 0, 100);
  lv_obj_set_style_anim_duration(slider, 2000, 0);
  lv_obj_add_style(slider, &style_main, LV_PART_MAIN);
  lv_obj_add_style(slider, &style_indicator, LV_PART_INDICATOR);
  lv_obj_add_style(slider, &style_knob, LV_PART_KNOB);

  // Create a label below the slider to display the current slider value
  lv_obj_t * slider_label = lv_label_create(lv_screen_active());
  lv_label_set_text(slider_label, "0%");
  lv_obj_align_to(slider_label, slider, LV_ALIGN_CENTER, 0, 100);

   static lv_style_t style_text_label; 
  lv_style_init(&style_text_label); 
  lv_style_set_text_font(&style_text_label, &lv_font_montserrat_34); 
  lv_obj_add_style(slider_label, &style_text_label, 0);

  // Add callback function to the slider
  lv_obj_add_event_cb(slider, event_handler_e5, LV_EVENT_VALUE_CHANGED, slider_label);
}

