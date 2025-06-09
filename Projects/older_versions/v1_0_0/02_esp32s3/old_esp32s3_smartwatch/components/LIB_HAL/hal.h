/**
  ******************************************************************************
  * @file           : hal.h
  * @brief          : Header for HAL module
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
#ifndef __HAL_H		
#define __HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "lcd.h"
#include "i2c_app.h"
#include "touch.h"

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void HAL_Init( void );

/* Exported defines ----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __HAL_H */