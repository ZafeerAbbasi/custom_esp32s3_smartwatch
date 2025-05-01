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
 * @brief Settings Options Enum
 * @note Used to index the array of aSettingsOptions in SETTINGS_zUserSettingsObj_t
 */
typedef enum SETTINGS_eSettingsOptions_t
{
    SETTINGS_eOptionScreenBrightness    = 0,
    SETTINGS_eOptionCircularScroll,
    SETTINGS_eOptionScreenTimeout,
    SETTINGS_eOptionCount
} SETTINGS_eSettingsOptions_t;

/**
 * @brief Main User Settings Object
 * @note Contains Settins Container, Settings List Object and Settings Options objs,
 * which go on the list object
 */
typedef struct SETTINGS_zUserSettingsObj_t
{
    lv_obj_t                        *pSettingsContainerObj;
    lv_obj_t                        *pSettingsListObj;
    COMMON_zCustomListOption_t      aSettingsOptions[ SETTINGS_eOptionCount ];
    lv_obj_t                        *pSettingsExitBtn;
    lv_obj_t                        *pSettingsExitBtnLabel;
    lv_obj_t                        *pSettingsLoadingScreen;
} SETTINGS_zUserSettingsObj_t;

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
