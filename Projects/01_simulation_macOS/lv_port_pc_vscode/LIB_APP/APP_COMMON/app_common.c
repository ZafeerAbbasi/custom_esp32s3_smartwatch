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
 *
 */
typedef struct common_zObjNode
{
    lv_obj_t                    *pObj;
    COMMON_zUsrObjType_t       zObjType;
    struct common_zObjNode      *pNextNode;
} common_zObjNode;

/**
 * @brief Typedef for function pointer that is used
 * when an object is found while iterating through
 * the registry
 *
 */
typedef void ( *COMMON_pfnObjFoundCb_t )( common_zObjNode * );

/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/

/* Flag to use circular scroll or not, default is true */
bool COMMON_isCircularScroll                                                    = true;

/* Array of commonly used themes */
lv_style_t COMMON_aThemeStyles[ COMMON_eTypeCount ][ COMMON_eThemeCount ] = { 0 };

/* Flag used to track current theme */
COMMON_eTheme_t COMMON_eCurrTheme                                               = COMMON_eThemeDark;

static common_zObjNode *common_aNodeHeads[ COMMON_eTypeCount ]                  = { NULL };
static int common_ObjCount[ COMMON_eTypeCount ]                                 = { 0 };

/* Function prototypes -------------------------------------------------------*/

static void common_AddNode( lv_obj_t *pObj, COMMON_zUsrObjType_t zObjType );
static void common_RemoveNode( lv_obj_t *pObj, COMMON_zUsrObjType_t zObjType );
static void common_IterateRegistry( COMMON_zUsrObjType_t zObjType, COMMON_pfnObjFoundCb_t pObjFoundCb );


/* User code -----------------------------------------------------------------*/

/**
 * @brief Apply the current theme to an User - defined obj type
 *
 * @param pObj Pointer to the object to style
 * @param zObjType User - defined obj type
 */
void COMMON_ApplyCurrThemeStyle( lv_obj_t *pObj, COMMON_zUsrObjType_t zObjType )
{
    lv_obj_add_style( pObj, &COMMON_aThemeStyles[ zObjType ][ COMMON_eCurrTheme ], LV_PART_MAIN );
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

    if( isChanged )
    {
        COMMON_isCircularScroll = isCircScroll;

        /* Manually send event to all list objs to update the scroll change */

        // Start from the head of the list
        common_zObjNode *pCurrNode = common_aNodeHeads[ COMMON_eTypeCustomList ];

        while( pCurrNode != NULL )
        {
            if( pCurrNode->zObjType == COMMON_eTypeCustomList )
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
 * @brief Initialize commonly-used styles
 *
 */
void COMMON_InitStyles( void )
{
    /* Container Dark/Light Theme */
    lv_style_t *zDarkTheme = &COMMON_aThemeStyles[ COMMON_eTypeCont ][ COMMON_eThemeDark ];
    lv_style_set_bg_opa( zDarkTheme, LV_OPA_COVER );
    lv_style_set_bg_color( zDarkTheme, lv_color_make( 13, 17, 23 ) );
    lv_style_set_bg_grad_color( zDarkTheme, lv_color_make( 40, 52, 71 ) );
    lv_style_set_bg_grad_dir( zDarkTheme, LV_GRAD_DIR_VER );
    lv_style_t *zLightTheme = &COMMON_aThemeStyles[ COMMON_eTypeCont ][ COMMON_eThemeLight ];
    lv_style_set_bg_opa( zLightTheme, LV_OPA_COVER );
    lv_style_set_bg_color( zLightTheme, lv_color_make(255, 211, 165) );
    lv_style_set_bg_grad_color( zLightTheme, lv_color_make(213, 145, 142) );
    lv_style_set_bg_grad_dir( zLightTheme, LV_GRAD_DIR_VER );

    /* Label Dark/Light Theme */
    zDarkTheme = &COMMON_aThemeStyles[ COMMON_eTypeLabel ][ COMMON_eThemeDark ];
    lv_style_set_text_color( zDarkTheme, lv_color_white( ) );
    zLightTheme = &COMMON_aThemeStyles[ COMMON_eTypeLabel ][ COMMON_eThemeLight ];
    lv_style_set_text_color( zLightTheme, lv_color_black( ) );

    /* List Option Panel Dark/Light Theme */
    zDarkTheme = &COMMON_aThemeStyles[ COMMON_eTypeListOptionPanel ][ COMMON_eThemeDark ];
    lv_style_set_border_color( zDarkTheme, lv_color_white( ) );
    zLightTheme = &COMMON_aThemeStyles[ COMMON_eTypeListOptionPanel ][ COMMON_eThemeLight ];
    lv_style_set_border_color( zLightTheme, lv_color_black( ) );

    /* Loading screen Dark/Light Theme */
    zDarkTheme = &COMMON_aThemeStyles[ COMMON_eTypeLoadingScreen ][ COMMON_eThemeDark ];
    lv_style_set_bg_color( zDarkTheme, lv_color_black( ) );
    zLightTheme = &COMMON_aThemeStyles[ COMMON_eTypeLoadingScreen ][ COMMON_eThemeLight ];
    lv_style_set_bg_color( zLightTheme, lv_color_white( ) );
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
void COMMON_AddCustomListOption( const char *pLabelText,
                            const lv_img_dsc_t *pImg,
                            uint32_t imgScale,
                            COMMON_zBasicListOpt_t *pListOption,
                            lv_obj_t *pParent )
{
    /* Create Option Panel on the List Obj and register it */
    pListOption->pOptPanel = lv_obj_create( pParent );
    COMMON_RegisterUsrObj( pListOption->pOptPanel, COMMON_eTypeListOptionPanel );

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
    COMMON_ApplyCurrThemeStyle( pListOption->pOptPanel, COMMON_eTypeListOptionPanel );

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
void COMMON_AddCustomListOptionCb( COMMON_zBasicListOpt_t *pListOption,
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

    /* Register the list */
    COMMON_RegisterUsrObj( pListObj, COMMON_eTypeCustomList );

    /* Add circular scroll to the list if enabled */
    lv_obj_add_event_cb( pListObj, COMMON_ListCircularScrollCb, LV_EVENT_SCROLL, ( void * )&COMMON_isCircularScroll );
}



/**
 * @brief Register a Usr Obj to the Obj Registry
 *
 * @param pObj Pointer to the Obj Object
 * @param zObjType Type of object being registered, can be 0 or COMMON_eTypeDontTrack if
 * in case of not tracking this type of object
 *
 * @note WARNING: This should ONLY be used for objs that will NEVER BE DELETED
 */
void COMMON_RegisterUsrObj( lv_obj_t *pObj, COMMON_zUsrObjType_t zObjType )
{
    /* Register Obj to the Registry */
    common_AddNode( pObj, zObjType );
}



/**
 * @brief Un-Register a Usr Obj from the Obj Registry
 *
 *
 * @param pObj Pointer to the Obj
 * @param zObjType Type of object being registered, can be 0 or COMMON_eTypeDontTrack if
 * in case of not tracking this type of object
 */
void COMMON_UnRegisterUsrObj( lv_obj_t *pObj, COMMON_zUsrObjType_t zObjType )
{
    /* Remove Obj from Registry */
    common_RemoveNode( pObj, zObjType );
}



/**
 * @brief Add a Usr Object to the Obj Registry
 *
 * @param pObj Pointer to the Obj to Register
 * @param zObjType Type of object being registered, will be 0 if not tracking
 */
static void common_AddNode( lv_obj_t *pObj, COMMON_zUsrObjType_t zObjType )
{
    // Allocate memory for a new node
    common_zObjNode *pNewNode = ( common_zObjNode * )malloc( sizeof( common_zObjNode ) );

    if( pNewNode == NULL )
    {
        // If malloc fails, exit the function
        return;
    }

    if( zObjType == COMMON_eTypeDontTrack )
    {
        return; // Usr does not want to track this obj
    }

    // Assign the Usr Obj object and type to the new node
    pNewNode->pObj      = pObj;
    pNewNode->zObjType  = zObjType;


    // Insert the new node at the beginning of the list
    pNewNode->pNextNode = common_aNodeHeads[ zObjType ];
    common_aNodeHeads[ zObjType ] = pNewNode;

    // Increment the Obj count
    common_ObjCount[ zObjType ]++;
}



/**
 * @brief Remove a Usr Object from the Obj Registry
 *
 * @param pObj Pointer to the Obj Object to Un-Register
 * @param zObjType Type of object being registered, will be 0 if not tracking
 */
static void common_RemoveNode( lv_obj_t *pObj, COMMON_zUsrObjType_t zObjType )
{
    // Start from the head of the list
    common_zObjNode *pCurrNode = common_aNodeHeads[ zObjType ];
    common_zObjNode *pPrevNode = NULL;

    while( pCurrNode != NULL )
    {
        // Check if the current node matches the Obj to remove
        if( pCurrNode->pObj == pObj )
        {
            if ( pPrevNode == NULL )
            {
                // Removing the head node
                common_aNodeHeads[ zObjType ] = pCurrNode->pNextNode;
            }
            else
            {
                // Bypass the current node
                pPrevNode->pNextNode = pCurrNode->pNextNode;
            }

            // Free the memory used by the current node
            free( pCurrNode );

            // Decrement the Obj count
            common_ObjCount[ zObjType ]--;

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
 * @param zObjType Type of object to look for
 * @param pObjFoundCb Function to execute if obj is found
 */
static void common_IterateRegistry( COMMON_zUsrObjType_t zObjType, COMMON_pfnObjFoundCb_t pObjFoundCb )
{
    // Start from the head of the list
    common_zObjNode *pCurrNode = common_aNodeHeads[ zObjType ];

    while( pCurrNode != NULL )
    {
        if( pCurrNode->zObjType == zObjType )
        {
            pObjFoundCb( pCurrNode );
        }

        pCurrNode = pCurrNode->pNextNode;
    }
}
