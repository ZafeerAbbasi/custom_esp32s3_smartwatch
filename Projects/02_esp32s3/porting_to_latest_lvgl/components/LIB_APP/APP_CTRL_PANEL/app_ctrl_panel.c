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
    lv_obj_remove_style_all( pCtrlPanelContainerObj );
    lv_obj_set_size( pCtrlPanelContainerObj, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT );
    lv_obj_set_style_bg_opa( pCtrlPanelContainerObj, LV_OPA_COVER, LV_PART_MAIN );
    lv_obj_set_style_bg_color(pCtrlPanelContainerObj, lv_color_make( 13, 17, 23 ), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_color(pCtrlPanelContainerObj, lv_color_make( 40, 52, 71 ), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(pCtrlPanelContainerObj, LV_GRAD_DIR_VER, LV_PART_MAIN);

    /* Create the Control Panel List on the Control panel container */
    pCtrlPanelListObj = lv_obj_create( pCtrlPanelContainerObj );

    /* Configure the Control Panel List */
    lv_obj_set_width(pCtrlPanelListObj, lv_pct(100));
    lv_obj_set_height(pCtrlPanelListObj, lv_pct(100));
    lv_obj_set_align(pCtrlPanelListObj, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(pCtrlPanelListObj, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(pCtrlPanelListObj, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(pCtrlPanelListObj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(pCtrlPanelListObj, LV_DIR_VER);
    lv_obj_set_style_radius(pCtrlPanelListObj, 0, LV_PART_MAIN );
    lv_obj_set_style_bg_opa(pCtrlPanelListObj, LV_OPA_TRANSP, LV_PART_MAIN );
    lv_obj_set_style_border_width(pCtrlPanelListObj, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_left(pCtrlPanelListObj, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_right(pCtrlPanelListObj, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_top(pCtrlPanelListObj, 50, LV_PART_MAIN );
    lv_obj_set_style_pad_bottom(pCtrlPanelListObj, 70, LV_PART_MAIN );

    /* Create the List Options on the CtrlPanelList */
    COMMON_AddListOption( "App Info",
                            &img_app_info,
                            &pCtrlPaneOptionsArray[ CTRLPANEL_eOptionAppInfo ],
                            NULL,
                            pCtrlPanelListObj
                          );
    COMMON_AddListOption( "Settings",
                            &img_settings,
                            &pCtrlPaneOptionsArray[ CTRLPANEL_eOptionSettings ],
                            NULL,
                            pCtrlPanelListObj
                          );
    COMMON_AddListOption( "Theme",
                            &img_theme,
                            &pCtrlPaneOptionsArray[ CTRLPANEL_eOptionTheme ],
                            NULL,
                            pCtrlPanelListObj
                          );

    /* Add Circular Scroll callback to the CtrlPanel List Obj */
    lv_obj_add_event_cb( pCtrlPanelListObj, COMMON_ListCircularScrollCallback, LV_EVENT_SCROLL, ( void * )&isCircularScroll );

}
