/**
  ******************************************************************************
  * @file           : app_ctrl_panel.c
  * @brief          : Contains application functions related to the control panel
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

/* Includes ------------------------------------------------------------------*/

#include "app_ctrl_panel.h"

/* Typedef -------------------------------------------------------------------*/


/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/


/* Function prototypes -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/

/**
 * @brief Initialize the Control Panel Screen
 *
 * @param pUsrCtrlPanelObj Pointer to the Usr Control Panel Object from the Main Watch Object
 * @param pParentObj Pointer to the Parent Object ( Main Watch Cont )
 */
void CTRLPANEL_Init( CTRLPANEL_zUsrCtrlPanelObj_t *pUsrCtrlPanelObj, lv_obj_t *pParentObj )
{
    lv_obj_t **ppCtrlPanelContObj                  = &pUsrCtrlPanelObj->pCtrlPanelContObj;
    lv_obj_t **ppCtrlPanelListObj                       = &pUsrCtrlPanelObj->pCtrlPanelListObj;
    COMMON_zBasicListOpt_t *pCtrlPaneOptionsArray   = pUsrCtrlPanelObj->aCtrlPanelOptions;

    /* Create the Control panel Cont and remove default styling */
    *ppCtrlPanelContObj = lv_obj_create(pParentObj);
    lv_obj_remove_style_all( *ppCtrlPanelContObj );
    lv_obj_set_size( *ppCtrlPanelContObj, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT );
    lv_obj_set_style_bg_opa( *ppCtrlPanelContObj, LV_OPA_TRANSP, LV_PART_MAIN );

    /* Create the Control Panel List on the Control panel Cont */
    *ppCtrlPanelListObj = lv_obj_create( *ppCtrlPanelContObj );

    /* Configure the Control Panel List */
    COMMON_SetupCustomListObj( *ppCtrlPanelListObj );

    /* Create the List Options on the CtrlPanelList */
    COMMON_AddCustomListOption( "App Info",
                            &img_app_info,
                            80,
                            &pCtrlPaneOptionsArray[ CTRLPANEL_eOptionAppInfo ],
                            *ppCtrlPanelListObj
                          );
    COMMON_AddCustomListOption( "Settings",
                            &img_settings,
                            80,
                            &pCtrlPaneOptionsArray[ CTRLPANEL_eOptionSettings ],
                            *ppCtrlPanelListObj
                          );
    COMMON_AddCustomListOption( "Theme",
                            &img_theme,
                            80,
                            &pCtrlPaneOptionsArray[ CTRLPANEL_eOptionTheme ],
                            *ppCtrlPanelListObj
                          );

    /* Make sure first option is in the middle at start */
    lv_obj_scroll_to_view(lv_obj_get_child(*ppCtrlPanelListObj, 0), LV_ANIM_OFF);

    /* Add Cb functions */
    COMMON_AddCustomListOptionCb( &pCtrlPaneOptionsArray[ CTRLPANEL_eOptionSettings ],
                                            SETTINGS_InitCb,
                                            ( void * )&pUsrCtrlPanelObj->zSettingsObj );

    /* Manually send first event to enable scrolling effect */
    #ifdef USE_SDL
        lv_obj_send_event(*ppCtrlPanelListObj, LV_EVENT_SCROLL, NULL);
    #else
        lv_event_send(*ppCtrlPanelListObj, LV_EVENT_SCROLL, NULL);
    #endif

}
