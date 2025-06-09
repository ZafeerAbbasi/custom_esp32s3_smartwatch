/**
  ******************************************************************************
  * @file           : lvgl_app.c
  * @brief          : Contains application lvgl functions.
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

#include "lvgl_app.h"

/* Typedef -------------------------------------------------------------------*/


/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/

/* LVGL Display/Touch Input handle */
static lv_display_t *pLvglDisplayAndTouchHdl;

/* Input Device Driver needs to be static because it is referenced via pointer by LVGL */
static lv_indev_drv_t zLvglInputDeviceDriver;

/* Function prototypes -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/

void LVGL_fnTask( void *pvArg )
{
    COMMON_teWIFI_NOTIF teWifiNotif = COMMON_eWIFI_NOTIF_IGNORE;
    
    // Init
    LVGL_Init( );

    // Wait for Wifi task to notify us that
    // we have finished scanning all APs
    if( xTaskNotifyWait( 0x00,
                         0xFFFFFFFF,
                         ( uint32_t * )&teWifiNotif,
                         portMAX_DELAY ) == pdPASS )
    {
        if( teWifiNotif == COMMON_eWIFI_NOTIF_AP_SCAN_CMPLT )
        {
            // Get the list of AP
            taskENTER_CRITICAL( &COMMON_tzLockWifiLvgl );
            /* Get AP */
            taskEXIT_CRITICAL( &COMMON_tzLockWifiLvgl );

            lvgl_port_lock( 0 );
            // WIFI_fnCreateWifiSelectionScr( )
            lvgl_port_unlock( );
        }
    }


}

/***************************************************************************//**
    @brief Initialize LVGL Engine, Display and Touch Driver
    
    @returns esp_err_t esp_err_t ESP_OK on success, error code on failure
    
 ******************************************************************************/
esp_err_t LVGL_Init( void )
{
    esp_err_t ret = ESP_OK;

    /* Configure and create the LVGL FreeRTOS task */
    const lvgl_port_cfg_t zLvglPortCfg = ESP_LVGL_PORT_INIT_CONFIG( );
    ESP_ERROR_CHECK( lvgl_port_init( &zLvglPortCfg ) );

    /* Add LCD Screen by creating a LVGL Display */
    const lvgl_port_display_cfg_t zLvglPortDispCfg = 
    {
        .io_handle          = LCD_zLcdIoHdl,
        .panel_handle       = LCD_zLcdPanelHdl,
        .buffer_size        = LCD_MAX_TRANSFER_SZ,
        .double_buffer      = LCD_DRAW_BUFF_DOUBLE,
        .hres               = LCD_H_RES,
        .vres               = LCD_V_RES,
        .monochrome         = false,

        /* Rotation values need to be the same as used in esp_lcd for the 
        screen settings init. */
        .rotation = 
        {
            .swap_xy        = false,
            .mirror_x       = false,
            .mirror_y       = false
        },
        .flags = 
        {
            .buff_dma       = true
        }
    };
    pLvglDisplayAndTouchHdl = lvgl_port_add_disp( &zLvglPortDispCfg );

    /* Add the Input Device Driver ( Touch ) */
    lv_indev_drv_init( &zLvglInputDeviceDriver );           // Init with default values

    zLvglInputDeviceDriver.type         = LV_INDEV_TYPE_POINTER;
    zLvglInputDeviceDriver.disp         = pLvglDisplayAndTouchHdl;
    zLvglInputDeviceDriver.read_cb      = LVGL_TouchDriverCallback;
    zLvglInputDeviceDriver.user_data    = TOUCH_zTouchPanelHdl;

    lv_indev_drv_register( &zLvglInputDeviceDriver );       // Register Input Device with cb and config

    return ret;
}

/***************************************************************************//**
    @brief LVGL Touch Callback, called every 4ms
    
    @param pInputDeviceDriver   Pointer LVGL Input Device Driver
    @param[out] pUserData       Pointer to User Data which will be registered
                                with the X and Y co-ordinates of the touch
    
 ******************************************************************************/
void LVGL_TouchDriverCallback( lv_indev_drv_t *pInputDeviceDriver, lv_indev_data_t *pUserData )
{
    esp_lcd_touch_handle_t zTouchPanel = ( esp_lcd_touch_handle_t )pInputDeviceDriver->user_data;
    uint16_t touchPanelX = 0;
    uint16_t touchPanelY = 0;
    uint8_t touchPanelNumOfPointsTouched = 0;

    /* Read data from touch controller*/
    esp_lcd_touch_read_data( zTouchPanel );

    /* Get the Co-ordinates */
    bool isTouchPanelPressed = esp_lcd_touch_get_coordinates( zTouchPanel,
                                                            &touchPanelX,
                                                            &touchPanelY,
                                                            NULL,
                                                            &touchPanelNumOfPointsTouched,
                                                            1 );
    
    /* Process the data */
    if( isTouchPanelPressed == true && touchPanelNumOfPointsTouched > 0 )
    {
        /* User touched the screen, register the x and y co-ordinates */
        pUserData->point.x      = touchPanelX;
        pUserData->point.y      = touchPanelY;
        pUserData->state        = LV_INDEV_STATE_PRESSED;
    }
    else
    {
        /* No user touch */
        pUserData->state        = LV_INDEV_STATE_RELEASED;
    }
}
