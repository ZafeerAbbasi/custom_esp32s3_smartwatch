/**
  ******************************************************************************
  * @file           : app_user.c
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

#include "app_user.h"

/* Typedef -------------------------------------------------------------------*/


/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/

/* Main User Watch Object */
COMMON_zUserWatchObj_t APP_zMainUserWatchObj = { 0 };

/* Function prototypes -------------------------------------------------------*/

static void app_CreateMainContainer( COMMON_zUserWatchObj_t *pUserWatchObj );

/* User code -----------------------------------------------------------------*/

/**
 * @brief Initialize the Clock and Control Panel Objects
 *
 */
void APP_Init( void )
{
    /* Create the main container for the clock and control panel */
    app_CreateMainContainer( &APP_zMainUserWatchObj );

    /* Create the Clock Object */
    CLOCK_Init( &APP_zMainUserWatchObj );

    /* Create the Control Panel Object */
}



/**
 * @brief Create the main container for the clock and control panel
 *
 * @param pUserWatchObj Pointer to the main user watch object
 */
static void app_CreateMainContainer( COMMON_zUserWatchObj_t *pUserWatchObj )
{
    lv_style_t *pMainContainerStyle = &pUserWatchObj->zMainWatchContainer.userWidgetStyle;

    /* Create empty container and remove the default style */
    lv_obj_t *pMainContainerObj = lv_obj_create( lv_scr_act( ) );
    lv_obj_remove_style_all( pMainContainerObj );

    /* Clear the style we will use for the container */
    lv_style_init( pMainContainerStyle );

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
    lv_style_set_pad_all( pMainContainerStyle, 0 );
    lv_style_set_pad_row( pMainContainerStyle, 0 );
    lv_style_set_pad_column( pMainContainerStyle, 0 );
    lv_style_set_pad_gap( pMainContainerStyle, 0 );

    /* Add style to container obj */
    lv_obj_add_style( pMainContainerObj, pMainContainerStyle, LV_PART_MAIN );

    pUserWatchObj->zMainWatchContainer.pUserWidget = pMainContainerObj;
}
