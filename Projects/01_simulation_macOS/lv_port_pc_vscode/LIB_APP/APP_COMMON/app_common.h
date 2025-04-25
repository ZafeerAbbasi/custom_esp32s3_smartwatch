/**
  ******************************************************************************
  * @file           : app_common.h
  * @brief          : Header for APP_COMMON module
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
#ifndef __APP_COMMON_H
#define __APP_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <lvgl/lvgl.h>
#include "app_clock.h"

/* Exported types ------------------------------------------------------------*/

/* Foward Declaration for CLOCK_zUserClockObj_t */
typedef struct CLOCK_zUserClockObj_t CLOCK_zUserClockObj_t;

/* General Struct for Widgets and thier corresponding style */
typedef struct COMMON_zUserWidgetObj_t
{
    lv_obj_t                    *pUserWidget;
    lv_style_t                  userWidgetStyle;
} COMMON_zUserWidgetObj_t;

/* Main Watch Object Struct */
typedef struct COMMON_zUserWatchObj_t
{
    COMMON_zUserWidgetObj_t     zMainWatchContainer;
    CLOCK_zUserClockObj_t       *zClockObj;
    COMMON_zUserWidgetObj_t     zControlPanelObj;
} COMMON_zUserWatchObj_t;

/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/


/* Private defines -----------------------------------------------------------*/

#define APP_SCREEN_WIDTH  240
#define APP_SCREEN_HEIGHT 280


#ifdef __cplusplus
}
#endif

#endif /* __APP_COMMON_H */
