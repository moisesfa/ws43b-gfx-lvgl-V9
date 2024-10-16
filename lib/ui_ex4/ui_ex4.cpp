#include "ui_ex4.h"
#include <lvgl.h>
#include "image.h"
#include "image_led_off.h"
#include "image_led_on.h"
#include <Arduino.h>


//***********************************
// EJERCICIO 1
//***********************************
/*
Procesar y cargar una imagen en el display
*/
void lv_create_ui_e4_1(void)
{
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);
    LV_IMAGE_DECLARE(my_image);
    lv_obj_t * img1 = lv_image_create(lv_screen_active());
    lv_image_set_src(img1, &my_image);
    lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);

    /*Create a white label, set its text and align it to the center*/
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello world image");
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 100);
}


//***********************************
// EJERCICIO 2
//***********************************
/*
Mostrar varias imágenes y a hacer que se pueda hacer clic en ellas, para poder ejecutar 
tareas al hacer clic en ellas. 
*/

LV_IMAGE_DECLARE(image_led_off);
LV_IMAGE_DECLARE(image_led_on);
static bool led_status = false ;
static lv_obj_t * img_led;

// Event callback function
static void image_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    Serial.println("Image clicked");
    // Cheap Yellow Display built-in RGB LED is controlled with inverted logic
    // If you are using a regular LED, remove the ! from the if statement
    if (!led_status) {
      lv_image_set_src(img_led, &image_led_off);
      lv_obj_align(img_led, LV_ALIGN_CENTER, 0, 0);
      led_status = true;
      Serial.println("Set LED to OFF!");
    }
    else {
      lv_image_set_src(img_led, &image_led_on);
      lv_obj_align(img_led, LV_ALIGN_CENTER, 0, 0);
      led_status = false;
      Serial.println("Set LED to ON!");
    }
  }
}

void lv_create_ui_e4_2(void)
{
  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x957012), LV_PART_MAIN);
  img_led = lv_image_create(lv_screen_active());
  lv_image_set_src(img_led, &image_led_off);
  lv_obj_add_flag(img_led, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_event_cb(img_led, image_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_align(img_led, LV_ALIGN_CENTER, 0, 0);
}


