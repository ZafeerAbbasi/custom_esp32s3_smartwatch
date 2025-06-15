
/******************************************************************************
 
******************************************************************************  
  @file         : hal.c
  @brief        : This module is the HAL - Hardware Abstraction Layer
                  This module contains code that is built on top of the LIB_BSP Module.
                  It's a layer to abstract out HW Specific details when interfacing with
                  the HW, including :

                  - TCA9554 IO Expander, 
                  - FT3168 Touch Controller, 
                  - SH8601A0 Display Controller, 
                  - ES8311 Audio Codec,
                  - QMI8658C Inertial Measurement Unit ( IMU ),
                  - PCF85063 Real-Time Clock ( RTC ),
                  - AXP2101 Power Management Unit ( PMU )

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

#include "hal.h"
 
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

void hal_fnSpiBusInit( void );
void hal_fnI2cBusInit( void );

/*==============================================================================
                           Function Definitions
==============================================================================*/

/***************************************************************************//**
    @brief Initialize the SPI Bus
    
    
    @note SPI Port used is SPI2_Host, SPI1_Host is used for flash controller internally
    
 ******************************************************************************/
void hal_fnSpiBusInit( void )
{
    const spi_bus_config_t ktzConfig    = SH8601_PANEL_BUS_QSPI_CONFIG( HAL_LCD_PCLK_PIN,
                                                                        HAL_LCD_DATA_0_PIN,
                                                                        HAL_LCD_DATA_1_PIN,
                                                                        HAL_LCD_DATA_2_PIN,
                                                                        HAL_LCD_DATA_3_PIN,
                                                                        HAL_LCD_MAX_DATA_TRANSFR_SIZE );
    
    // Initialize SPI Bus
    ESP_ERROR_CHECK( spi_bus_initialize( HAL_SPI_BUS_PORT, &ktzConfig, SPI_DMA_CH_AUTO ) ); 
}

// void hal_fnSpiSH8601A0Init( void )
// {
//     const esp_lcd_panel_io_spi_config_t ktzIOConfig = SH8601_PANEL_IO_QSPI_CONFIG(  HAL_LCD_CS_PIN,
                                                                                    
//     )
// }

/***************************************************************************//**
    @brief Initialize the I2C Bus
    

    @note I2C Port used is I2C_NUM_0

 ******************************************************************************/
void hal_fnI2cBusInit( void )
{
    // Initialize I2C Bus
    const i2c_config_t ktzConfig = {
        .mode               = I2C_MODE_MASTER,
        .sda_io_num         = HAL_I2C_MASTER_SDA_PIN,
        .sda_pullup_en      = GPIO_PULLUP_ENABLE,
        .scl_io_num         = HAL_I2C_MASTER_SCL_PIN,
        .scl_pullup_en      = GPIO_PULLUP_ENABLE,
        .master.clk_speed   = HAL_I2C_MASTER_CLK_SPEED
    };
    ESP_ERROR_CHECK( i2c_param_config( HAL_I2C_MASTER_PORT_NUM, &ktzConfig ) );
    ESP_ERROR_CHECK( i2c_driver_install( HAL_I2C_MASTER_PORT_NUM, I2C_MODE_MASTER, 0, 0, 0 ) );
}
 
//*****************************************************************************
// End of file.
//! @}
//*****************************************************************************
