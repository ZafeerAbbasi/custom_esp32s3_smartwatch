/**
  ******************************************************************************
  * @file           : app_ctrl_panel.h
  * @brief          :
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
#ifndef __APP_CTRL_PANEL_H
#define __APP_CTRL_PANEL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#ifdef USE_SDL
    #include <lvgl/lvgl.h>
#else
    #include "esp_lvgl_port.h"
#endif
#include "app_common.h"
#include "app_settings.h"
#include "app_theme.h"

/* Exported types ------------------------------------------------------------*/

/**
 * @brief Control Panel Options Enum
 * @note Used to index the array of aCtrlPanelOptions in CTRLPANEL_zUsrCtrlPanelObj_t
 */
typedef enum CTRLPANEL_eBasicOpts
{
    CTRLPANEL_eOptAppInfo        = 0,
    CTRLPANEL_eOptSettings,
    CTRLPANEL_eOptTheme,
    CTRLPANEL_eBasicOptCnt
} CTRLPANEL_eBasicOpts;

/**
 * @brief Main Usr Control Panel Object
 * @note Contains CtrlPanel Cont, CtrlPanel List Object and CtrlPanel Option objects,
 * which go on the list oject
 */
typedef struct CTRLPANEL_zUsrCtrlPanelObj_t
{
    lv_obj_t                        *pCtrlPanelContObj;
    lv_obj_t                        *pCtrlPanelListObj;
    COMMON_zBasicListOpt_t          aCtrlPanelOptions[ CTRLPANEL_eBasicOptCnt ];
    SETTINGS_zUsrSettingsObj_t      zSettingsObj;
    THEME_zUsrThemeObj_t            zThemeObj;
} CTRLPANEL_zUsrCtrlPanelObj_t;

/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void CTRLPANEL_Init( CTRLPANEL_zUsrCtrlPanelObj_t *pUsrCtrlPanelObj, lv_obj_t *pParentObj );


/* Exported defines ----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __LCD_H */
