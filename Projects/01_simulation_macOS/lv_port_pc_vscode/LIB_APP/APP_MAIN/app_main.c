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

/* Main Usr Watch Object */
APP_zUsrWatchObj_t APP_zMainUsrWatchObj = { 0 };

/* Function prototypes -------------------------------------------------------*/

static void app_CreateMainCont( APP_zUsrWatchObj_t *pUsrWatchObj );

/* User code -----------------------------------------------------------------*/

/**
 * @brief Initialize the Clock and Control Panel Objects
 *
 */
void APP_Init( void )
{
    /* Initalize the styles which are used by multiple modules */
    COMMON_InitStyles( );

    /* Create the main Cont for the Clock and control panel */
    app_CreateMainCont( &APP_zMainUsrWatchObj );

    /* Create the Clock Screen */
    Clock_Init( &APP_zMainUsrWatchObj.zClockObj, APP_zMainUsrWatchObj.pMainWatchCont );

    /* Create the Control Panel Screen */
    CTRLPANEL_Init( &APP_zMainUsrWatchObj.zCtrlPanelObj, APP_zMainUsrWatchObj.pMainWatchCont );
}



/**
 * @brief Create the main Container on which the clock and ctrlpanel
 * will be placed on
 *
 * @param pUsrWatchObj Pointer to the main Usr watch object
 */
static void app_CreateMainCont( APP_zUsrWatchObj_t *pUsrWatchObj )
{
    /* Create empty Cont, register it and remove the default style */
    lv_obj_t *pMainContObj = lv_obj_create( lv_scr_act( ) );
    COMMON_RegisterUsrObj( pMainContObj, COMMON_eTypeCont );
    lv_obj_remove_style_all( pMainContObj );

    /* Set size of Cont Object */
    lv_obj_set_size( pMainContObj, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT );

    /* Add style according to current theme */
    COMMON_ApplyCurrThemeStyle( pMainContObj, COMMON_eTypeCont );

    /* Configure horizontal scroll on the main Cont */
    lv_obj_add_flag( pMainContObj, LV_OBJ_FLAG_SCROLL_ONE );
    lv_obj_set_scroll_snap_x( pMainContObj, LV_SCROLL_SNAP_START );
    lv_obj_set_scroll_dir( pMainContObj, LV_DIR_HOR );
    lv_obj_set_scrollbar_mode( pMainContObj, LV_SCROLLBAR_MODE_OFF );

    /* Use FLEX layout with horizontal flow */
    lv_obj_set_layout( pMainContObj, LV_LAYOUT_FLEX );
    lv_obj_set_flex_flow( pMainContObj, LV_FLEX_FLOW_ROW ); // Add children horizontally

    /* Remove all spacing/padding of the Cont style */
    lv_obj_set_style_pad_all( pMainContObj, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_row( pMainContObj, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_column( pMainContObj, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_gap( pMainContObj, 0, LV_PART_MAIN );

    /* Add Main Cont to the watch obj */
    pUsrWatchObj->pMainWatchCont = pMainContObj;
}
