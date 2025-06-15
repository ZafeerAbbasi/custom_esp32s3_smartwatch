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
#include "lcd.h"

/* Typedef -------------------------------------------------------------------*/


/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/


/* Function prototypes -------------------------------------------------------*/

static void settings_BuildSettingsScreen( lv_timer_t *pTimer );
static void settings_FinishScreenBuilding( lv_timer_t *pTimer );

static void settings_FadeOutCb( void *pObj, int32_t value );
static void settings_FadeOutCompletedCb( lv_anim_t *pAnimation );
static void settings_ExitBtnCb( lv_event_t *pEvent );
static void settings_BrightnessSliderCb( lv_event_t *pEvent );

static void settings_CreateBrightnessOption( SETTINGS_zListOptionBrightness_t *pBrightnessOption, lv_obj_t *pParent );

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



/**
 * @brief Build the settings screen
 *
 * @param pTimer Pointer to the timer which called this function via callback
 */
static void settings_BuildSettingsScreen( lv_timer_t *pTimer )
{
    #ifdef USE_SDL
        SETTINGS_zUserSettingsObj_t *pUserSettingsObj       = ( SETTINGS_zUserSettingsObj_t * )lv_timer_get_user_data( pTimer );
    #else
        SETTINGS_zUserSettingsObj_t *pUserSettingsObj       = ( SETTINGS_zUserSettingsObj_t * )pTimer->user_data;
    #endif

    lv_obj_t **ppSettingsContainerObj                       = &pUserSettingsObj->pSettingsContainerObj;
    lv_obj_t **ppSettingsListObj                            = &pUserSettingsObj->pSettingsListObj;
    lv_obj_t **ppLoadingScreen                              = &pUserSettingsObj->pSettingsLoadingScreen;
    SETTINGS_zListOptionBrightness_t *pBrightnessOption     = &pUserSettingsObj->zListOptionBrightness;

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

    /* Brightness setting */
    settings_CreateBrightnessOption( pBrightnessOption, *ppSettingsListObj );

    /* TODO: Add rest of settings options */

    // Exit button
    // settings_CreateExitBtn( );
    // *ppExitBtn  = lv_btn_create( *ppSettingsContainerObj );
    // COMMON_RegisterUserObj( *ppExitBtn, COMMON_eTypeBtn );
    // lv_obj_align( *ppExitBtn , LV_ALIGN_TOP_LEFT, 10, 10 );

    // *ppExitBtnLabel = lv_label_create( *ppExitBtn );
    // COMMON_RegisterUserObj( *ppExitBtnLabel, COMMON_eTypeLabel );
    // lv_label_set_text( *ppExitBtnLabel, "Exit" );

    // Register the callback
    // lv_obj_add_event_cb( *ppExitBtn, settings_ExitBtnCb, LV_EVENT_CLICKED, ( void * )ppSettingsContainerObj );

    /* Create a timer to initiate the loading screen fade, and show the settings screen */
    lv_timer_create( settings_FinishScreenBuilding, 500, ( void * )pUserSettingsObj );  // 100ms delay

    /* Delete the timer so we don't call this function again */
    lv_timer_del( pTimer );
}


/**
 * @brief Create the Screen Brightness Setting
 *
 * @param pBrightnessOption Pointer to the Brightness Option Struct
 * @param pParent Parent to place the List option on
 */
static void settings_CreateBrightnessOption( SETTINGS_zListOptionBrightness_t *pBrightnessOption, lv_obj_t *pParent )
{
    lv_obj_t **ppPanel          = &pBrightnessOption->zBasicOptionObjs.pOptionPanel;
    lv_obj_t **ppImg            = &pBrightnessOption->zBasicOptionObjs.pOptionImg;
    lv_obj_t **ppLabel          = &pBrightnessOption->zBasicOptionObjs.pOptionLabel;
    lv_obj_t **ppSlider         = &pBrightnessOption->pBrightnessSlider;
    lv_obj_t **ppSliderLabel    = &pBrightnessOption->pSliderLabel;


    *ppPanel = lv_obj_create(pParent);
    COMMON_RegisterUserObj( *ppPanel, COMMON_eTypeListOptionPanel );
    lv_obj_set_width(*ppPanel, 200);
    lv_obj_set_height(*ppPanel, 80);
    lv_obj_set_align(*ppPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(*ppPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(*ppPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(*ppPanel, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(*ppPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(*ppPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(*ppPanel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(*ppPanel, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(*ppPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(*ppPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(*ppPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(*ppPanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    *ppSlider = lv_slider_create(*ppPanel);
    lv_slider_set_range(*ppSlider, 1, 100);
    lv_slider_set_value(*ppSlider, 10, LV_ANIM_OFF);
    lv_obj_set_width(*ppSlider, 130);
    lv_obj_set_height(*ppSlider, 10);
    lv_obj_set_x(*ppSlider, -20);
    lv_obj_set_y(*ppSlider, 12);
    lv_obj_set_align(*ppSlider, LV_ALIGN_CENTER);
    lv_obj_clear_flag(*ppSlider, LV_OBJ_FLAG_GESTURE_BUBBLE); /// Flags
    lv_obj_add_event_cb( *ppSlider, settings_BrightnessSliderCb, LV_EVENT_VALUE_CHANGED, ( void * )pBrightnessOption );

    /*Create a label below the slider*/
    *ppSliderLabel = lv_label_create( *ppPanel );
    lv_label_set_text(*ppSliderLabel, "0%");
    lv_obj_set_style_text_color( *ppSliderLabel, lv_color_white( ), LV_PART_MAIN );
    lv_obj_align_to(*ppSliderLabel, *ppSlider, LV_ALIGN_OUT_RIGHT_MID, 20, 0);

    *ppLabel = lv_label_create(*ppPanel);
    lv_obj_set_width(*ppLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(*ppLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(*ppLabel, 45);
    lv_obj_set_y(*ppLabel, 5);
    lv_label_set_text(*ppLabel, "Screen Brightness");
    lv_obj_set_style_text_font( *ppLabel, &lv_font_montserrat_16, LV_PART_MAIN );
    lv_obj_set_style_text_color( *ppLabel, lv_color_white( ), LV_PART_MAIN );

    *ppImg = lv_img_create(*ppPanel);
    lv_img_set_src(*ppImg, &img_brightness);
    lv_obj_set_width(*ppImg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(*ppImg, LV_SIZE_CONTENT); /// 1
    lv_obj_align_to( *ppImg, *ppLabel, LV_ALIGN_OUT_LEFT_MID, 25, 0 );
    lv_obj_add_flag(*ppImg, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
    lv_obj_clear_flag(*ppImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_zoom(*ppImg, 80);

    /* Manually send slider event cb to update the percent label to the current slider value */
    #ifdef USE_SDL
        lv_obj_send_event( *ppSlider, LV_EVENT_VALUE_CHANGED, NULL);
    #else
        lv_event_send(*ppSlider, LV_EVENT_VALUE_CHANGED, NULL);
    #endif

}



static void settings_BrightnessSliderCb( lv_event_t *pEvent )
{
    SETTINGS_zListOptionBrightness_t *pBrightnessOption = ( SETTINGS_zListOptionBrightness_t * )lv_event_get_user_data( pEvent );
    lv_obj_t **ppSliderLabel                            = &pBrightnessOption->pSliderLabel;
    lv_obj_t **ppSliderObj                              = &pBrightnessOption->pBrightnessSlider;
    int sliderVal                                       = ( int )lv_slider_get_value( *ppSliderObj );
    char aSliderPct[ 8 ];

    /* Format the label text to show the current value of the slider */
    snprintf( aSliderPct, sizeof( aSliderPct ), "%d%%", sliderVal );
    lv_label_set_text( *ppSliderLabel, ( const char * )aSliderPct );

    /* TODO: Implement ability to control LCD Brightness using slider value */
    LCD_SetBacklightLvlPct( ( uint8_t )sliderVal );
}



/**
 * @brief Finish building the screen and initiate loading screen fade
 *
 * @param pTimer Pointer to the timer which called this function via callback
 */
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
    lv_anim_set_exec_cb( &zAnimation, settings_FadeOutCb );
    lv_anim_set_time( &zAnimation, 300 ); // 300ms fade
    lv_anim_set_values( &zAnimation, LV_OPA_COVER, LV_OPA_TRANSP );
    lv_anim_set_ready_cb( &zAnimation, settings_FadeOutCompletedCb );
    lv_anim_start( &zAnimation );

    /* Remove the hidden flag from settings screen, the loading screen is still in front right now */
    lv_obj_clear_flag( *ppSettingsContainer, LV_OBJ_FLAG_HIDDEN );

    /* Delete the timer so we don't call this function again */
    lv_timer_del( pTimer );
}



/**
 * @brief Settings Exit Button callback
 *
 * @param pEvent Pointer to the event
 */
static void settings_ExitBtnCb( lv_event_t *pEvent )
{
    lv_obj_t **ppSettingsContainerObj = ( lv_obj_t ** )lv_event_get_user_data( pEvent );

    if ( *ppSettingsContainerObj )
    {
        lv_obj_del( *ppSettingsContainerObj );
        *ppSettingsContainerObj = NULL;
    }
}



/**
 * @brief Fade out callback for loading screen
 *
 * @param pObj Pointer to the object being animated
 * @param value Value thats being changed
 */
static void settings_FadeOutCb( void *pObj, int32_t value )
{
    lv_obj_set_style_opa( ( lv_obj_t * )pObj, value, LV_PART_MAIN );
}



/**
 * @brief Fade out completed callback
 *
 * @param pAnimation Pointer to the animation
 */
static void settings_FadeOutCompletedCb( lv_anim_t *pAnimation )
{
    lv_obj_del( ( lv_obj_t * )pAnimation->var );
}
