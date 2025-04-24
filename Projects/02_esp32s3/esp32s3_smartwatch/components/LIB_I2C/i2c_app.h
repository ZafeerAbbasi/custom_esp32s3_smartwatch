/**
  ******************************************************************************
  * @file           : i2c_app.h
  * @brief          : Header for i2c module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_APP_H		
#define __I2C_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "driver/gpio.h"
#include "driver/i2c.h"

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

esp_err_t I2C_PortZeroBusMasterInit( void );

/* Private defines -----------------------------------------------------------*/


/* Touch controller */
#define I2C_MASTER_PORT         I2C_NUM_0
#define I2C_MASTER_GPIO_SCL     (GPIO_NUM_10)
#define I2C_MASTER_GPIO_SDA     (GPIO_NUM_11)
#define I2C_MASTER_CLK_SPEED    (100 * 1000) // 100kHz


#ifdef __cplusplus
}
#endif

#endif /* __I2C_APP_H */