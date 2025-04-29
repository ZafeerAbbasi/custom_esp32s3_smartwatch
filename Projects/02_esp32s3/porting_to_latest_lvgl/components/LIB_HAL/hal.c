/**
  ******************************************************************************
  * @file           : hal.c
  * @brief          : Interface for dealing with low-level HW drivers
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

#include "hal.h"

/* Typedef -------------------------------------------------------------------*/


/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/


/* Function prototypes -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/

/**
 * @brief Initializes all low level HW - LCD, I2C BUS, Touch Controller
 * 
 */
void HAL_Init( void )
{
    /* Disable logging for everything -> Consumes way too much CPU, like 100% sometimes */
    esp_log_level_set("*", ESP_LOG_NONE);
    
    /* LCD Controller Initialization */
    LCD_LcdControllerInit( );

    // /* I2C Port Zero Bus Master Initialization */
    // I2C_PortZeroBusMasterInit( );

    // /* Touch Controller Initialization */
    // TOUCH_TouchControllerInit( );
}