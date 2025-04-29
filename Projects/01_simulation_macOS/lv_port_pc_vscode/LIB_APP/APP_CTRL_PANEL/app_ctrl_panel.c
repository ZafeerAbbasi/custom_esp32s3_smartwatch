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
    lv_obj_t *pCtrlPanelContainerObj                    = pUserCtrlPanelObj->pCtrlPanelContainerObj;
    lv_obj_t *pCtrlPanelListObj                         = pUserCtrlPanelObj->pCtrlPanelListObj;
    COMMON_zCustomListOption_t *pCtrlPaneOptionsArray   = pUserCtrlPanelObj->aCtrlPanelOptions;

    /* Create the Control panel container and remove default styling */
    pCtrlPanelContainerObj = lv_obj_create(pParentObj);
    COMMON_RegisterUserObj( pCtrlPanelContainerObj, COMMON_eTypeContainer );
    lv_obj_remove_style_all( pCtrlPanelContainerObj );
    lv_obj_set_size( pCtrlPanelContainerObj, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT );
    lv_obj_set_style_bg_opa( pCtrlPanelContainerObj, LV_OPA_COVER, LV_PART_MAIN );
    lv_obj_set_style_bg_color(pCtrlPanelContainerObj, lv_color_make( 13, 17, 23 ), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_color(pCtrlPanelContainerObj, lv_color_make( 40, 52, 71 ), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(pCtrlPanelContainerObj, LV_GRAD_DIR_VER, LV_PART_MAIN);

    /* Create the Control Panel List on the Control panel container */
    pCtrlPanelListObj = lv_obj_create( pCtrlPanelContainerObj );
    COMMON_RegisterUserObj( pCtrlPanelListObj, COMMON_eTypeDontTrack );

    /* Configure the Control Panel List */
    COMMON_SetupCustomListObj( pCtrlPanelListObj );

    /* Create the List Options on the CtrlPanelList */
    COMMON_AddCustomListOption( "App Info",
                            &img_app_info,
                            80,
                            &pCtrlPaneOptionsArray[ CTRLPANEL_eOptionAppInfo ],
                            pCtrlPanelListObj
                          );
    COMMON_AddCustomListOption( "Settings",
                            &img_settings,
                            80,
                            &pCtrlPaneOptionsArray[ CTRLPANEL_eOptionSettings ],
                            pCtrlPanelListObj
                          );
    COMMON_AddCustomListOption( "Theme",
                            &img_theme,
                            80,
                            &pCtrlPaneOptionsArray[ CTRLPANEL_eOptionTheme ],
                            pCtrlPanelListObj
                          );

    /* Add Callback functions */
    COMMON_AddCustomListOptionCallback( &pCtrlPaneOptionsArray[ CTRLPANEL_eOptionSettings ],
                                            SETTINGS_InitCallback,
                                            ( void * )&pUserCtrlPanelObj->zSettingsObj );

    /* Add Circular Scroll callback to the CtrlPanel List Obj */
    lv_obj_add_event_cb( pCtrlPanelListObj, COMMON_ListCircularScrollCallback, LV_EVENT_SCROLL, ( void * )&isCircularScroll );

    /* Manually send first event to enable scrolling effect */
    #ifdef USE_SDL
        lv_obj_send_event(pCtrlPanelListObj, LV_EVENT_SCROLL, NULL);
    #else
        lv_event_send(pCtrlPanelListObj, LV_EVENT_SCROLL, NULL);
    #endif

}
