#include "ui_ex4.h"
#include <lvgl.h>
#include "image.h"


//***********************************
// EJERCICIO 1
//***********************************

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