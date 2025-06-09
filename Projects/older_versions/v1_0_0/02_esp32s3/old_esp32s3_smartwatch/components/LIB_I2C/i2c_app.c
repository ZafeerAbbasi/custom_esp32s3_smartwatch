/**
  ******************************************************************************
  * @file           : i2c_app.c
  * @brief          : Used for general purpose i2c functions.
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

#include "i2c_app.h"


/* Typedef -------------------------------------------------------------------*/


/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/


/* Function prototypes -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/

/**
 * @brief Initialize the I2C Port 0 Bus as Master
 * 
 * @return esp_err_t ESP_OK on success, error code on failure
 */
esp_err_t I2C_PortZeroBusMasterInit( void )
{
    esp_err_t ret = ESP_OK;

    /* I2C Bus Config Parameter Init */
    const i2c_config_t zI2cConfig =
    {
        .mode               = I2C_MODE_MASTER,
        .sda_io_num         = I2C_MASTER_GPIO_SDA,
        .sda_pullup_en      = GPIO_PULLUP_ENABLE,
        .scl_io_num         = I2C_MASTER_GPIO_SCL,
        .scl_pullup_en      = GPIO_PULLUP_ENABLE,
        .master.clk_speed   = I2C_MASTER_CLK_SPEED,
    };
    ESP_ERROR_CHECK( i2c_param_config( I2C_MASTER_PORT, &zI2cConfig ) );

    /* I2C Bus Driver Install */
    ESP_ERROR_CHECK( i2c_driver_install( I2C_MASTER_PORT, zI2cConfig.mode, 0, 0, 0 ) );

    return ret;
}