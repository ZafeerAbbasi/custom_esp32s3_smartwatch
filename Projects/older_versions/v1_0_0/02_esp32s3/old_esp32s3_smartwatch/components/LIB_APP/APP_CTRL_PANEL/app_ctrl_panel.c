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

/* Flag to use circular scroll or not, default is true */
bool isCircularScroll = true;

/* Function prototypes -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/

/**
 * @brief Initialize the Control Panel Screen
 *
 * @param pUserCtrlPanelObj Pointer to the User Control Panel Object from the Main Watch Object
 * @param pParentObj Pointer to the Parent Object ( Main Watch Container )
 */
void CTRLPANEL_Init( CTRLPANEL_zUserCtrlPanelObj_t *pUserCtrlPanelObj, lv_obj_t *pParentObj )
{
    lv_obj_t **ppCtrlPanelContainerObj                  = &pUserCtrlPanelObj->pCtrlPanelContainerObj;
    lv_obj_t **ppCtrlPanelListObj                       = &pUserCtrlPanelObj->pCtrlPanelListObj;
    COMMON_zBasicListOption_t *pCtrlPaneOptionsArray   = pUserCtrlPanelObj->aCtrlPanelOptions;

    /* Create the Control panel container and remove default styling */
    *ppCtrlPanelContainerObj = lv_obj_create(pParentObj);
    lv_obj_remove_style_all( *ppCtrlPanelContainerObj );
    lv_obj_set_size( *ppCtrlPanelContainerObj, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT );
    lv_obj_set_style_bg_opa( *ppCtrlPanelContainerObj, LV_OPA_TRANSP, LV_PART_MAIN );

    /* Create the Control Panel List on the Control panel container */
    *ppCtrlPanelListObj = lv_obj_create( *ppCtrlPanelContainerObj );

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

    /* Add Cb functions */
    COMMON_AddCustomListOptionCb( &pCtrlPaneOptionsArray[ CTRLPANEL_eOptionSettings ],
                                            SETTINGS_InitCb,
                                            ( void * )&pUserCtrlPanelObj->zSettingsObj );

    /* Add Circular Scroll Cb to the CtrlPanel List Obj */
    lv_obj_add_event_cb( *ppCtrlPanelListObj, COMMON_ListCircularScrollCb, LV_EVENT_SCROLL, ( void * )&isCircularScroll );

    /* Manually send first event to enable scrolling effect */
    #ifdef USE_SDL
        lv_obj_send_event(*ppCtrlPanelListObj, LV_EVENT_SCROLL, NULL);
    #else
        lv_event_send(*ppCtrlPanelListObj, LV_EVENT_SCROLL, NULL);
    #endif

}
