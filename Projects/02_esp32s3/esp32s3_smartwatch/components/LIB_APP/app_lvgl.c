/**
  ******************************************************************************
  * @file           : app_lvgl.c
  * @brief          : Contains for application lvgl functions.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 Zafeer Abbasi.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "driver/gpio.h"
#include "esp_lvgl_port.h"
#include "lv_demos.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* User includes */
#include "lcd.h"
#include "user_i2c.h"
#include "touch.h"

/* Typedef -------------------------------------------------------------------*/


/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/


/* Function prototypes -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/

esp_err_t APP_LvglInit( void )
{
    esp_err_t ret = ESP_OK;

    /* Basic LVGL Init */
    const lvgl_port_cfg_t zLvglPortCfg = 
    {

    }
}