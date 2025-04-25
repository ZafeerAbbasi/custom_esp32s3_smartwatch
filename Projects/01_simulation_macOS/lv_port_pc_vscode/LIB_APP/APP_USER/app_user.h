/**
  ******************************************************************************
  * @file           : app_user.h
  * @brief          : Header for APP_USER module
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
#ifndef __APP_USER_H
#define __APP_USER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <lvgl/lvgl.h>
#include "app_clock.h"

/* Exported types ------------------------------------------------------------*/

/* Main Watch Object Struct */
typedef struct APP_zUserWatchObj_t
{
    COMMON_zUserWidgetObj_t     zMainWatchContainer;
    CLOCK_zUserClockObj_t       zClockObj;
    COMMON_zUserWidgetObj_t     zControlPanelObj;
} APP_zUserWatchObj_t;

/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void APP_Init( void );

/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APP_USER_H */
