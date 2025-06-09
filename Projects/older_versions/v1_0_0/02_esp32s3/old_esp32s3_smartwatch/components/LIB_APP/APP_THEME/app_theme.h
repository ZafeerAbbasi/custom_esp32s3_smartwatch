/**
  ******************************************************************************
  * @file           : app_theme.h
  * @brief          : Header for APP_THEME module
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
#ifndef __APP_THEME_H
#define __APP_THEME_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#ifdef USE_SDL
    #include <lvgl/lvgl.h>
#else
    #include "esp_lvgl_port.h"
#endif
#include "app_common.h"

/* Exported types ------------------------------------------------------------*/

/**
 * @brief Theme Exit Button Struct
 * @note Contains Button Cont, and a label
 */
typedef struct THEME_zExitBtn_t
{
    lv_obj_t                            *pBtnCont;
    lv_obj_t                            *pBtnLabel;
} THEME_zExitBtn_t;

/**
 * @brief Theme Switch struct
 * @note Contains basic list option struct, switch,
 * and switch label
 */
typedef struct Theme_zThemeSwitch_t
{
    COMMON_zBasicListOpt_t              zBasicOptionObjs;
    lv_obj_t                            *pSwitch;
    lv_obj_t                            *pSwitchLabel;
} Theme_zThemeSwitch_t;

/**
 * @brief Main Usr Theme Object
 * @note Contains all objects on the settings screen
 */
typedef struct THEME_zUsrThemeObj_t
{
    lv_obj_t                            *pThemeContObj;
    lv_obj_t                            *pThemeListObj;
    lv_obj_t                            *pThemeLoadingScreen;
    THEME_zExitBtn_t                    zThemeExitBtn;
    Theme_zThemeSwitch_t                zThemeSwitch;
} THEME_zUsrThemeObj_t;

/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void THEME_InitCb( lv_event_t *pEvent );

/* Exported defines ----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APP_THEME_H */
