/**
  ******************************************************************************
  * @file           : app_clk.h
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
#ifndef __APP_CLK_H
#define __APP_CLK_H

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
typedef enum CLK_eMeridiem_t
{
    CLK_eMeridiemAM = 0,
    CLK_eMeridiemPM
} CLK_eMeridiem_t;

typedef enum CLK_eDays_t
{
    CLK_eDayMonday = 0,
    CLK_eDayTuesday,
    CLK_eDayWednesday,
    CLK_eDayThursday,
    CLK_eDayFriday,
    CLK_eDaySaturday,
    CLK_eDaySunday
} CLK_eDays_t;

typedef enum CLK_eMonths_t
{
    CLK_eMonthJan = 0,
    CLK_eMonthFeb,
    CLK_eMonthMar,
    CLK_eMonthApr,
    CLK_eMonthMay,
    CLK_eMonthJun,
    CLK_eMonthJul,
    CLK_eMonthAug,
    CLK_eMonthSep,
    CLK_eMonthOct,
    CLK_eMonthNov,
    CLK_eMonthDec
} CLK_eMonths_t;

typedef struct CLK_zClkTimeFields_t
{
    uint8_t                     seconds;
    uint8_t                     minutes;
    uint8_t                     hour;
    CLK_eDays_t               eDay;
    uint8_t                     date;
    CLK_eMonths_t             eMonth;
    uint16_t                    year;
    CLK_eMeridiem_t           eMeridiem;
} CLK_zClkTimeFields_t;

/**
 * @brief Clock Labels Enum
 * @note Used to index the array of ClockLabelObjs in CLK_zUsrClkObj_t
 */
typedef enum CLK_eLabels_t
{
    CLK_eLabelTime,
    CLK_eLabelDate,
    CLK_eLabelDay,
    CLK_eLabelMonth,
    CLK_eLabelYear,
    CLK_eLabelCount
} CLK_eLabels_t;

/**
 * @brief Main Usr Clock Object Struct
 * @note Contains: Current/Unsaved Clock settings, Clock Label Objects, Clock Cont Object
 */
typedef struct CLK_zUsrClkObj_t
{
    CLK_zClkTimeFields_t    zCurrentClockSettings;
    CLK_zClkTimeFields_t    zUnsavedClockSettings;
    lv_obj_t                    *aClockLabelObjs[ CLK_eLabelCount ];
    lv_obj_t                    *pClockContObj;
} CLK_zUsrClkObj_t;

/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void CLK_Init( CLK_zUsrClkObj_t *pUsrClockObj, lv_obj_t *pParentObj );

/* Exported defines ----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APP_CLK_H */
