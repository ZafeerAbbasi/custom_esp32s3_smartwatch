/**
  ******************************************************************************
  * @file           : app_common.c
  * @brief          : Module for commonly used application functions
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

#include "app_common.h"
#include <stdlib.h>

/* Typedef -------------------------------------------------------------------*/

/**
 * @brief Struct used to store Objs in the Registry
 */
typedef struct common_zObjNode
{
    lv_obj_t                    *pObj;
    COMMON_eUsrObjType_t        eObjType;
    struct common_zObjNode      *pNextNode;
} common_zObjNode;

/**
 * @brief Typedef for function pointer that is used
 * when an object is found while iterating through
 * the registry
 */
typedef void ( *COMMON_pfnObjFoundCb_t )( common_zObjNode * );

/**
 * @brief Typedef for function pointer that applies a
 * theme-based style on a user-defined obj type
 */
typedef void ( *common_pfnApplyObjTheme )( lv_obj_t * );

/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/

/* Flag to use circular scroll or not, default is true */
bool COMMON_isCircularScroll                                                    = true;

/* Flag used to track current theme */
COMMON_eTheme_t COMMON_eCurrTheme                                               = COMMON_eThemeDark;

static common_pfnApplyObjTheme common_aApplyThemeFuncs[ COMMON_eTypeCount ]     = { NULL };
static common_zObjNode *common_aNodeHeads[ COMMON_eTypeCount ]                  = { NULL };
static int common_objCount[ COMMON_eTypeCount ]                                 = { 0 };

/* Function prototypes -------------------------------------------------------*/

static void common_AddNode( lv_obj_t *pObj, COMMON_eUsrObjType_t eObjType );
static void common_RemoveNode( lv_obj_t *pObj, COMMON_eUsrObjType_t eObjType );
static void common_IterateRegistry( COMMON_eUsrObjType_t eObjType, COMMON_pfnObjFoundCb_t pObjFoundCb );

static void common_ApplyStyleLoadingScr( lv_obj_t *pObj );
static void common_ApplyStyleLstOptPanel( lv_obj_t *pObj );
static void common_ApplyStyleLabel( lv_obj_t *pObj );
static void common_ApplyStyleCont( lv_obj_t *pObj );
static void common_ApplyStyleSwitch( lv_obj_t *pObj );
static void common_ApplyStyleBtn( lv_obj_t *pObj );
static void common_ApplyStyleSlider( lv_obj_t *pObj );

/* User code -----------------------------------------------------------------*/

/**
 * @brief Set all Objs theme to current theme
 *
 */
void COMMON_SetAllObjsTheme( void )
{
    common_zObjNode *pCurrNode      = NULL;

   /* Iterate through each registry and apply the
   current theme on each object within that registry */
   for( int currType = COMMON_eTypeCont; currType < COMMON_eTypeCount; currType++ )
   {
        pCurrNode = common_aNodeHeads[ currType ];

        while( pCurrNode != NULL )
        {
            COMMON_ApplyCurrThemeStyle( pCurrNode->pObj,
                                            pCurrNode->eObjType );

            pCurrNode = pCurrNode->pNextNode;
        }
   }

}



/**
 * @brief Change the Current Theme Flag
 *
 * @param eNewTheme New value for the theme flag
 */
void COMMON_ChangeCurrThemeFlag( COMMON_eTheme_t eNewTheme )
{
    if( eNewTheme != COMMON_eCurrTheme )
    {
        COMMON_eCurrTheme = eNewTheme;
    }
}



/**
 * @brief Apply the current theme to an User - defined obj type
 *
 * @param pObj Pointer to the object to style
 * @param eObjType User - defined obj type
 */
void COMMON_ApplyCurrThemeStyle( lv_obj_t *pObj, COMMON_eUsrObjType_t eObjType )
{
    common_pfnApplyObjTheme pfnApplyTheme = common_aApplyThemeFuncs[ eObjType ];

    if( pfnApplyTheme != NULL )
    {
        pfnApplyTheme( pObj );
    }
}



/**
 * @brief Set the Scroll Mode for all Lists
 *
 * @param isCircScroll true if circular scroll, false for normal scroll
 */
void COMMON_SetAllListScroll( bool isCircScroll )
{
    bool currVal = COMMON_isCircularScroll;
    bool isChanged = ( currVal == isCircScroll ) ? false : true;
    common_zObjNode *pCurrNode = common_aNodeHeads[ COMMON_eTypeCustomLst ];

    if( isChanged )
    {
        COMMON_isCircularScroll = isCircScroll;

        /* Manually send event to all list objs to update the scroll change */

        while( pCurrNode != NULL )
        {
            if( pCurrNode->eObjType == COMMON_eTypeCustomLst )
            {
                #ifdef USE_SDL
                    lv_obj_send_event( pCurrNode->pObj, LV_EVENT_SCROLL, NULL);
                #else
                    lv_event_send( pCurrNode->pObj, LV_EVENT_SCROLL, NULL);
                #endif
            }

            pCurrNode = pCurrNode->pNextNode;
        }
    }
    else
    {
        return;
    }
}



/**
 * @brief Initialize functions used to apply
 * themes on the user-defined objs
 *
 */
void COMMON_InitStyles( void )
{
    common_aApplyThemeFuncs[ COMMON_eTypeDontTrack ]       = NULL;
    common_aApplyThemeFuncs[ COMMON_eTypeCont ]            = common_ApplyStyleCont;
    common_aApplyThemeFuncs[ COMMON_eTypeLabel ]           = common_ApplyStyleLabel;
    common_aApplyThemeFuncs[ COMMON_eTypeCustomLst ]       = NULL;
    common_aApplyThemeFuncs[ COMMON_eTypeLstOptPanel ]     = common_ApplyStyleLstOptPanel;
    common_aApplyThemeFuncs[ COMMON_eTypeLoadingScr ]      = common_ApplyStyleLoadingScr;
    common_aApplyThemeFuncs[ COMMON_eTypeBtn ]             = common_ApplyStyleBtn;
    common_aApplyThemeFuncs[ COMMON_eTypeSlider ]          = common_ApplyStyleSlider;
    common_aApplyThemeFuncs[ COMMON_eTypeSwitch ]          = common_ApplyStyleSwitch;
}



/**
 * @brief Custom List Circular Scroll Cb
 *
 * @param pEvent Pointer to Event
 */
void COMMON_ListCircularScrollCb( lv_event_t *pEvent )
{
    lv_obj_t *list = lv_event_get_target(pEvent);
    bool isCircularScroll = *( bool *)lv_event_get_user_data( pEvent );

    lv_area_t list_a;
    lv_obj_get_coords(list, &list_a);
    lv_coord_t list_y_center = list_a.y1 + lv_area_get_height(&list_a) / 2;

    lv_coord_t r = lv_obj_get_height(list) * 7 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(list);
    for (i = 0; i < child_cnt; i++)
    {
        lv_obj_t *child = lv_obj_get_child(list, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);

        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;

        lv_coord_t diff_y = child_y_center - list_y_center;
        diff_y = LV_ABS(diff_y);

        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if (diff_y >= r)
        {
                x = r;
        }
        else
        {
                /*Use Pythagoras theorem to get x from radius and y*/
                uint32_t x_sqr = r * r - diff_y * diff_y;
                lv_sqrt_res_t res;
                lv_sqrt(x_sqr, &res, 0x8000); /*Use lvgl's built in sqrt root function*/
                x = r - res.i;
        }

        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, isCircularScroll ? x : 0, 0);

    }
}



/**
 * @brief Add an Option to a List
 *
 * @param pLabelText Label for the Option
 * @param pImg Image for the Option
 * @param imgScale Image scale
 * @param pListOption Pointer to the ListOption struct
 * @param pParent Parent Obj - usually the list object
 *
 * @note WARNING: This should ONLY be used when adding options to a list that WILL NEVER
 * BE DELETED
 */
void COMMON_AddBasicLstOpt( const char *pLabelText,
                            const lv_img_dsc_t *pImg,
                            uint32_t imgScale,
                            COMMON_zBasicListOpt_t *pListOption,
                            lv_obj_t *pParent )
{
    /* Create Option Panel on the List Obj and register it */
    pListOption->pOptPanel = lv_obj_create( pParent );
    COMMON_RegisterUsrObj( pListOption->pOptPanel, COMMON_eTypeLstOptPanel );

    /* Configure Option Panel */
    lv_obj_set_width(pListOption->pOptPanel, 200);
    lv_obj_set_height(pListOption->pOptPanel, 64);
    lv_obj_set_align(pListOption->pOptPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(pListOption->pOptPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(pListOption->pOptPanel, 0, LV_PART_MAIN );
    lv_obj_set_style_bg_opa(pListOption->pOptPanel, LV_OPA_TRANSP, LV_PART_MAIN );
    lv_obj_set_style_border_opa(pListOption->pOptPanel, 255, LV_PART_MAIN );
    lv_obj_set_style_border_width(pListOption->pOptPanel, 1, LV_PART_MAIN );
    lv_obj_set_style_border_side(pListOption->pOptPanel, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN );
    lv_obj_set_style_pad_left(pListOption->pOptPanel, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_right(pListOption->pOptPanel, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_top(pListOption->pOptPanel, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_bottom(pListOption->pOptPanel, 5, LV_PART_MAIN );
    COMMON_ApplyCurrThemeStyle( pListOption->pOptPanel, COMMON_eTypeLstOptPanel );

    /* Create Option Img on the Option Panel*/
    pListOption->pOptImg = lv_img_create( pListOption->pOptPanel );

    /* Configure Option Img */
    lv_img_set_src(pListOption->pOptImg, ( const void * )pImg );
    lv_obj_set_width(pListOption->pOptImg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(pListOption->pOptImg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(pListOption->pOptImg, -74);
    lv_obj_set_y(pListOption->pOptImg, 2);
    lv_obj_set_align(pListOption->pOptImg, LV_ALIGN_CENTER);
    lv_obj_add_flag(pListOption->pOptImg, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
    lv_obj_clear_flag(pListOption->pOptImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_zoom(pListOption->pOptImg, imgScale);

    /* Create Option Label on the Option Panel and register it*/
    pListOption->pOptLabel = lv_label_create( pListOption->pOptPanel );
    COMMON_RegisterUsrObj( pListOption->pOptLabel, COMMON_eTypeLabel );

    /* Configure Option Label */
    lv_obj_set_width(pListOption->pOptLabel, 160);
    lv_obj_set_height(pListOption->pOptLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(pListOption->pOptLabel, 54);
    lv_obj_set_y(pListOption->pOptLabel, 3);
    lv_obj_set_align(pListOption->pOptLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(pListOption->pOptLabel, pLabelText);
    lv_label_set_long_mode(pListOption->pOptLabel, LV_LABEL_LONG_CLIP);
    lv_obj_set_style_text_font(pListOption->pOptLabel, &lv_font_montserrat_20, LV_PART_MAIN );
    COMMON_ApplyCurrThemeStyle( pListOption->pOptLabel, COMMON_eTypeLabel );

}



/**
 * @brief Add a Option on a Custom List
 *
 * @param pListOption Pointer to a List Option
 * @param pfnOptionClickedCb Option Clicked Callback
 * @param pUsrData Usr data to be accessed in the callback
 */
void COMMON_AddBasicLstOptCb( COMMON_zBasicListOpt_t *pListOption,
                                    lv_event_cb_t pfnOptionClickedCb,
                                    void *pUsrData )
{
    /* Add the Cb to the ListOption panel */
    lv_obj_add_event_cb( pListOption->pOptPanel,
                            pfnOptionClickedCb,
                            LV_EVENT_CLICKED,
                            pUsrData );
}



/**
 * @brief Setup and Style a default obj into a Custom List
 *
 * @param pListObj Pointer to default obj
 */
void COMMON_SetupCustomListObj( lv_obj_t *pListObj )
{
    /* Configure the List */
    lv_obj_set_width(pListObj, lv_pct(100));
    lv_obj_set_height(pListObj, lv_pct(100));
    lv_obj_set_align(pListObj, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(pListObj, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(pListObj, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(pListObj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag( pListObj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scroll_dir(pListObj, LV_DIR_VER);
    lv_obj_set_style_radius(pListObj, 0, LV_PART_MAIN );
    lv_obj_set_style_bg_opa(pListObj, LV_OPA_TRANSP, LV_PART_MAIN );
    lv_obj_set_style_border_width(pListObj, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_left(pListObj, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_right(pListObj, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_top(pListObj, 50, LV_PART_MAIN );
    lv_obj_set_style_pad_bottom(pListObj, 70, LV_PART_MAIN );

    /* Add circular scroll to the list if enabled */
    lv_obj_add_event_cb( pListObj, COMMON_ListCircularScrollCb, LV_EVENT_SCROLL, ( void * )&COMMON_isCircularScroll );
}



/**
 * @brief Register a Usr Obj to the Obj Registry
 *
 * @param pObj Pointer to the Obj Object
 * @param eObjType Type of object being registered, can be 0 or COMMON_eTypeDontTrack if
 * in case of not tracking this type of object
 *
 * @note WARNING: This should ONLY be used for objs that will NEVER BE DELETED
 */
void COMMON_RegisterUsrObj( lv_obj_t *pObj, COMMON_eUsrObjType_t eObjType )
{
    /* Register Obj to the Registry */
    common_AddNode( pObj, eObjType );
}



/**
 * @brief Un-Register a Usr Obj from the Obj Registry
 *
 *
 * @param pObj Pointer to the Obj
 * @param eObjType Type of object being registered, can be 0 or COMMON_eTypeDontTrack if
 * in case of not tracking this type of object
 */
void COMMON_UnRegisterUsrObj( lv_obj_t *pObj, COMMON_eUsrObjType_t eObjType )
{
    /* Remove Obj from Registry */
    common_RemoveNode( pObj, eObjType );
}



/**
 * @brief Add a Usr Object to the Obj Registry
 *
 * @param pObj Pointer to the Obj to Register
 * @param eObjType Type of object being registered, will be 0 if not tracking
 */
static void common_AddNode( lv_obj_t *pObj, COMMON_eUsrObjType_t eObjType )
{
    // Allocate memory for a new node
    common_zObjNode *pNewNode = ( common_zObjNode * )malloc( sizeof( common_zObjNode ) );

    if( pNewNode == NULL )
    {
        // If malloc fails, exit the function
        return;
    }

    if( eObjType == COMMON_eTypeDontTrack )
    {
        return; // Usr does not want to track this obj
    }

    // Assign the Usr Obj object and type to the new node
    pNewNode->pObj      = pObj;
    pNewNode->eObjType  = eObjType;


    // Insert the new node at the beginning of the list
    pNewNode->pNextNode = common_aNodeHeads[ eObjType ];
    common_aNodeHeads[ eObjType ] = pNewNode;

    // Increment the Obj count
    common_objCount[ eObjType ]++;
}



/**
 * @brief Remove a Usr Object from the Obj Registry
 *
 * @param pObj Pointer to the Obj Object to Un-Register
 * @param eObjType Type of object being registered, will be 0 if not tracking
 */
static void common_RemoveNode( lv_obj_t *pObj, COMMON_eUsrObjType_t eObjType )
{
    // Start from the head of the list
    common_zObjNode *pCurrNode = common_aNodeHeads[ eObjType ];
    common_zObjNode *pPrevNode = NULL;

    while( pCurrNode != NULL )
    {
        // Check if the current node matches the Obj to remove
        if( pCurrNode->pObj == pObj )
        {
            if ( pPrevNode == NULL )
            {
                // Removing the head node
                common_aNodeHeads[ eObjType ] = pCurrNode->pNextNode;
            }
            else
            {
                // Bypass the current node
                pPrevNode->pNextNode = pCurrNode->pNextNode;
            }

            // Free the memory used by the current node
            free( pCurrNode );

            // Decrement the Obj count
            common_objCount[ eObjType ]--;

            return;
        }

        // Move to the next node in the list
        pPrevNode = pCurrNode;
        pCurrNode = pCurrNode->pNextNode;
    }
}



/**
 * @brief Iterate through the registry execute a function is the specified
 * obj type is found
 *
 * @param eObjType Type of object to look for
 * @param pObjFoundCb Function to execute if obj is found
 */
static void common_IterateRegistry( COMMON_eUsrObjType_t eObjType, COMMON_pfnObjFoundCb_t pObjFoundCb )
{
    // Start from the head of the list
    common_zObjNode *pCurrNode = common_aNodeHeads[ eObjType ];

    while( pCurrNode != NULL )
    {
        if( pCurrNode->eObjType == eObjType )
        {
            pObjFoundCb( pCurrNode );
        }

        pCurrNode = pCurrNode->pNextNode;
    }
}



/**
 * @brief Apply the Loading Screen Style based on the current theme
 *
 * @param pObj Pointer to the Loading Screen Obj
 */
static void common_ApplyStyleLoadingScr( lv_obj_t *pObj )
{
    switch( COMMON_eCurrTheme )
    {
        case COMMON_eThemeDark:
            lv_obj_set_style_bg_color( pObj, lv_color_make( 13, 17, 23 ), LV_PART_MAIN );
            break;

        case COMMON_eThemeLight:
            lv_obj_set_style_bg_color( pObj, lv_color_make( 255, 211, 165 ), LV_PART_MAIN );
            break;

        default:
            return;
    }
}



/**
 * @brief Apply the List Option Panel Style based on the current theme
 *
 * @param pObj Pointer to the List Option Panel Obj
 */
static void common_ApplyStyleLstOptPanel( lv_obj_t *pObj )
{
    switch( COMMON_eCurrTheme )
    {
        case COMMON_eThemeDark:
            lv_obj_set_style_border_color( pObj, lv_color_white(), LV_PART_MAIN );
            break;

        case COMMON_eThemeLight:
            lv_obj_set_style_border_color( pObj, lv_color_black(), LV_PART_MAIN );
            break;

        default:
            return;
    }
}



/**
 * @brief Apply the Label Style based on the current Theme
 *
 * @param pObj Pointer to the Label Obj
 */
static void common_ApplyStyleLabel( lv_obj_t *pObj )
{
    switch( COMMON_eCurrTheme )
    {
        case COMMON_eThemeDark:
            lv_obj_set_style_text_color( pObj, lv_color_white(), LV_PART_MAIN );
            break;

        case COMMON_eThemeLight:
            lv_obj_set_style_text_color( pObj, lv_color_black(), LV_PART_MAIN );
            break;

        default:
            return;
    }
}



/**
 * @brief Apply the Container Style based on the current theme
 *
 * @param pObj Pointer to the Container Obj
 */
static void common_ApplyStyleCont( lv_obj_t *pObj )
{
    lv_obj_set_style_bg_opa( pObj, LV_OPA_COVER, LV_PART_MAIN );

    switch( COMMON_eCurrTheme )
    {
        case COMMON_eThemeDark:
            lv_obj_set_style_bg_color( pObj, lv_color_make( 13, 17, 23 ), LV_PART_MAIN );
            lv_obj_set_style_bg_grad_color( pObj, lv_color_make( 40, 52, 71 ), LV_PART_MAIN );
            lv_obj_set_style_bg_grad_dir( pObj, LV_GRAD_DIR_VER, LV_PART_MAIN );
            break;

        case COMMON_eThemeLight:
            lv_obj_set_style_bg_color( pObj, lv_color_make( 255, 211, 165 ), LV_PART_MAIN );
            lv_obj_set_style_bg_grad_color( pObj, lv_color_make( 213, 145, 142 ), LV_PART_MAIN );
            lv_obj_set_style_bg_grad_dir( pObj, LV_GRAD_DIR_VER, LV_PART_MAIN );
            break;

        default:
            return;
    }
}



/**
 * @brief Apply the Switch Style based on the current theme
 *
 * @param pObj Pointer to the Switch Obj
 */
static void common_ApplyStyleSwitch( lv_obj_t *pObj )
{
    lv_obj_set_style_bg_opa( pObj, LV_OPA_100, LV_PART_MAIN);
    lv_obj_set_style_border_opa( pObj, LV_OPA_100, LV_PART_MAIN | LV_PART_INDICATOR);
    lv_obj_set_style_border_width( pObj, 2, LV_PART_MAIN | LV_PART_INDICATOR);
    lv_obj_set_style_outline_opa( pObj, LV_OPA_100, LV_PART_MAIN );
    lv_obj_set_style_bg_opa( pObj, LV_OPA_0, LV_PART_INDICATOR | LV_STATE_CHECKED );

    switch( COMMON_eCurrTheme )
    {
        case COMMON_eThemeDark:
            lv_obj_set_style_border_color( pObj, lv_color_white( ), LV_PART_MAIN | LV_PART_INDICATOR);
            lv_obj_set_style_bg_color( pObj, lv_color_white( ), LV_PART_KNOB );
            lv_obj_set_style_bg_color( pObj, lv_color_black( ), LV_PART_MAIN );
            break;

        case COMMON_eThemeLight:
            lv_obj_set_style_border_color( pObj, lv_color_black( ), LV_PART_MAIN | LV_PART_INDICATOR);
            lv_obj_set_style_bg_color( pObj, lv_color_black( ), LV_PART_KNOB );
            lv_obj_set_style_bg_color( pObj, lv_color_make( 255, 211, 165 ), LV_PART_MAIN );
            break;

        default:
            return;
    }
}



/**
 * @brief Apply the Button Style based on the current theme
 *
 * @param pObj Pointer to the Button Obj
 */
static void common_ApplyStyleBtn( lv_obj_t *pObj )
{
    lv_obj_set_style_bg_opa( pObj, LV_OPA_COVER, LV_PART_MAIN );
    lv_obj_set_style_border_width( pObj, 2, LV_PART_MAIN );

    switch( COMMON_eCurrTheme )
    {
        case COMMON_eThemeDark:
            lv_obj_set_style_bg_color( pObj, lv_color_make( 13, 17, 23 ), LV_PART_MAIN );
            lv_obj_set_style_border_color( pObj, lv_color_white( ), LV_PART_MAIN );
            break;

        case COMMON_eThemeLight:
            lv_obj_set_style_bg_color( pObj, lv_color_make( 255, 211, 165 ), LV_PART_MAIN );
            lv_obj_set_style_border_color( pObj, lv_color_black( ), LV_PART_MAIN );
            break;

        default:
            return;
    }
}



/**
 * @brief Apply the Slider style based on the current theme
 *
 * @param pObj Pointer to the Slider Obj
 */
static void common_ApplyStyleSlider( lv_obj_t *pObj )
{
    // Set border opacity and width for each part
    lv_obj_set_style_border_opa(pObj, LV_OPA_100, LV_PART_INDICATOR);
    lv_obj_set_style_border_opa(pObj, LV_OPA_100, LV_PART_KNOB);

    lv_obj_set_style_border_width(pObj, 2, LV_PART_INDICATOR);
    lv_obj_set_style_border_width(pObj, 2, LV_PART_KNOB);

    switch (COMMON_eCurrTheme)
    {
        case COMMON_eThemeDark:

            // Set background color for each part
            lv_obj_set_style_bg_color(pObj, lv_color_white( ), LV_PART_MAIN);
            lv_obj_set_style_bg_color(pObj, lv_color_white( ), LV_PART_INDICATOR);
            lv_obj_set_style_bg_color(pObj, lv_color_white( ), LV_PART_KNOB);

            // Set border color for each part
            lv_obj_set_style_border_color(pObj, lv_color_white(), LV_PART_INDICATOR);
            lv_obj_set_style_border_color(pObj, lv_color_black(), LV_PART_KNOB);
            break;

        case COMMON_eThemeLight:

            // Set background color for each part
            lv_obj_set_style_bg_color(pObj, lv_color_black( ), LV_PART_MAIN);
            lv_obj_set_style_bg_color(pObj, lv_color_black( ), LV_PART_INDICATOR);
            lv_obj_set_style_bg_color(pObj, lv_color_black( ), LV_PART_KNOB);

            // Set border color for each part
            lv_obj_set_style_border_color(pObj, lv_color_black(), LV_PART_INDICATOR);
            lv_obj_set_style_border_color(pObj, lv_color_black( ), LV_PART_KNOB);
            break;

        default:
            return;
    }
}
