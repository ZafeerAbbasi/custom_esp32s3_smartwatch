/******************************************************************************
 
******************************************************************************
  @file         : hal.h
  @brief        : Header for HAL Module
******************************************************************************

  @attention

  Copyright (c) 2025 Zafeer Abbasi.
  All rights reserved.

  This software is licensed under terms that can be found in the LICENSE file
  in the root directory of this software component.
  If no LICENSE file comes with the software, it is provided AS-IS.
 
******************************************************************************/
 
#ifndef HAL_H
#define HAL_H
 
/*==============================================================================
                              Includes
==============================================================================*/
 
#include <stdlib.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "driver/spi_master.h"

#include "esp_lcd_sh8601.h"
#include "esp_io_expander_tca9554.h"
#include "esp_lcd_touch_ft5x06.h"

 
/*==============================================================================
                          Public Defines
==============================================================================*/

// Display
#define HAL_DISP_H_RES                      368
#define HAL_DISP_V_RES                      448

// SPI Bus Config
#define HAL_SPI_BUS_PORT                    SPI2_HOST

// I2C Bus Config
#define HAL_I2C_MASTER_PORT_NUM             I2C_NUM_0
#define HAL_I2C_MASTER_SDA_PIN              GPIO_NUM_15
#define HAL_I2C_MASTER_SCL_PIN              GPIO_NUM_14
#define HAL_I2C_MASTER_CLK_SPEED            ( 200 * 1000 )

// I2C TCA9554 IO Expander
#define HAL_I2C_IO_EXP_LCD_RST_PIN          ( IO_EXPANDER_PIN_NUM_0 )
#define HAL_I2C_IO_EXP_LCD_DSI_PWR_EN_PIN   ( IO_EXPANDER_PIN_NUM_1 )
#define HAL_I2C_IO_EXP_TOUCH_RST_PIN        ( IO_EXPANDER_PIN_NUM_2 )

// I2C FT5X06 Touch Controller
#define HAL_I2C_TOUCH_INT_PIN               GPIO_NUM_21

// QSPI SH8601 AMOLED Display Controller
#define HAL_LCD_BITS_PER_PIXEL              16
#define HAL_LCD_CS_PIN                      GPIO_NUM_12
#define HAL_LCD_PCLK_PIN                    GPIO_NUM_11
#define HAL_LCD_DATA_0_PIN                  GPIO_NUM_4
#define HAL_LCD_DATA_1_PIN                  GPIO_NUM_5
#define HAL_LCD_DATA_2_PIN                  GPIO_NUM_6
#define HAL_LCD_DATA_3_PIN                  GPIO_NUM_7
#define HAL_LCD_MAX_DATA_TRANSFR_SIZE       HAL_DISP_H_RES * HAL_DISP_V_RES * HAL_LCD_BITS_PER_PIXEL / 8

 
/*=============================================================================
                          Public Data Types
=============================================================================*/

 
/*==============================================================================
                          Public Constants
==============================================================================*/
 
 
/*==============================================================================
                          Public Variables
==============================================================================*/

extern esp_lcd_touch_handle_t HAL_ptzTouchHdl;
 
/*==============================================================================
                      Public Function Prototypes
==============================================================================*/

void I2C_fnInit( void );
 
#endif  // HAL_H
 
//*****************************************************************************
// End of file.
//! @}
//*****************************************************************************
