/**
  ******************************************************************************
  * @file           : app_clock.h
  * @brief          : Header for APP_CLOCK Module
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
#ifndef __APP_CLOCK_H
#define __APP_CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include "esp_lvgl_port.h"
#include "app_common.h"

/* Exported types ------------------------------------------------------------*/

/* CLOCK enums used for tracking dates*/
typedef enum CLOCK_eMeridiem_t
{
    CLOCK_eMeridiemAM = 0,
    CLOCK_eMeridiemPM
} CLOCK_eMeridiem_t;

typedef enum CLOCK_eDays_t
{
    CLOCK_eDayMonday = 0,
    CLOCK_eDayTuesday,
    CLOCK_eDayWednesday,
    CLOCK_eDayThursday,
    CLOCK_eDayFriday,
    CLOCK_eDaySaturday,
    CLOCK_eDaySunday
} CLOCK_eDays_t;

typedef enum CLOCK_eMonths_t
{
    CLOCK_eMonthJan = 0,
    CLOCK_eMonthFeb,
    CLOCK_eMonthMar,
    CLOCK_eMonthApr,
    CLOCK_eMonthMay,
    CLOCK_eMonthJun,
    CLOCK_eMonthJul,
    CLOCK_eMonthAug,
    CLOCK_eMonthSep,
    CLOCK_eMonthOct,
    CLOCK_eMonthNov,
    CLOCK_eMonthDec
} CLOCK_eMonths_t;

typedef struct CLOCK_zClockTimeFields_t
{
    uint8_t                     seconds;
    uint8_t                     minutes;
    uint8_t                     hour;
    CLOCK_eDays_t               eDay;
    uint8_t                     date;
    CLOCK_eMonths_t             eMonth;
    uint16_t                    year;
    CLOCK_eMeridiem_t           eMeridiem;
} CLOCK_zClockTimeFields_t;

/**
 * @brief Clock Labels Enum
 * @note Used to index the array of ClockLabelObjs in CLOCK_zUserClockObj_t
 */
typedef enum CLOCK_eLabels_t
{
    CLOCK_eLabelTime,
    CLOCK_eLabelDate,
    CLOCK_eLabelDay,
    CLOCK_eLabelMonth,
    CLOCK_eLabelYear,
    CLOCK_eLabelCount
} CLOCK_eLabels_t;

/**
 * @brief Main User Clock Object Struct
 * @note Contains: Current/Unsaved clock settings, Clock Label Objects, Clock Container Object
 */
typedef struct CLOCK_zUserClockObj_t
{
    CLOCK_zClockTimeFields_t    zCurrentClockSettings;
    CLOCK_zClockTimeFields_t    zUnsavedClockSettings;
    lv_obj_t                    *aClockLabelObjs[ CLOCK_eLabelCount];
    lv_obj_t                    *pClockContainerObj;
} CLOCK_zUserClockObj_t;

/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void CLOCK_Init( CLOCK_zUserClockObj_t *pUserClockObj, lv_obj_t *pParentObj );

/* Exported defines ----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APP_CLOCK_H */
