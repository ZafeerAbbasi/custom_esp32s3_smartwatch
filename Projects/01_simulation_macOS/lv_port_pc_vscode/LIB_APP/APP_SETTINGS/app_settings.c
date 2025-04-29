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

/* Pointer to Settings Loading screen, needs to be static because it is
used by another callback during the transtition from loading screen
to actual settings menu */
static lv_obj_t *settings_pSettingsLoadingScreen = NULL;

static lv_obj_t *settings_pSettingsScreen = NULL;

/* Function prototypes -------------------------------------------------------*/

void settings_BuildSettingsScreen( lv_timer_t *pTimer );
static void exit_btn_event_cb(lv_event_t *e);
static void finish_screen_build(lv_timer_t *t);
static void fade_out_cb(void *obj, int32_t v);

/* User code -----------------------------------------------------------------*/

/**
 * @brief Creates the Settings loading screen and starts building
 * the settings screen
 *
 * @param pEvent Pointer to the event
 */
void SETTINGS_InitCallback( lv_event_t *pEvent )
{
    /* First lets create the loading screen
    to display while the actual settings screen is being made

    We create the screen in the callback because creating it at the start
    and keeping it in ram will slow down the application */
    settings_pSettingsLoadingScreen = lv_obj_create( lv_scr_act( ) );
    lv_obj_remove_style_all( settings_pSettingsLoadingScreen );
    lv_obj_set_size(settings_pSettingsLoadingScreen, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_opa(settings_pSettingsLoadingScreen, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(settings_pSettingsLoadingScreen, lv_color_black(), 0);
    lv_obj_clear_flag(settings_pSettingsLoadingScreen, LV_OBJ_FLAG_SCROLLABLE);

    /* Add Image to loading screen */
    lv_obj_t *pImg = lv_img_create( settings_pSettingsLoadingScreen );
    lv_img_set_src( pImg, ( const void * )&img_settings );
    lv_img_set_zoom( pImg, 200 );
    lv_obj_center( pImg );

    /* Start building the settings menu while loading screen is visible */
    lv_timer_create( settings_BuildSettingsScreen, 50, lv_event_get_user_data( pEvent ) );

}


void settings_BuildSettingsScreen( lv_timer_t *pTimer )
{
    SETTINGS_zUserSettingsObj_t *pUserSettingsObj       = ( SETTINGS_zUserSettingsObj_t * )lv_timer_get_user_data( pTimer );
    lv_obj_t *pSettingsContainerObj                     = pUserSettingsObj->pSettingsContainerObj;
    lv_obj_t *pSettingsListObj                          = pUserSettingsObj->pSettingsListObj;
    COMMON_zCustomListOption_t *pSettingsOptionsArray   = pUserSettingsObj->aSettingsOptions;

    /* Create the Settings container and remove default styling */
    pSettingsContainerObj = lv_obj_create(lv_scr_act( ));
    lv_obj_add_flag(pSettingsContainerObj, LV_OBJ_FLAG_HIDDEN); // Hide initially
    COMMON_RegisterUserObj( pSettingsContainerObj, COMMON_eTypeContainer );

    /* Bring Loading screen to the front */
    lv_obj_move_foreground( settings_pSettingsLoadingScreen );

    lv_obj_remove_style_all( pSettingsContainerObj );
    lv_obj_set_size( pSettingsContainerObj, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT );
    lv_obj_set_style_bg_opa( pSettingsContainerObj, LV_OPA_COVER, LV_PART_MAIN );
    lv_obj_set_style_bg_color(pSettingsContainerObj, lv_color_make( 13, 17, 23 ), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_color(pSettingsContainerObj, lv_color_make( 40, 52, 71 ), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(pSettingsContainerObj, LV_GRAD_DIR_VER, LV_PART_MAIN);

    /* Create the Settings List on the Settings container */
    pSettingsListObj = lv_obj_create( pSettingsContainerObj );
    COMMON_RegisterUserObj( pSettingsListObj, COMMON_eTypeDontTrack );

    /* Configure the Settings List */
    COMMON_SetupCustomListObj( pSettingsListObj );

    /* Create List options on the SettingsList */
    COMMON_AddCustomListOption( "Brightness",
                                &img_brightness,
                                80,
                                &pSettingsOptionsArray[ SETTINGS_eOptionScreenBrightness ],
                                pSettingsListObj );

    /* TODO: Add rest of settings options */

    // Create Exit button
    lv_obj_t *pExitBtn = lv_btn_create(pSettingsContainerObj);
    lv_obj_align(pExitBtn, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_t *label = lv_label_create(pExitBtn);
    lv_label_set_text(label, "Exit");

    settings_pSettingsScreen                            = pSettingsContainerObj;
    lv_obj_clear_flag(settings_pSettingsScreen, LV_OBJ_FLAG_HIDDEN);

    // Register the callback
    lv_obj_add_event_cb(pExitBtn, exit_btn_event_cb, LV_EVENT_CLICKED, ( void * )pSettingsContainerObj );

    lv_timer_create(finish_screen_build, 500, NULL);  // 100ms delay
    lv_timer_del(pTimer);
}


// Step 3: Called after settings screen is created
static void finish_screen_build(lv_timer_t *t)
{

    // 2. Animate loading screen fade out
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, settings_pSettingsLoadingScreen);
    lv_anim_set_exec_cb(&a, fade_out_cb);
    lv_anim_set_time(&a, 1000); // 300ms fade
    lv_anim_set_values(&a, LV_OPA_COVER, LV_OPA_TRANSP);
    lv_anim_start(&a);

    lv_timer_del(t);
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
    if (v == LV_OPA_TRANSP) {
        lv_obj_del((lv_obj_t *)obj);
    }
}
