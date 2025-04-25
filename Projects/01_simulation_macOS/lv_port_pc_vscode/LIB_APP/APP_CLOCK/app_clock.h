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
#include <lvgl/lvgl.h>
#include "app_common.h"

/* Exported types ------------------------------------------------------------*/

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

typedef enum CLOCK_eLabelObjs
{
    CLOCK_eLabelTimeObj,
    CLOCK_eLabelDateObj,
    CLOCK_eLabelDayObj,
    CLOCK_eLabelMonthObj,
    CLOCK_eLabelYearObj,
    CLOCK_eLabelCount
} CLOCK_eLabelObj_t;

typedef struct CLOCK_zUserClockObj_t
{
    CLOCK_zClockTimeFields_t    zCurrentClockSettings;
    CLOCK_zClockTimeFields_t    zUnsavedClockSettings;
    COMMON_zUserWidgetObj_t     ClockLabelObjs[7];
    COMMON_zUserWidgetObj_t     zClockContainerObj;
} CLOCK_zUserClockObj_t;

/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void CLOCK_Init( COMMON_zUserWatchObj_t *pUserWatchObj );

/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APP_CLOCK_H */
