/**
  ******************************************************************************
  * @file           : app_common.h
  * @brief          : Header for APP_COMMON module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_COMMON_H
#define __APP_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#ifdef USE_SDL
    #include <lvgl/lvgl.h>
#else
    #include "esp_lvgl_port.h"
#endif

/* Exported types ------------------------------------------------------------*/

/**
 * @brief Enum used to index array of lv_style_t
 *
 */
typedef enum COMMON_eTheme_t
{
    COMMON_eThemeDark       = 0,
    COMMON_eThemeLight,
    COMMON_eThemeCount
} COMMON_eTheme_t;

/**
 * @brief Types of Usr Objects Enum
 * @note Used in Registry
 */
typedef enum COMMON_eUsrObjType_t
{
    COMMON_eTypeDontTrack    = 0,
    COMMON_eTypeCont,
    COMMON_eTypeLabel,
    COMMON_eTypeCustomLst,
    COMMON_eTypeLstOptPanel,
    COMMON_eTypeLoadingScr,
    COMMON_eTypeBtn,
    COMMON_eTypeSlider,
    COMMON_eTypeSwitch,
    COMMON_eTypeCount
} COMMON_eUsrObjType_t;

/**
 * @brief Basic List Option Struct
 * @note Basic List Option consists of a Panel, Image, and Label
 */
typedef struct COMMON_zBasicListOpt_t
{
    lv_obj_t         *pOptPanel;
    lv_obj_t         *pOptImg;
    lv_obj_t         *pOptLabel;
} COMMON_zBasicListOpt_t;

/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/

/* Circular Scroll Flag */
extern bool COMMON_isCircularScroll;

/* Current Theme Flag */
extern COMMON_eTheme_t COMMON_eCurrTheme;

/* Images */
LV_IMG_DECLARE( img_app_info );
LV_IMG_DECLARE( img_brightness );
LV_IMG_DECLARE( img_circular_scroll );
LV_IMG_DECLARE( img_screen_timeout );
LV_IMG_DECLARE( img_settings );
LV_IMG_DECLARE( img_theme );


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void COMMON_InitStyles( void );
void COMMON_ApplyCurrThemeStyle( lv_obj_t *pObj, COMMON_eUsrObjType_t eObjType );
void COMMON_ChangeCurrThemeFlag( COMMON_eTheme_t eNewTheme );
void COMMON_SetAllObjsTheme( void );

void COMMON_SetupCustomListObj( lv_obj_t *pListObj );
void COMMON_AddBasicLstOpt( const char *pLabelText,
                            const lv_img_dsc_t *pImg,
                            uint32_t imgScale,
                            COMMON_zBasicListOpt_t *pListOption,
                            lv_obj_t *pParent );
void COMMON_AddBasicLstOptCb( COMMON_zBasicListOpt_t *pListOption,
                                    lv_event_cb_t pfnOptionClickedCb,
                                    void *pUsrData );
void COMMON_ListCircularScrollCb( lv_event_t *pEvent );
void COMMON_SetAllListScroll( bool isCircScroll );

void COMMON_RegisterUsrObj( lv_obj_t *pObj, COMMON_eUsrObjType_t eObjType );
void COMMON_UnRegisterUsrObj( lv_obj_t *pObj, COMMON_eUsrObjType_t eObjType );

/* Exported defines ----------------------------------------------------------*/

/* Macro for concatenating strings */
#define MALLOC_AND_CONCAT(dest_ptr, str1, str2)                    \
    do {                                                           \
        size_t len = strlen(str1) + strlen(str2) + 1;               \
        dest_ptr = (char *)malloc(len);                            \
        if (dest_ptr != NULL) {                                    \
            strcpy(dest_ptr, str1);                                \
            strcat(dest_ptr, str2);                                \
        }                                                          \
    } while(0)

/* Screen Resolutions */
#define APP_SCREEN_WIDTH  240
#define APP_SCREEN_HEIGHT 280


#ifdef __cplusplus
}
#endif

#endif /* __APP_COMMON_H */
