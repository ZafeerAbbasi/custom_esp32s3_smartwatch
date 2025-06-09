/**
  ******************************************************************************
  * @file           : lvgl_app.h
  * @brief          : Header for Application LVGL Module
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
#ifndef __LVGL_APP_H		
#define __LVGL_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "esp_lvgl_port.h"
#include "lcd.h"
#include "touch.h"

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

esp_err_t LVGL_Init( void );
// void LVGL_TouchDriverCallback( lv_indev_drv_t *pInputDeviceDriver, lv_indev_data_t *pUserData );


/* Exported defines ----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __LCD_H */