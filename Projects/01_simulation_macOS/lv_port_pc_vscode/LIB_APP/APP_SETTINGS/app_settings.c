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


/* Function prototypes -------------------------------------------------------*/


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
    

}
