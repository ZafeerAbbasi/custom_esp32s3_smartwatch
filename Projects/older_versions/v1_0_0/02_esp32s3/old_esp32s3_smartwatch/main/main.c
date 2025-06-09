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


static void app_main_display(void)
{

    /* Task lock */
    lvgl_port_lock(-1);

    // create_ui( );
    APP_Init( );

    /* Task unlock */
    lvgl_port_unlock();
}

void app_main(void)
{   
    // HW Abstraction Layer Init
    HAL_Init( );

    // Create Wifi task

    // Create LVGL task

    // LVGL Init
    LVGL_Init( );

    // Show LVGL objects
    app_main_display();
}
