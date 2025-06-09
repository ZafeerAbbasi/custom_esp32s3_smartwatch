/******************************************************************************
 
******************************************************************************
  @file         : 
  @brief        : 
******************************************************************************

  @attention

  Copyright (c) 2025 Zafeer Abbasi.
  All rights reserved.

  This software is licensed under terms that can be found in the LICENSE file
  in the root directory of this software component.
  If no LICENSE file comes with the software, it is provided AS-IS.
 
******************************************************************************/
 
#ifndef TEMPLATE_H
#define TEMPLATE_H
 
/*==============================================================================
                              Includes
==============================================================================*/
 
#include <stdlib.h>
#include <stdbool.h>
#include "esp_lvgl_port.h"
#include "esp_event.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
 
/*==============================================================================
                          Public Defines
==============================================================================*/
 
 
/*=============================================================================
                          Public Data Types
=============================================================================*/

// Wifi notifications that are sent from Wi-fi task
// Some are processed by the LVGL Task, hence why its in common module
typedef enum COMMON_eWIFI_NOTIF
{
    COMMON_eWIFI_NOTIF_IGNORE           = 0,
    COMMON_eWIFI_NOTIF_AP_SCAN_CMPLT,
    COMMON_eWIFI_NOTIF_CONN_CMPLT
}COMMON_teWIFI_NOTIF;

/*==============================================================================
                          Public Constants
==============================================================================*/
 
 
/*==============================================================================
                          Public Variables
==============================================================================*/
 
extern portMUX_TYPE COMMON_tzLockWifiLvgl;      // Used by Wifi & LVGL task when
                                                // accessing shared data

/*==============================================================================
                      Public Function Prototypes
==============================================================================*/
 
 
#endif  // TEMPLATE_H
 
//*****************************************************************************
// End of file.
//! @}
//*****************************************************************************
