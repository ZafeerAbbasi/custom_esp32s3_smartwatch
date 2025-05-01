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
 * @brief Types of User Objects Enum
 * @note Used in Registry
 */
typedef enum COMMON_zUserObjType_t
{
    COMMON_eTypeDontTrack    = 0,
    COMMON_eTypeMainContainer,
    COMMON_eTypeLabel,
    COMMON_eTypeListOptionPanel,
    
    COMMON_eTypeCount
} COMMON_zUserObjType_t;

/**
 * @brief Custom List Option Struct
 * @note Each List Option consists of a Panel, Image, and Label
 */
typedef struct COMMON_zCustomListOption_t
{
    lv_obj_t         *pOptionPanel;
    lv_obj_t         *pOptionImg;
    lv_obj_t         *pOptionLabel;
} COMMON_zCustomListOption_t;

/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/

/* Images */
LV_IMG_DECLARE( img_app_info );
LV_IMG_DECLARE( img_brightness );
LV_IMG_DECLARE( img_circular_scroll );
LV_IMG_DECLARE( img_screen_timeout );
LV_IMG_DECLARE( img_settings );
LV_IMG_DECLARE( img_theme );


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void COMMON_SetupCustomListObj( lv_obj_t *pListObj );
void COMMON_AddCustomListOption( const char *pLabelText,
                            const lv_img_dsc_t *pImg,
                            uint32_t imgScale,
                            COMMON_zCustomListOption_t *pListOption,
                            lv_obj_t *pParent );
void COMMON_AddCustomListOptionCallback( COMMON_zCustomListOption_t *pListOption,
                                    lv_event_cb_t pfnOptionClickedCallback,
                                    void *pUserData );
void COMMON_ListCircularScrollCallback( lv_event_t *pEvent );

void COMMON_RegisterUserObj( lv_obj_t *pObj, COMMON_zUserObjType_t zObjType );
void COMMON_UnRegisterUserObj( lv_obj_t *pObj, COMMON_zUserObjType_t zObjType );

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
