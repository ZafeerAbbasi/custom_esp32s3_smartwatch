/**
  ******************************************************************************
  * @file           : app_settings.h
  * @brief          : Header for APP_SETTINGS module
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
#ifndef __APP_SETTINGS_H
#define __APP_SETTINGS_H

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
 * @brief Settings Exit Button Struct
 * @note Contains Button Cont, and a label
 */
typedef struct SETTINGS_zExitBtn_t
{
    lv_obj_t                            *pBtnCont;
    lv_obj_t                            *pBtnLabel;
} SETTINGS_zExitBtn_t;

/**
 * @brief Brightness list option struct
 * @note Contains basic list option struct, slider,
 * and slider label
 */
typedef struct SETTINGS_zListOptBright_t
{
    COMMON_zBasicListOpt_t              zBasicOptionObjs;
    lv_obj_t                            *pSlider;
    lv_obj_t                            *pSliderLabel;
} SETTINGS_zListOptBright_t;

/**
 * @brief Circular Scroll Option struct
 * @note Contains basic list option struct, switch,
 * and switch label
 */
typedef struct SETTINGS_zListOptCircScroll_t
{
    COMMON_zBasicListOpt_t              zBasicOptionObjs;
    lv_obj_t                            *pSwitch;
    lv_obj_t                            *pSwitchLabel;
} SETTINGS_zListOptCircScroll_t;

/**
 * @brief Main Usr Settings Object
 * @note Contains all objects on the settings screen
 */
typedef struct SETTINGS_zUsrSettingsObj_t
{
    lv_obj_t                            *pSettingsContObj;
    lv_obj_t                            *pSettingsListObj;
    lv_obj_t                            *pSettingsLoadingScreen;
    SETTINGS_zExitBtn_t                 zSettingsExitBtn;
    SETTINGS_zListOptBright_t           zListOptBright;
    SETTINGS_zListOptCircScroll_t       zListOptCircScroll;
} SETTINGS_zUsrSettingsObj_t;

/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void SETTINGS_InitCb( lv_event_t *pEvent );

/* Exported defines ----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APP_SETTINGS_H */
