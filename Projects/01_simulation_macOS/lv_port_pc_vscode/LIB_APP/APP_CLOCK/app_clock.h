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
#ifdef USE_SDL
    #include <lvgl/lvgl.h>
#else
    #include "esp_lvgl_port.h"
#endif
#include "app_common.h"

/* Exported types ------------------------------------------------------------*/

/* Clock enums used for tracking dates*/
typedef enum Clock_eMeridiem_t
{
    Clock_eMeridiemAM = 0,
    Clock_eMeridiemPM
} Clock_eMeridiem_t;

typedef enum Clock_eDays_t
{
    Clock_eDayMonday = 0,
    Clock_eDayTuesday,
    Clock_eDayWednesday,
    Clock_eDayThursday,
    Clock_eDayFriday,
    Clock_eDaySaturday,
    Clock_eDaySunday
} Clock_eDays_t;

typedef enum Clock_eMonths_t
{
    Clock_eMonthJan = 0,
    Clock_eMonthFeb,
    Clock_eMonthMar,
    Clock_eMonthApr,
    Clock_eMonthMay,
    Clock_eMonthJun,
    Clock_eMonthJul,
    Clock_eMonthAug,
    Clock_eMonthSep,
    Clock_eMonthOct,
    Clock_eMonthNov,
    Clock_eMonthDec
} Clock_eMonths_t;

typedef struct Clock_zClockTimeFields_t
{
    uint8_t                     seconds;
    uint8_t                     minutes;
    uint8_t                     hour;
    Clock_eDays_t               eDay;
    uint8_t                     date;
    Clock_eMonths_t             eMonth;
    uint16_t                    year;
    Clock_eMeridiem_t           eMeridiem;
} Clock_zClockTimeFields_t;

/**
 * @brief Clock Labels Enum
 * @note Used to index the array of ClockLabelObjs in Clock_zUsrClockObj_t
 */
typedef enum Clock_eLabels_t
{
    Clock_eLabelTime,
    Clock_eLabelDate,
    Clock_eLabelDay,
    Clock_eLabelMonth,
    Clock_eLabelYear,
    Clock_eLabelCount
} Clock_eLabels_t;

/**
 * @brief Main Usr Clock Object Struct
 * @note Contains: Current/Unsaved Clock settings, Clock Label Objects, Clock Cont Object
 */
typedef struct Clock_zUsrClockObj_t
{
    Clock_zClockTimeFields_t    zCurrentClockSettings;
    Clock_zClockTimeFields_t    zUnsavedClockSettings;
    lv_obj_t                    *aClockLabelObjs[ Clock_eLabelCount ];
    lv_obj_t                    *pClockContObj;
} Clock_zUsrClockObj_t;

/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void Clock_Init( Clock_zUsrClockObj_t *pUsrClockObj, lv_obj_t *pParentObj );

/* Exported defines ----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APP_CLOCK_H */
