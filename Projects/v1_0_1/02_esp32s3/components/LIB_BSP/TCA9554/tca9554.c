/******************************************************************************
 
******************************************************************************  
  @file         : tca9554.c
  @brief        : Contains code to interface with the TCA9554 IO Expander
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
 
 
/*==============================================================================
                        Local/Private Function Prototypes
==============================================================================*/
 
 
/*==============================================================================
                           Function Definitions
==============================================================================*/

/***************************************************************************//**
    @brief Initialize the TCA9554 IO Expander

    @note The IO Expander is used to control the voltage on the following pins:
    
    - LCD Controller Reset Pin

    - LCD Controller DSI Power Enable Pin

    - Touch Controller Reset Pin
    
 ******************************************************************************/
void BSP_fnI2cTCA9554Init( void )
{
    esp_io_expander_handle_t tpzIOExpHdl = NULL;

    // Create a new TCA9554 IO Expander Driver
    ESP_ERROR_CHECK( esp_io_expander_new_i2c_tca9554( BSP_I2C_MASTER_PORT_NUM,
                                     ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000,
                                     &tpzIOExpHdl ) );

    // Set pins direction
    esp_io_expander_set_dir( tpzIOExpHdl, 
                             IO_EXPANDER_PIN_NUM_0 | IO_EXPANDER_PIN_NUM_1 | IO_EXPANDER_PIN_NUM_2,
                             IO_EXPANDER_OUTPUT );
    
    // Set pins to low initially
    esp_io_expander_set_level(  tpzIOExpHdl, 
                                IO_EXPANDER_PIN_NUM_0 | IO_EXPANDER_PIN_NUM_1 | IO_EXPANDER_PIN_NUM_2,
                                0 );
                                
    vTaskDelay( pdMS_TO_TICKS( 200 ) );   // Delay becuase the LCD Controller might register the pins going low
                                                        // as commands
    
    // Set pins to high as they all connect to RST pins for controllers of LCD/TOUCH
    esp_io_expander_set_level(  tpzIOExpHdl, 
                                IO_EXPANDER_PIN_NUM_0 | IO_EXPANDER_PIN_NUM_1 | IO_EXPANDER_PIN_NUM_2,
                                1 );
}
 
//*****************************************************************************
// End of file.
//! @}
//*****************************************************************************
