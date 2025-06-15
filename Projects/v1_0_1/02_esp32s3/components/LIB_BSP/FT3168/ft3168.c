/******************************************************************************
 
******************************************************************************  
  @file         : ft3168.c
  @brief        : Contains code to interface with the FT3168 Touch Controller
******************************************************************************

  @attention

  Copyright (c) 2025 Zafeer Abbasi.
  All rights reserved.

  This software is licensed under terms that can be found in the LICENSE file
  in the root directory of this software component.
  If no LICENSE file comes with the software, it is provided AS-IS.
 
******************************************************************************/
 
/*==============================================================================
                              Includes
==============================================================================*/

#include "bsp.h"
 
/*==============================================================================
                              Defines
==============================================================================*/
 
 
/*==============================================================================
                               Data Types
==============================================================================*/
 
 
/*==============================================================================
                           Local/Private Data
==============================================================================*/

// Touch Instance Handle, used by the periodic touch cb in LVGL, which
// uses the handle to check if there is any touch from user
esp_lcd_touch_handle_t BSP_ptzTouchHdl = NULL;    
 
/*==============================================================================
                        Local/Private Function Prototypes
==============================================================================*/
 
 
/*==============================================================================
                           Function Definitions
==============================================================================*/

/***************************************************************************//**
    @brief Initialize the FT3168 Touch Controller
    
 ******************************************************************************/
void BSP_fnI2cFT3168Init( void )
{
    esp_lcd_panel_io_handle_t tzLCDTouchIOHdl               = NULL;
    const esp_lcd_panel_io_i2c_config_t ktzLCDTouchIOCfg    = ESP_LCD_TOUCH_IO_I2C_FT5x06_CONFIG( );
    const esp_lcd_touch_config_t ktzTouchCfg                = {
        .x_max          = BSP_DISP_H_RES,
        .y_max          = BSP_DISP_V_RES,
        .rst_gpio_num   = -1,
        .int_gpio_num   = BSP_I2C_TOUCH_INT_PIN,
        .levels         = {
            .reset      = 0,
            .interrupt  = 0
        },
        .flags          = {
            .swap_xy    = 0,
            .mirror_x   = 0,
            .mirror_y   = 0
        },
    };

    // Attach FT3168 to the I2C Bus as new LCD IO
    ESP_ERROR_CHECK( esp_lcd_new_panel_io_i2c( ( uint32_t )BSP_I2C_MASTER_PORT_NUM, &ktzLCDTouchIOCfg, &tzLCDTouchIOHdl ) );

    // Initialize Touch Controller
    ESP_ERROR_CHECK( esp_lcd_touch_new_i2c_ft5x06( tzLCDTouchIOHdl, &ktzTouchCfg, &BSP_ptzTouchHdl ) );
}
 
//*****************************************************************************
// End of file.
//! @}
//*****************************************************************************
