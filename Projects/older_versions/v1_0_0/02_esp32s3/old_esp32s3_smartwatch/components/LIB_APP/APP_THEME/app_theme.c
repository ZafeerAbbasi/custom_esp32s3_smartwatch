/**
  ******************************************************************************
  * @file           : app_theme.c
  * @brief          : Contains functions related to the theme settings
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

#include "app_theme.h"
#include <string.h>

/* Typedef -------------------------------------------------------------------*/

/**
 * @brief Theme Obj Node Typedef
 * @note Used to iterate through the theme objects
 */
typedef struct theme_zObjNode
{
    lv_obj_t                *pObj;
    COMMON_eUsrObjType_t    eObjType;
} theme_zObjNode;

/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/

static theme_zObjNode theme_aObjNodes[ 20 ] = { 0 };
static int theme_objCnt                     = 0;

/* Function prototypes -------------------------------------------------------*/

static void theme_BuildThemeScreen( lv_timer_t *pTimer );
static void theme_FinishScreenBuilding( lv_timer_t *pTimer );

static void theme_FadeOutCb( void *pObj, int32_t value );
static void theme_FadeOutCompletedCb( lv_anim_t *pAnimation );
static void theme_ExitBtnCb( lv_event_t *pEvent );
static void theme_SwitchCb( lv_event_t *pEvent );

static void theme_CreateExitBtn( THEME_zUsrThemeObj_t *pThemeObj );
static void theme_CreateThemeSwitch( Theme_zThemeSwitch_t *pOpt, lv_obj_t *pParent );

static void theme_ApplyThemeOnCurrScr( void );

/* User code -----------------------------------------------------------------*/

/**
 * @brief Creates the Theme loading screen and starts building
 * the theme screen
 *
 * @param pEvent Pointer to the event
 */
void THEME_InitCb( lv_event_t *pEvent )
{
    THEME_zUsrThemeObj_t *pUsrThemeObj  = ( THEME_zUsrThemeObj_t * )lv_event_get_user_data( pEvent );
    lv_obj_t **ppLoadingScreen          = &pUsrThemeObj->pThemeLoadingScreen;

    /* First lets create the loading screen
    to display while the actual settings screen is being made
    We create the screen in the callback because creating it at the start
    and keeping it in ram will slow down the application */
    *ppLoadingScreen = lv_obj_create( lv_scr_act( ) );

    /* Configure Loading Screen */
    lv_obj_remove_style_all( *ppLoadingScreen );
    lv_obj_set_size( *ppLoadingScreen, LV_PCT( 100 ), LV_PCT( 100 ) );
    lv_obj_set_style_bg_opa( *ppLoadingScreen, LV_OPA_COVER, 0 );
    lv_obj_clear_flag( *ppLoadingScreen, LV_OBJ_FLAG_SCROLLABLE );
    COMMON_ApplyCurrThemeStyle( *ppLoadingScreen, COMMON_eTypeLoadingScr );

    /* Add Image to loading screen */
    lv_obj_t *pImg = lv_img_create( *ppLoadingScreen );
    lv_img_set_src( pImg, ( const void * )&img_theme );
    lv_img_set_zoom( pImg, 200 );
    lv_obj_center( pImg );

    /* Start building the settings menu while loading screen is visible */
    lv_timer_create( theme_BuildThemeScreen, 50, ( void * )pUsrThemeObj );

}



/**
 * @brief Build the theme screen
 *
 * @param pTimer Pointer to the timer which called this function via callback
 */
static void theme_BuildThemeScreen( lv_timer_t *pTimer )
{
    #ifdef USE_SDL
        THEME_zUsrThemeObj_t *pUsrThemeObj       = ( THEME_zUsrThemeObj_t * )lv_timer_get_user_data( pTimer );
    #else
        THEME_zUsrThemeObj_t *pUsrThemeObj       = ( THEME_zUsrThemeObj_t * )pTimer->user_data;
    #endif

    lv_obj_t **ppThemeContObj                           = &pUsrThemeObj->pThemeContObj;
    lv_obj_t **ppThemeListObj                           = &pUsrThemeObj->pThemeListObj;
    lv_obj_t **ppLoadingScreen                          = &pUsrThemeObj->pThemeLoadingScreen;
    Theme_zThemeSwitch_t *pThemeSwitch                  = &pUsrThemeObj->zThemeSwitch;

    /* Create the Theme Cont and remove default styling */
    *ppThemeContObj = lv_obj_create( lv_scr_act( ) );
    lv_obj_add_flag( *ppThemeContObj, LV_OBJ_FLAG_HIDDEN ); // Hide initially

    /* Bring Loading screen to the front */
    lv_obj_move_foreground( *ppLoadingScreen );

    /* Configure the theme Cont */
    lv_obj_set_style_border_width( *ppThemeContObj, 0, LV_PART_MAIN );
    lv_obj_set_size( *ppThemeContObj, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT );
    COMMON_ApplyCurrThemeStyle( *ppThemeContObj, COMMON_eTypeCont );
    theme_aObjNodes[ theme_objCnt ] = ( theme_zObjNode ){ *ppThemeContObj, COMMON_eTypeCont };
    theme_objCnt++;

    /* Create the Settings List on the Settings Cont */
    *ppThemeListObj = lv_obj_create( *ppThemeContObj );

    /* Configure the Settings List */
    COMMON_SetupCustomListObj( *ppThemeListObj );

    /* Exit Button */
    theme_CreateExitBtn( pUsrThemeObj );

    /* Circular Scroll */
    theme_CreateThemeSwitch( pThemeSwitch, *ppThemeListObj );

    /* Manually send first event to enable scrolling effect */
    #ifdef USE_SDL
        lv_obj_send_event( *ppThemeListObj, LV_EVENT_SCROLL, NULL);
    #else
        lv_event_send( *ppThemeListObj, LV_EVENT_SCROLL, NULL);
    #endif

    /* Create a timer to initiate the loading screen fade, and show the settings screen */
    lv_timer_create( theme_FinishScreenBuilding, 500, ( void * )pUsrThemeObj );  // 100ms delay

    /* Delete the timer so we don't call this function again */
    lv_timer_del( pTimer );
}



/**
 * @brief Create the Settings Exit Button
 *
 * @param pThemeObj Pointer to the Usr Settings Obj
 */
static void theme_CreateExitBtn( THEME_zUsrThemeObj_t *pThemeObj )
{
    lv_obj_t **ppExitBtn            = &pThemeObj->zThemeExitBtn.pBtnCont;
    lv_obj_t **ppLabel              = &pThemeObj->zThemeExitBtn.pBtnLabel;
    lv_obj_t **ppThemeCont          = &pThemeObj->pThemeContObj;

    /* Create Exit Button on parent and register it */
    *ppExitBtn = lv_btn_create( *ppThemeCont );
    lv_obj_set_size( *ppExitBtn, LV_SIZE_CONTENT, LV_SIZE_CONTENT );
    lv_obj_align( *ppExitBtn, LV_ALIGN_TOP_LEFT, 1, 1 );

    /* Exit Button Label */
    *ppLabel = lv_label_create( *ppExitBtn );
    lv_label_set_text( *ppLabel, "Exit" );

    /* Register Exit button callback */
    lv_obj_add_event_cb( *ppExitBtn, theme_ExitBtnCb, LV_EVENT_CLICKED, ( void * )ppThemeCont );
}



/**
 * @brief Create the Circular Scroll Setting
 *
 * @param pOpt Pointer to the CircScroll Option Struct
 * @param pParent Pointer to the parent to place the List option on
 */
static void theme_CreateThemeSwitch( Theme_zThemeSwitch_t *pOpt, lv_obj_t *pParent )
{
    lv_obj_t **ppPanel          = &pOpt->zBasicOptionObjs.pOptPanel;
    lv_obj_t **ppImg            = &pOpt->zBasicOptionObjs.pOptImg;
    lv_obj_t **ppLabel          = &pOpt->zBasicOptionObjs.pOptLabel;
    lv_obj_t **ppSwitch         = &pOpt->pSwitch;
    lv_obj_t **ppSwitchLabel    = &pOpt->pSwitchLabel;

    /* Circular Scroll Option Panel on Settings List */
    *ppPanel = lv_obj_create(pParent);
    lv_obj_set_width(*ppPanel, 200);
    lv_obj_set_height(*ppPanel, 90);
    lv_obj_set_align(*ppPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(*ppPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(*ppPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(*ppPanel, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(*ppPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(*ppPanel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(*ppPanel, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(*ppPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(*ppPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(*ppPanel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(*ppPanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    COMMON_ApplyCurrThemeStyle( *ppPanel, COMMON_eTypeLstOptPanel );
    theme_aObjNodes[ theme_objCnt ] = ( theme_zObjNode ){ *ppPanel, COMMON_eTypeLstOptPanel };
    theme_objCnt++;

    /* "Circular Scroll" Label on panel */
    *ppLabel = lv_label_create(*ppPanel);
    lv_obj_set_width(*ppLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(*ppLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(*ppLabel, 45);
    lv_obj_set_y(*ppLabel, 5);
    lv_label_set_text(*ppLabel, "Theme");
    lv_obj_set_style_text_font( *ppLabel, &lv_font_montserrat_16, LV_PART_MAIN );
    COMMON_ApplyCurrThemeStyle( *ppLabel, COMMON_eTypeLabel );
    theme_aObjNodes[ theme_objCnt ] = ( theme_zObjNode ){ *ppLabel, COMMON_eTypeLabel };
    theme_objCnt++;

    /* Brightness Icon */
    *ppImg = lv_img_create(*ppPanel);
    lv_img_set_src(*ppImg, &img_theme);
    lv_obj_set_width(*ppImg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(*ppImg, LV_SIZE_CONTENT); /// 1
    lv_obj_align_to( *ppImg, *ppLabel, LV_ALIGN_OUT_LEFT_MID, 25, 0 );
    lv_obj_add_flag(*ppImg, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
    lv_obj_clear_flag(*ppImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_zoom(*ppImg, 100);

    /* Create Switch */
    *ppSwitch = lv_switch_create( *ppPanel );
    lv_obj_align_to( *ppSwitch, *ppLabel, LV_ALIGN_OUT_BOTTOM_LEFT, -15, 15 );
    lv_obj_add_state( *ppSwitch, COMMON_eCurrTheme ? LV_STATE_CHECKED : LV_STATE_DEFAULT );
    COMMON_ApplyCurrThemeStyle( *ppSwitch, COMMON_eTypeSwitch );
    lv_obj_add_event_cb( *ppSwitch, theme_SwitchCb, LV_EVENT_VALUE_CHANGED, ( void * )pOpt );
    theme_aObjNodes[ theme_objCnt ] = ( theme_zObjNode ){ *ppSwitch, COMMON_eTypeSwitch };
    theme_objCnt++;

    /* Switch Label */
    *ppSwitchLabel = lv_label_create( *ppPanel );
    lv_obj_align_to( *ppSwitchLabel, *ppSwitch, LV_ALIGN_OUT_RIGHT_MID, 20, 0 );
    lv_label_set_text( *ppSwitchLabel, lv_obj_has_state( *ppSwitch, LV_STATE_CHECKED ) ? "Light" : "Dark" );
    COMMON_ApplyCurrThemeStyle( *ppSwitchLabel, COMMON_eTypeLabel );
    theme_aObjNodes[ theme_objCnt ] = ( theme_zObjNode ){ *ppSwitchLabel, COMMON_eTypeLabel };
    theme_objCnt++;

}




/**
 * @brief Finish building the screen and initiate loading screen fade
 *
 * @param pTimer Pointer to the timer which called this function via callback
 */
static void theme_FinishScreenBuilding( lv_timer_t *pTimer )
{
    #ifdef USE_SDL
        THEME_zUsrThemeObj_t *pUsrThemeObj       = ( THEME_zUsrThemeObj_t * )lv_timer_get_user_data( pTimer );
    #else
        THEME_zUsrThemeObj_t *pUsrThemeObj       = ( THEME_zUsrThemeObj_t * )pTimer->user_data;
    #endif

    lv_obj_t **ppLoadingScreen      = &pUsrThemeObj->pThemeLoadingScreen;
    lv_obj_t **ppThemeCont          = &pUsrThemeObj->pThemeContObj;

    // Animate loading screen fade out
    lv_anim_t zAnimation;
    lv_anim_init( &zAnimation );
    lv_anim_set_var( &zAnimation, *ppLoadingScreen );
    lv_anim_set_exec_cb( &zAnimation, theme_FadeOutCb );
    lv_anim_set_time( &zAnimation, 300 ); // 300ms fade
    lv_anim_set_values( &zAnimation, LV_OPA_COVER, LV_OPA_TRANSP );
    lv_anim_set_ready_cb( &zAnimation, theme_FadeOutCompletedCb );
    lv_anim_start( &zAnimation );

    /* Remove the hidden flag from settings screen, the loading screen is still in front right now */
    lv_obj_clear_flag( *ppThemeCont, LV_OBJ_FLAG_HIDDEN );

    /* Delete the timer so we don't call this function again */
    lv_timer_del( pTimer );
}



static void theme_SwitchCb( lv_event_t *pEvent )
{
    Theme_zThemeSwitch_t *pOpt                          = ( Theme_zThemeSwitch_t * )lv_event_get_user_data( pEvent );
    lv_obj_t **ppSwitchLabel                            = &pOpt->pSwitchLabel;
    lv_obj_t **ppSwitch                                 = &pOpt->pSwitch;
    bool isSwitchChecked                                = lv_obj_has_state( *ppSwitch, LV_STATE_CHECKED );

    /* Update Label */
    lv_label_set_text( *ppSwitchLabel,
                        isSwitchChecked ? "Light" : "Dark" );

    /* Update Curr Theme Flag */
    COMMON_ChangeCurrThemeFlag( isSwitchChecked ? COMMON_eThemeLight : COMMON_eThemeDark );

    /* First update the theme for the Theme Page */
    theme_ApplyThemeOnCurrScr( );

    /* Update the theme for other objs */
    COMMON_SetAllObjsTheme( );
}



static void theme_ApplyThemeOnCurrScr( void )
{
    lv_obj_t *pObj                  = NULL;
    COMMON_eUsrObjType_t eObjType   = COMMON_eTypeDontTrack;

    /* Loop through all theme objs */
    for( int cnt = 0; cnt < theme_objCnt; cnt++ )
    {
        pObj        = theme_aObjNodes[ cnt ].pObj;
        eObjType    = theme_aObjNodes[ cnt ].eObjType;

        /* Apply the current theme style for each object */
        COMMON_ApplyCurrThemeStyle( pObj, eObjType );
    }
}



/**
 * @brief Settings Exit Button callback
 *
 * @param pEvent Pointer to the event
 */
static void theme_ExitBtnCb( lv_event_t *pEvent )
{
    lv_obj_t **pThemeContObj = ( lv_obj_t ** )lv_event_get_user_data( pEvent );

    /* Clear contents of theme objs array */
    theme_objCnt = 0;
    memset( theme_aObjNodes, 0, sizeof( theme_aObjNodes ) );

    if ( *pThemeContObj )
    {
        lv_obj_del( *pThemeContObj );
        *pThemeContObj = NULL;
    }
}



/**
 * @brief Fade out callback for loading screen
 *
 * @param pObj Pointer to the object being animated
 * @param value Value thats being changed
 */
static void theme_FadeOutCb( void *pObj, int32_t value )
{
    lv_obj_set_style_opa( ( lv_obj_t * )pObj, value, LV_PART_MAIN );
}



/**
 * @brief Fade out completed callback
 *
 * @param pAnimation Pointer to the animation
 */
static void theme_FadeOutCompletedCb( lv_anim_t *pAnimation )
{
    lv_obj_del( ( lv_obj_t * )pAnimation->var );
}
