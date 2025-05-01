/**
  ******************************************************************************
  * @file           : app_settings.c
  * @brief          : Contains functions related to the settings screen
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

#include "app_settings.h"

/* Typedef -------------------------------------------------------------------*/


/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/


/* Function prototypes -------------------------------------------------------*/

static void settings_BuildSettingsScreen( lv_timer_t *pTimer );
static void exit_btn_event_cb(lv_event_t *e);
static void settings_FinishScreenBuilding( lv_timer_t *pTimer );
static void fade_out_cb(void *obj, int32_t v);
static void fade_out_anim_ready_cb(lv_anim_t *a);

/* User code -----------------------------------------------------------------*/

/**
 * @brief Creates the Settings loading screen and starts building
 * the settings screen
 *
 * @param pEvent Pointer to the event
 */
void SETTINGS_InitCb( lv_event_t *pEvent )
{
    SETTINGS_zUserSettingsObj_t *pUserSettingsObj = ( SETTINGS_zUserSettingsObj_t * )lv_event_get_user_data( pEvent );
    lv_obj_t **ppLoadingScreen = &pUserSettingsObj->pSettingsLoadingScreen;

    /* First lets create the loading screen
    to display while the actual settings screen is being made
    We create the screen in the callback because creating it at the start
    and keeping it in ram will slow down the application */
    *ppLoadingScreen = lv_obj_create( lv_scr_act( ) );

    /* Configure Loading Screen */
    lv_obj_remove_style_all( *ppLoadingScreen );
    lv_obj_set_size( *ppLoadingScreen, LV_PCT( 100 ), LV_PCT( 100 ) );
    lv_obj_set_style_bg_opa( *ppLoadingScreen, LV_OPA_COVER, 0 );
    lv_obj_set_style_bg_color( *ppLoadingScreen, lv_color_black(), 0 );
    lv_obj_clear_flag( *ppLoadingScreen, LV_OBJ_FLAG_SCROLLABLE );

    /* Add Image to loading screen */
    lv_obj_t *pImg = lv_img_create( *ppLoadingScreen );
    lv_img_set_src( pImg, ( const void * )&img_settings );
    lv_img_set_zoom( pImg, 200 );
    lv_obj_center( pImg );

    /* Start building the settings menu while loading screen is visible */
    lv_timer_create( settings_BuildSettingsScreen, 50, ( void * )pUserSettingsObj );

}


static void settings_BuildSettingsScreen( lv_timer_t *pTimer )
{
    #ifdef USE_SDL
        SETTINGS_zUserSettingsObj_t *pUserSettingsObj       = ( SETTINGS_zUserSettingsObj_t * )lv_timer_get_user_data( pTimer );
    #else
        SETTINGS_zUserSettingsObj_t *pUserSettingsObj       = ( SETTINGS_zUserSettingsObj_t * )pTimer->user_data;
    #endif

    lv_obj_t **ppSettingsContainerObj                   = &pUserSettingsObj->pSettingsContainerObj;
    lv_obj_t **ppSettingsListObj                        = &pUserSettingsObj->pSettingsListObj;
    COMMON_zCustomListOption_t *pSettingsOptionsArray   = pUserSettingsObj->aSettingsOptions;
    lv_obj_t **ppExitBtn                                = &pUserSettingsObj->pSettingsExitBtn;
    lv_obj_t **ppExitBtnLabel                           = &pUserSettingsObj->pSettingsExitBtnLabel;
    lv_obj_t **ppLoadingScreen                          = &pUserSettingsObj->pSettingsLoadingScreen;

    /* Create the Settings container and remove default styling */
    *ppSettingsContainerObj = lv_obj_create( lv_scr_act( ) );
    lv_obj_add_flag( *ppSettingsContainerObj, LV_OBJ_FLAG_HIDDEN ); // Hide initially
    COMMON_RegisterUserObj(  *ppSettingsContainerObj, COMMON_eTypeContainer );

    /* Bring Loading screen to the front */
    lv_obj_move_foreground( *ppLoadingScreen );

    lv_obj_remove_style_all( *ppSettingsContainerObj );
    lv_obj_set_size( *ppSettingsContainerObj, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT );
    lv_obj_add_style( *ppSettingsContainerObj, &COMMON_aThemeStyles[ COMMON_eThemeDark ], LV_PART_MAIN );

    /* Create the Settings List on the Settings container */
    *ppSettingsListObj = lv_obj_create( *ppSettingsContainerObj );

    /* Configure the Settings List */
    COMMON_SetupCustomListObj( *ppSettingsListObj );

    /* Create List options on the SettingsList */
    COMMON_AddCustomListOption( "Brightness",
                                &img_brightness,
                                80,
                                &pSettingsOptionsArray[ SETTINGS_eOptionScreenBrightness ],
                                *ppSettingsListObj );

    /* TODO: Add rest of settings options */

    // Create Exit button
    *ppExitBtn  = lv_btn_create( *ppSettingsContainerObj );
    COMMON_RegisterUserObj( *ppExitBtn, COMMON_eTypeBtn );
    lv_obj_align( *ppExitBtn , LV_ALIGN_TOP_LEFT, 10, 10 );

    *ppExitBtnLabel = lv_label_create( *ppExitBtn );
    COMMON_RegisterUserObj( ppExitBtnLabel, COMMON_eTypeLabel );
    lv_label_set_text( *ppExitBtnLabel, "Exit" );

    // Register the callback
    lv_obj_add_event_cb( *ppExitBtnLabel, exit_btn_event_cb, LV_EVENT_CLICKED, ( void * )ppSettingsContainerObj );

    /* Create a timer to initiate the loading screen fade, and show the settings screen */
    lv_timer_create( settings_FinishScreenBuilding, 500, ( void * )pUserSettingsObj );  // 100ms delay

    /* Delete the timer so we don't call this function again */
    lv_timer_del( pTimer );
}


// Step 3: Called after settings screen is created
static void settings_FinishScreenBuilding( lv_timer_t *pTimer )
{
    #ifdef USE_SDL
        SETTINGS_zUserSettingsObj_t *pUserSettingsObj       = ( SETTINGS_zUserSettingsObj_t * )lv_timer_get_user_data( pTimer );
    #else
        SETTINGS_zUserSettingsObj_t *pUserSettingsObj       = ( SETTINGS_zUserSettingsObj_t * )pTimer->user_data;
    #endif

    lv_obj_t **ppLoadingScreen      = &pUserSettingsObj->pSettingsLoadingScreen;
    lv_obj_t **ppSettingsContainer  = &pUserSettingsObj->pSettingsContainerObj;

    // Animate loading screen fade out
    lv_anim_t zAnimation;
    lv_anim_init( &zAnimation );
    lv_anim_set_var( &zAnimation, *ppLoadingScreen );
    lv_anim_set_exec_cb( &zAnimation, fade_out_cb );
    lv_anim_set_time( &zAnimation, 300 ); // 300ms fade
    lv_anim_set_values( &zAnimation, LV_OPA_COVER, LV_OPA_TRANSP );
    lv_anim_set_ready_cb( &zAnimation, fade_out_anim_ready_cb );
    lv_anim_start( &zAnimation );

    /* Remove the hidden flag from settings screen, the loading screen is still in front right now */
    lv_obj_clear_flag( *ppSettingsContainer, LV_OBJ_FLAG_HIDDEN );

    /* Delete the timer so we don't call this function again */
    lv_timer_del( pTimer );
}

// Callback function
static void exit_btn_event_cb(lv_event_t *e)
{
    lv_obj_t *pSettingsContainerObj = ( lv_obj_t * )lv_event_get_user_data( e );
    if (pSettingsContainerObj) {
        lv_obj_del(pSettingsContainerObj);
        pSettingsContainerObj = NULL;
    }
}

// Fade-out + delete animation callback
static void fade_out_cb(void *obj, int32_t v)
{
    lv_obj_set_style_opa((lv_obj_t *)obj, v, 0);
}

static void fade_out_anim_ready_cb(lv_anim_t *a)
{
    lv_obj_del((lv_obj_t *)a->var);
}
