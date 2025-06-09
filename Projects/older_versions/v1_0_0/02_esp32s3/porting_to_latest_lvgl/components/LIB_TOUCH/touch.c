/**
  ******************************************************************************
  * @file           : touch.c
  * @brief          : Low level touch driver for the CST816S touch controller.
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

#include "touch.h"

/* Typedef -------------------------------------------------------------------*/


/* Define --------------------------------------------------------------------*/

#define TOUCH_HORIZONTAL_RESOLUTION     240
#define TOUCH_VERTICAL_RESOLUTION       280
#define TOUCH_I2C_MASTER_PORT           ( I2C_NUM_0 )

/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/

/* ESP LCD Touch Controller Handle */
esp_lcd_touch_handle_t TOUCH_zTouchPanelHdl = NULL;

/* Function prototypes -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/

/**
 * @brief Initialize the Touch Controller
 * 
 * @return esp_err_t ESP_OK on success, error code on failure
 */
esp_err_t TOUCH_TouchControllerInit( void )
{
    esp_err_t ret = ESP_OK;
    esp_lcd_panel_io_handle_t zTouchIoHandle = NULL;
    const esp_lcd_panel_io_i2c_config_t zTouchIoConfig = ESP_LCD_TOUCH_IO_I2C_CST816S_CONFIG( );

    /* Add the touch controller to the I2C bus */
    ESP_ERROR_CHECK( esp_lcd_new_panel_io_i2c( 
        (esp_lcd_i2c_bus_handle_t)TOUCH_I2C_MASTER_PORT, 
        &zTouchIoConfig, 
        &zTouchIoHandle ) );

    /* Install Touch controller driver */
    const esp_lcd_touch_config_t zTouchConfig = 
    {
        .x_max              = TOUCH_HORIZONTAL_RESOLUTION,
        .y_max              = TOUCH_VERTICAL_RESOLUTION,
        .rst_gpio_num       = TOUCH_GPIO_RST,
        .int_gpio_num       = TOUCH_GPIO_INT,
        .levels = 
        {
            .reset          = 0,
            .interrupt      = 0,
        },
        .flags = 
        {
            .swap_xy        = 0,
            .mirror_x       = 0,
            .mirror_y       = 0,
        }
    };
    ESP_ERROR_CHECK( esp_lcd_touch_new_i2c_cst816s( 
        zTouchIoHandle, 
        &zTouchConfig, 
        &TOUCH_zTouchPanelHdl ) );

    return ret;
}