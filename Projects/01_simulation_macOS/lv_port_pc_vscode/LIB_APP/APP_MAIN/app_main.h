/**
  ******************************************************************************
  * @file           : app_main.h
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

#ifdef USE_SDL
    #include <lvgl/lvgl.h>
#else
    #include "esp_lvgl_port.h"
#endif

#include "app_clock.h"
#include "app_ctrl_panel.h"

/* Exported types ------------------------------------------------------------*/

/* Main Watch Object Struct */
typedef struct APP_zUsrWatchObj_t
{
    lv_obj_t                        *pMainWatchCont;
    Clock_zUsrClockObj_t           zClockObj;
    CTRLPANEL_zUsrCtrlPanelObj_t   zCtrlPanelObj;
} APP_zUsrWatchObj_t;

/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void APP_Init( void );

/* Exported defines ----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APP_USER_H */
