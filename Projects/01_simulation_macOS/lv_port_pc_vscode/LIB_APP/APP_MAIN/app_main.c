/**
  ******************************************************************************
  * @file           : app_main.c
  * @brief          : Module for main application
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

#include "app_main.h"

/* Typedef -------------------------------------------------------------------*/


/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/

/* Main User Watch Object */
APP_zUserWatchObj_t APP_zMainUserWatchObj = { 0 };

/* Function prototypes -------------------------------------------------------*/

static void app_CreateMainContainer( APP_zUserWatchObj_t *pUserWatchObj );

/* User code -----------------------------------------------------------------*/

/**
 * @brief Initialize the Clock and Control Panel Objects
 *
 */
void APP_Init( void )
{
    /* Create the main container for the clock and control panel */
    app_CreateMainContainer( &APP_zMainUserWatchObj );

    /* Create the Clock Screen */
    CLOCK_Init( &APP_zMainUserWatchObj.zClockObj, APP_zMainUserWatchObj.pMainWatchContainer );

    /* Create the Control Panel Screen */
    CTRLPANEL_Init( &APP_zMainUserWatchObj.zCtrlPanelObj, APP_zMainUserWatchObj.pMainWatchContainer );
}



/**
 * @brief Create the main container for the clock and control panel
 *
 * @param pUserWatchObj Pointer to the main user watch object
 */
static void app_CreateMainContainer( APP_zUserWatchObj_t *pUserWatchObj )
{
    /* Create empty container, register it and remove the default style */
    lv_obj_t *pMainContainerObj = lv_obj_create( lv_scr_act( ) );
    COMMON_RegisterUserObj( pMainContainerObj, COMMON_eTypeDontTrack );
    lv_obj_remove_style_all( pMainContainerObj );

    /* Set size of Container Object */
    lv_obj_set_size( pMainContainerObj, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT );

    /* Configure horizontal scroll on the main container */
    lv_obj_add_flag( pMainContainerObj, LV_OBJ_FLAG_SCROLL_ONE );
    lv_obj_set_scroll_snap_x( pMainContainerObj, LV_SCROLL_SNAP_START );
    lv_obj_set_scroll_dir( pMainContainerObj, LV_DIR_HOR );
    lv_obj_set_scrollbar_mode( pMainContainerObj, LV_SCROLLBAR_MODE_OFF );

    /* Use FLEX layout with horizontal flow */
    lv_obj_set_layout( pMainContainerObj, LV_LAYOUT_FLEX );
    lv_obj_set_flex_flow( pMainContainerObj, LV_FLEX_FLOW_ROW ); // Add children horizontally

    /* Remove all spacing/padding of the container style */
    lv_obj_set_style_pad_all( pMainContainerObj, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_row( pMainContainerObj, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_column( pMainContainerObj, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_gap( pMainContainerObj, 0, LV_PART_MAIN );

    /* Add Main container to the watch obj */
    pUserWatchObj->pMainWatchContainer = pMainContainerObj;
}
