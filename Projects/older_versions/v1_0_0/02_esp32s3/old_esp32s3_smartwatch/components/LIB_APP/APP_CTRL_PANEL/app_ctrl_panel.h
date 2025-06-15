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

/* Exported types ------------------------------------------------------------*/

/**
 * @brief Control Panel Options Enum
 * @note Used to index the array of aCtrlPanelOptions in CTRLPANEL_zUserCtrlPanelObj_t
 */
typedef enum CTRLPANEL_eCtrlPanelOptions_t
{
    CTRLPANEL_eOptionAppInfo        = 0,
    CTRLPANEL_eOptionSettings,
    CTRLPANEL_eOptionTheme,
    CTRLPANEL_eOptionCount
} CTRLPANEL_eCtrlPanelOptions_t;

/**
 * @brief Main User Control Panel Object
 * @note Contains CtrlPanel Container, CtrlPanel List Object and CtrlPanel Option objects,
 * which go on the list oject
 */
typedef struct CTRLPANEL_zUserCtrlPanelObj_t
{
    lv_obj_t                        *pCtrlPanelContainerObj;
    lv_obj_t                        *pCtrlPanelListObj;
    COMMON_zBasicListOption_t       aCtrlPanelOptions[CTRLPANEL_eOptionCount];
    SETTINGS_zUserSettingsObj_t     zSettingsObj;
} CTRLPANEL_zUserCtrlPanelObj_t;

/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void CTRLPANEL_Init( CTRLPANEL_zUserCtrlPanelObj_t *pUserCtrlPanelObj, lv_obj_t *pParentObj );


/* Exported defines ----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __LCD_H */
