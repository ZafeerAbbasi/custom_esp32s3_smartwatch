/**
  ******************************************************************************
  * @file           : app_clk.c
  * @brief          : Contains Application Functions related to Clock feature
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

#include "app_clk.h"
#include <inttypes.h>

/* Typedef -------------------------------------------------------------------*/


/* Define --------------------------------------------------------------------*/

#define CLK_INITIAL_SECOND                ((uint8_t) 0)
#define CLK_INITIAL_MINUTE                ((uint8_t) 54)
#define CLK_INITIAL_HOUR                  ((uint8_t) 16)
#define CLK_INITIAL_DATE                  ((uint8_t) 24)
#define CLK_INITIAL_YEAR                  ((uint16_t) 2025)
#define CLK_INITIAL_MERIDIEM              CLK_eMeridiemPM
#define CLK_INITIAL_DAY                   CLK_eDayThursday
#define CLK_INITIAL_MONTH                 CLK_eMonthApr

/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/

bool clock_bIs24HTime = false;
const char *clock_aDaysOfTheWeek[ ] =
{
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};
const char *clock_aMonthsOfTheYear[ ] =
{
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec"
};

/* Function prototypes -------------------------------------------------------*/

static void clock_SetInitialClockSettings( CLK_zClkTimeFields_t *ClockSettings );
static void clock_ConvertMonthToString( char *buffer, CLK_eMonths_t eMonth );
static void clock_ConvertDayToString( char *buffer, CLK_eDays_t eDay );
static void clock_ConvertNumToString( char *buffer, uint32_t num );
static void clock_ConvertTimeToString( char *buffer, uint8_t minutes, uint8_t hours, CLK_eMeridiem_t eMeridiem );

/* User code -----------------------------------------------------------------*/

/**
 * @brief Initialize the Clock Screen
 *
 * @param pUsrClockObj Pointer to the Usr Clock Object from the Main Watch Object
 * @param pParentObj Pointer to the parent obj ( Main Watch Cont )
 */
void CLK_Init( CLK_zUsrClkObj_t *pUsrClockObj, lv_obj_t *pParentObj )
{
    lv_obj_t *pMainContObj                                  = pParentObj;
    lv_obj_t **ppClockContObj                               = &pUsrClockObj->pClockContObj;
    lv_obj_t **ppClockLabelsArray                           = pUsrClockObj->aClockLabelObjs;
    CLK_zClkTimeFields_t *pCurrentTimeSettings              = &pUsrClockObj->zCurrentClockSettings;
    char ClockTimeStr[ 25 ]                                 = { 0 };
    char ClockDayStr[ 15 ]                                  = { 0 };
    char ClockDateStr[ 15 ]                                 = { 0 };
    char ClockMonthStr[ 15 ]                                = { 0 };
    char ClockYearStr[ 15 ]                                 = { 0 };

    /* Set the Clock Settings to default values */
    clock_SetInitialClockSettings( &pUsrClockObj->zCurrentClockSettings );

    /* Create Clock Cont Obj on main Cont and remove default styling */
    *ppClockContObj = lv_obj_create( pMainContObj );
    lv_obj_remove_style_all( *ppClockContObj );
    lv_obj_set_size( *ppClockContObj, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT );

    /* Configure Clock Cont Background */
    lv_obj_set_style_bg_opa( *ppClockContObj, LV_OPA_TRANSP, LV_PART_MAIN );

    /* Initialize the label objs */
    for( int i = 0; i < CLK_eLabelCount; i++ )
    {
        ppClockLabelsArray[ i ] = lv_label_create( *ppClockContObj );

        /* Apply style according to current theme */
        COMMON_ApplyCurrThemeStyle( ppClockLabelsArray[ i ], COMMON_eTypeLabel );

        /* Register the Labels since we want track them if we ever want to change themes */
        COMMON_RegisterUsrObj( ppClockLabelsArray[ i ], COMMON_eTypeLabel );
    }

    /* Format the Clock data into a string format for use in label */
    clock_ConvertTimeToString( ClockTimeStr,
                                    pCurrentTimeSettings->minutes,
                                    pCurrentTimeSettings->hour,
                                    pCurrentTimeSettings->eMeridiem  );
    clock_ConvertDayToString( ClockDayStr, pCurrentTimeSettings->eDay );
    clock_ConvertMonthToString( ClockMonthStr, pCurrentTimeSettings->eMonth );
    clock_ConvertNumToString( ClockDateStr, ( uint32_t)pCurrentTimeSettings->date );
    clock_ConvertNumToString( ClockYearStr, pCurrentTimeSettings->year );

    /* Set labels with default values */
    lv_label_set_text( ppClockLabelsArray[ CLK_eLabelTime ], ClockTimeStr );
    lv_label_set_text( ppClockLabelsArray[ CLK_eLabelDate ], ClockDateStr );
    lv_label_set_text( ppClockLabelsArray[ CLK_eLabelDay ], ClockDayStr );
    lv_label_set_text( ppClockLabelsArray[ CLK_eLabelMonth ], ClockMonthStr );
    lv_label_set_text( ppClockLabelsArray[ CLK_eLabelYear ], ClockYearStr );

    /* Set the label fonts */
    lv_obj_set_style_text_font(ppClockLabelsArray[ CLK_eLabelDay ], &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_font(ppClockLabelsArray[ CLK_eLabelMonth ], &lv_font_montserrat_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(ppClockLabelsArray[ CLK_eLabelDate ], &lv_font_montserrat_40, LV_PART_MAIN);
    lv_obj_set_style_text_font(ppClockLabelsArray[ CLK_eLabelYear ], &lv_font_montserrat_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(ppClockLabelsArray[ CLK_eLabelTime ], &lv_font_montserrat_40, LV_PART_MAIN);

    /* Align the labels */
    lv_obj_align(ppClockLabelsArray[ CLK_eLabelTime ], LV_ALIGN_CENTER, LV_PCT( -3 ), LV_PCT( 12 ));
    lv_obj_align(ppClockLabelsArray[ CLK_eLabelDate ], LV_ALIGN_TOP_LEFT, LV_PCT(8), LV_PCT(20));
    lv_obj_align(ppClockLabelsArray[ CLK_eLabelDay ], LV_ALIGN_TOP_LEFT, LV_PCT(8), LV_PCT(10));
    lv_obj_align(ppClockLabelsArray[ CLK_eLabelMonth ], LV_ALIGN_TOP_LEFT, LV_PCT(8), LV_PCT(15));
    lv_obj_align(ppClockLabelsArray[ CLK_eLabelYear ], LV_ALIGN_TOP_LEFT, LV_PCT(8), LV_PCT(35));

    /* TODO: Create a timer for 1 second, to update the seconds value */


}



/**
 * @brief Set the Clock Time Fields to Inital Values
 *
 * @param pClockSettings Pointer to the Clock Time Fields struct from Usr Clock Object
 */
static void clock_SetInitialClockSettings( CLK_zClkTimeFields_t *pClockSettings )
{
    /* Set the fields to the default values */
    pClockSettings->seconds         = CLK_INITIAL_SECOND;
    pClockSettings->minutes         = CLK_INITIAL_MINUTE;
    pClockSettings->hour            = CLK_INITIAL_HOUR;
    pClockSettings->eDay            = CLK_INITIAL_DAY;
    pClockSettings->date            = CLK_INITIAL_DATE;
    pClockSettings->eMonth          = CLK_INITIAL_MONTH;
    pClockSettings->year            = CLK_INITIAL_YEAR;
    pClockSettings->eMeridiem       = CLK_INITIAL_MERIDIEM;
}



/**
 * @brief Convert a CLK_eMonths_t enum to string
 *
 * @param buffer String Buffer
 * @param eMonth Month Enum
 */
static void clock_ConvertMonthToString( char *buffer, CLK_eMonths_t eMonth )
{
    sprintf( buffer, "%s", clock_aMonthsOfTheYear[ eMonth ] );
}



/**
 * @brief Convert a CLK_eDays_t enum to string
 *
 * @param buffer String Buffer
 * @param eDay Day Enum
 */
static void clock_ConvertDayToString( char *buffer, CLK_eDays_t eDay )
{
    sprintf( buffer, "%s", clock_aDaysOfTheWeek[ eDay ] );
}



/**
 * @brief Convert a number to a string
 *
 * @param buffer String buffer
 * @param num Number to convert
 */
static void clock_ConvertNumToString( char *buffer, uint32_t num )
{
    sprintf(buffer, "%" PRIu32, num);
}



/**
 * @brief Convert Hour/Min/Merdiem numerical values into a string representation
 *
 * @param buffer String Buffer
 * @param minutes Numerical value of minutes
 * @param hours Numerical value of hours
 * @param eMeridiem Meridiem Enum
 */
static void clock_ConvertTimeToString( char *buffer, uint8_t minutes, uint8_t hours, CLK_eMeridiem_t eMeridiem )
{
    // Temporary buffer for formatted time
    char timeString[20];

    if( clock_bIs24HTime == true )
    {
        // 24-hour format (no AM/PM)
        snprintf(timeString, sizeof(timeString), "%02d:%02d", hours, minutes);
        snprintf(buffer, 20, "%s", timeString);
    }
    else
    {
        /* TODO: Add check if hours == 12, then use AM or PM*/

        /* Convert 24H into 12H format */
        if( hours > 12 )
        {
            hours = hours - 12;
        }

        // Format time as HH:MM AM/PM
        snprintf(timeString, sizeof(timeString), "%2d:%2d", hours, minutes);

        if (eMeridiem == CLK_eMeridiemAM) {
            snprintf(buffer, 24, "%s AM", timeString);
        } else {
            snprintf(buffer, 24, "%s PM", timeString);
        }
    }
}
