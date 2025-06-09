/*
 * SPDX-FileCopyrightText: 2022-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */



#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "esp_lvgl_port.h"
#include "lv_demos.h"

/* User includes */
#include "hal.h"
#include "lvgl_app.h"
#include "app_main.h"

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 280

static const char *TAG = "EXAMPLE";

static lv_obj_t *avatar;

void create_ui( void );

// static void _app_button_cb(lv_event_t *e)
// {
//     lv_disp_rotation_t rotation = lv_disp_get_rotation(lvgl_disp);
//     rotation++;
//     if (rotation > LV_DISPLAY_ROTATION_270)
//     {
//         rotation = LV_DISPLAY_ROTATION_0;
//     }

//     /* LCD HW rotation */
//     lv_disp_set_rotation(lvgl_disp, rotation);
// }

void create_ui(void) {

    lv_obj_t *h_scroll_container = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(h_scroll_container);  // Remove border/shadow/padding
    lv_obj_set_size(h_scroll_container, LV_HOR_RES, LV_VER_RES);
    lv_obj_add_flag(h_scroll_container, LV_OBJ_FLAG_SCROLL_ONE);
    lv_obj_set_scroll_snap_x(h_scroll_container, LV_SCROLL_SNAP_START);
    lv_obj_set_scroll_dir(h_scroll_container, LV_DIR_HOR);
    lv_obj_set_scrollbar_mode(h_scroll_container, LV_SCROLLBAR_MODE_OFF);

    // ✅ Use FLEX layout with horizontal flow
    lv_obj_set_layout(h_scroll_container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(h_scroll_container, LV_FLEX_FLOW_ROW);  // Arrange children horizontally

    // ✅ Remove all spacing/padding
    lv_obj_set_style_pad_all(h_scroll_container, 0, 0);    // Internal padding
    lv_obj_set_style_pad_row(h_scroll_container, 0, 0);
    lv_obj_set_style_pad_column(h_scroll_container, 0, 0);
    lv_obj_set_style_pad_gap(h_scroll_container, 0, 0);



    lv_obj_t *screen1 = lv_obj_create(h_scroll_container);
    lv_obj_remove_style_all(screen1);
    lv_obj_set_size(screen1, LV_HOR_RES, LV_VER_RES);

    lv_obj_set_style_bg_opa(screen1, LV_OPA_COVER, 0);  // Needed to show bg
    lv_obj_set_style_bg_color(screen1, lv_color_hex(0x000000), 0);  // Set black background


    // Add time label
    lv_obj_t *label_time = lv_label_create(screen1);
    lv_label_set_text(label_time, "12:45");
    lv_obj_align(label_time, LV_ALIGN_CENTER, 0, -20);

    // Add date label
    lv_obj_t *label_date = lv_label_create(screen1);
    lv_label_set_text(label_date, "Wed, Apr 23");
    lv_obj_align(label_date, LV_ALIGN_CENTER, 0, 20);

    lv_obj_t *screen2 = lv_obj_create(h_scroll_container);
    lv_obj_set_layout(screen2, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(screen2, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_size(screen2, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_pos(screen2, LV_HOR_RES, 0);  // Place to the right

    lv_obj_set_scroll_dir(screen2, LV_DIR_VER); // Vertical scroll for this screen
    lv_obj_add_flag(screen2, LV_OBJ_FLAG_SCROLL_ONE);
    lv_obj_set_scrollbar_mode(screen2, LV_SCROLLBAR_MODE_ACTIVE);

    // Add rounded menu buttons
    for(int i = 0; i < 5; i++) {
        lv_obj_t *btn = lv_btn_create(screen2);
        lv_obj_set_size(btn, 180, 60);
        lv_obj_set_style_radius(btn, 30, 0);
        lv_obj_add_flag(btn, LV_OBJ_FLAG_SNAPPABLE);  // Optional for snapping

        // Center contents (label)
        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text_fmt(label, "Option %d", i + 1);
        lv_obj_center(label);
    }
}


static void app_main_display(void)
{
    lv_obj_t *scr = lv_scr_act();

    /* Task lock */
    lvgl_port_lock(-1);

    // create_ui( );
    // APP_Init( );
    lv_demo_widgets();
    
    // LV_IMG_DECLARE(img_test3);
    // avatar = lv_img_create(scr);
    // lv_img_set_src(avatar, &img_test3);

    /* Task unlock */
    lvgl_port_unlock();
}

void app_main(void)
{   
    /* Low Level HW Init
    - LCD/SPI
    - I2C Bus
    - Touch Controller */
    HAL_Init( );

    /* LVGL initialization */
    LVGL_Init( );

    /* Show LVGL objects */
    app_main_display();
}
