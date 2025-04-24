/**
  ******************************************************************************
  * @file           : touch.h
  * @brief          : Header for touch module.
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
#ifndef __TOUCH_H		
#define __TOUCH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "driver/gpio.h"
#include "esp_lcd_touch_cst816s.h"

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/

extern esp_lcd_touch_handle_t TOUCH_zTouchPanelHdl;

/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

esp_err_t TOUCH_TouchControllerInit( void );


/* Private defines -----------------------------------------------------------*/

#define TOUCH_GPIO_INT      ( GPIO_NUM_14 )
#define TOUCH_GPIO_RST      ( GPIO_NUM_13 )

#ifdef __cplusplus
}
#endif

#endif /* __TOUCH_H */