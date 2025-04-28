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
    const lv_obj_t                  *pObj;
    struct common_zObjNode       *pNextNode;
} common_zObjNode;

/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/

static common_zObjNode *pNodeHead    = NULL;
static int common_ObjCount           = 0;

/* Function prototypes -------------------------------------------------------*/

static void common_AddNode( const lv_obj_t *pObj );
static void common_RemoveNode( const lv_obj_t *pObj );


/* User code -----------------------------------------------------------------*/

/**
 * @brief Custom List Circular Scroll Callback
 *
 * @param pEvent Pointer to
 */
void COMMON_ListCircularScrollCallback( lv_event_t *pEvent )
{
    lv_obj_t *list = lv_event_get_target(pEvent);
    bool isCircularScroll = *( bool *)lv_event_get_user_data( pEvent );

    lv_area_t list_a;
    lv_obj_get_coords(list, &list_a);
    lv_coord_t list_y_center = list_a.y1 + lv_area_get_height(&list_a) / 2;

    lv_coord_t r = lv_obj_get_height(list) * 7 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_count(list);
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

        /*Use some opacity with larger translations*/
        // lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        // lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
    }
}



/**
 * @brief Add a Option on a List
 *
 * @param pLabelText Label for the Option
 * @param pImg Image for the Option
 * @param pListOption Pointer to the List Option Obj
 * @param pfnOptionClickedCallback Callback if the user clicks on the option, can be NULL
 * @param pList Pointer to the List which the option is placed on
 */
void COMMON_AddListOption( const char *pLabelText,
                            const lv_image_dsc_t *pImg,
                            COMMON_zCustomListOption_t *pListOption,
                            lv_event_cb_t pfnOptionClickedCallback,
                            lv_obj_t *pList )
{
    /* Create Option Panel on the List Obj and register it */
    pListOption->pOptionPanel = lv_obj_create( pList );
    COMMON_RegisterUserObj( pListOption->pOptionPanel );

    /* Configure Option Panel */
    lv_obj_set_width(pListOption->pOptionPanel, 200);
    lv_obj_set_height(pListOption->pOptionPanel, 64);
    lv_obj_set_align(pListOption->pOptionPanel, LV_ALIGN_CENTER);
    lv_obj_remove_flag(pListOption->pOptionPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(pListOption->pOptionPanel, 0, LV_PART_MAIN );
    lv_obj_set_style_bg_opa(pListOption->pOptionPanel, LV_OPA_TRANSP, LV_PART_MAIN );
    lv_obj_set_style_border_color(pListOption->pOptionPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN );
    lv_obj_set_style_border_opa(pListOption->pOptionPanel, 255, LV_PART_MAIN );
    lv_obj_set_style_border_width(pListOption->pOptionPanel, 1, LV_PART_MAIN );
    lv_obj_set_style_border_side(pListOption->pOptionPanel, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN );
    lv_obj_set_style_pad_left(pListOption->pOptionPanel, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_right(pListOption->pOptionPanel, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_top(pListOption->pOptionPanel, 0, LV_PART_MAIN );
    lv_obj_set_style_pad_bottom(pListOption->pOptionPanel, 5, LV_PART_MAIN );

    /* Create Option Img on the Option Panel and register it */
    pListOption->pOptionImg = lv_image_create( pListOption->pOptionPanel );
    COMMON_RegisterUserObj( pListOption->pOptionImg );

    /* Configure Option Img */
    lv_image_set_src(pListOption->pOptionImg, ( const void * )pImg );
    lv_obj_set_width(pListOption->pOptionImg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(pListOption->pOptionImg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(pListOption->pOptionImg, -74);
    lv_obj_set_y(pListOption->pOptionImg, 2);
    lv_obj_set_align(pListOption->pOptionImg, LV_ALIGN_CENTER);
    lv_obj_add_flag(pListOption->pOptionImg, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
    lv_obj_remove_flag(pListOption->pOptionImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_image_set_scale(pListOption->pOptionImg, 60);

    /* Create Option Label on the Option Panel and register it*/
    pListOption->pOptionLabel = lv_label_create( pListOption->pOptionPanel );
    COMMON_RegisterUserObj( pListOption->pOptionLabel );

    /* Configure Option Label */
    lv_obj_set_width(pListOption->pOptionLabel, 160);
    lv_obj_set_height(pListOption->pOptionLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(pListOption->pOptionLabel, 54);
    lv_obj_set_y(pListOption->pOptionLabel, 3);
    lv_obj_set_align(pListOption->pOptionLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(pListOption->pOptionLabel, pLabelText);
    lv_obj_set_style_text_color( pListOption->pOptionLabel, lv_color_white( ), LV_PART_MAIN );
    lv_label_set_long_mode(pListOption->pOptionLabel, LV_LABEL_LONG_CLIP);
    lv_obj_set_style_text_font(pListOption->pOptionLabel, &lv_font_montserrat_20, LV_PART_MAIN );

    /* Add Option Clicked Callback on the Option panel, if available */
    if( pfnOptionClickedCallback != NULL )
    {
        lv_obj_add_event_cb( pListOption->pOptionPanel, pfnOptionClickedCallback, LV_EVENT_CLICKED, NULL );
    }

}


/**
 * @brief Register a User Obj to the Obj Registry
 *
 * @note This function MUST be called after creating ANY lv object
 * @param pName Name for the Obj
 * @param pObj Pointer to the Obj Object
 */
void COMMON_RegisterUserObj( lv_obj_t *pObj )
{
    /* Register Obj to the Registry */
    common_AddNode( pObj );
}



/**
 * @brief Un-Register a User Obj from the Obj Registry
 *
 *
 * @param pObj Pointer to the Obj
 */
void COMMON_UnRegisterUserObj( lv_obj_t *pObj )
{
    /* Remove Obj from Registry */
    common_RemoveNode( pObj );
}



/**
 * @brief Add a User Object to the Obj Registry
 *
 * @param pObj Pointer to the Obj to Register
 */
static void common_AddNode( const lv_obj_t *pObj )
{
    // Allocate memory for a new node
    common_zObjNode *pNewNode = ( common_zObjNode * )malloc( sizeof( common_zObjNode ) );

    if( pNewNode == NULL )
    {
        // If malloc fails, exit the function
        return;
    }

    // Assign the user Obj object to the new node
    pNewNode->pObj = pObj;

    // Insert the new node at the beginning of the list
    pNewNode->pNextNode = pNodeHead;
    pNodeHead = pNewNode;

    // Increment the Obj count
    common_ObjCount++;
}



/**
 * @brief Remove a User Object from the Obj Registry
 *
 * @param pObj Pointer to the Obj Object to Un-Register
 */
static void common_RemoveNode( const lv_obj_t *pObj )
{
    // Start from the head of the list
    common_zObjNode *pCurrNode = pNodeHead;
    common_zObjNode *pPrevNode = NULL;

    while( pCurrNode != NULL )
    {
        // Check if the current node matches the Obj to remove
        if( pCurrNode->pObj == pObj )
        {
            if ( pPrevNode == NULL )
            {
                // Removing the head node
                pNodeHead = pCurrNode->pNextNode;
            }
            else
            {
                // Bypass the current node
                pPrevNode->pNextNode = pCurrNode->pNextNode;
            }

            // Free the memory used by the current node
            free( pCurrNode );

            // Decrement the Obj count
            common_ObjCount--;

            return;
        }

        // Move to the next node in the list
        pPrevNode = pCurrNode;
        pCurrNode = pCurrNode->pNextNode;
    }
}
