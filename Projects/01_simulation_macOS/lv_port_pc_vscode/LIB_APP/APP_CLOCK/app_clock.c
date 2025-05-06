/**
  ******************************************************************************
  * @file           : app_clock.c
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

#include "app_clock.h"

/* Typedef -------------------------------------------------------------------*/


/* Define --------------------------------------------------------------------*/

#define Clock_INITIAL_SECOND                ((uint8_t) 0)
#define Clock_INITIAL_MINUTE                ((uint8_t) 54)
#define Clock_INITIAL_HOUR                  ((uint8_t) 16)
#define Clock_INITIAL_DATE                  ((uint8_t) 24)
#define Clock_INITIAL_YEAR                  ((uint16_t) 2025)
#define Clock_INITIAL_MERIDIEM              Clock_eMeridiemPM
#define Clock_INITIAL_DAY                   Clock_eDayThursday
#define Clock_INITIAL_MONTH                 Clock_eMonthApr

/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/

bool Clock_bIs24Htime = false;
const char *Clock_aDaysOfTheWeek[ ] =
{
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};
const char *Clock_aMonthsOfTheYear[ ] =
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

static void Clock_SetInitialClockSettings( Clock_zClockTimeFields_t *ClockSettings );
static void Clock_ConvertMonthToString( char *buffer, Clock_eMonths_t eMonth );
static void Clock_ConvertDayToString( char *buffer, Clock_eDays_t eDay );
static void Clock_ConvertNumToString( char *buffer, uint32_t num );
static void Clock_ConvertTimeToString( char *buffer, uint8_t minutes, uint8_t hours, Clock_eMeridiem_t eMeridiem );

/* User code -----------------------------------------------------------------*/

/**
 * @brief Initialize the Clock Screen
 *
 * @param pUsrClockObj Pointer to the Usr Clock Object from the Main Watch Object
 * @param pParentObj Pointer to the parent obj ( Main Watch Cont )
 */
void Clock_Init( Clock_zUsrClockObj_t *pUsrClockObj, lv_obj_t *pParentObj )
{
    lv_obj_t *pMainContObj                                  = pParentObj;
    lv_obj_t **ppClockContObj                               = &pUsrClockObj->pClockContObj;
    lv_obj_t **ppClockLabelsArray                           = pUsrClockObj->aClockLabelObjs;
    Clock_zClockTimeFields_t *pCurrentTimeSettings          = &pUsrClockObj->zCurrentClockSettings;
    char ClockTimeStr[ 25 ]                                 = { 0 };
    char ClockDayStr[ 15 ]                                  = { 0 };
    char ClockDateStr[ 15 ]                                 = { 0 };
    char ClockMonthStr[ 15 ]                                = { 0 };
    char ClockYearStr[ 15 ]                                 = { 0 };

    /* Set the Clock Settings to default values */
    Clock_SetInitialClockSettings( &pUsrClockObj->zCurrentClockSettings );

    /* Create Clock Cont Obj on main Cont and remove default styling */
    *ppClockContObj = lv_obj_create( pMainContObj );
    lv_obj_remove_style_all( *ppClockContObj );
    lv_obj_set_size( *ppClockContObj, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT );

    /* Configure Clock Cont Background */
    lv_obj_set_style_bg_opa( *ppClockContObj, LV_OPA_TRANSP, LV_PART_MAIN );

    /* Initialize the label objs */
    for( int i = 0; i < Clock_eLabelCount; i++ )
    {
        ppClockLabelsArray[ i ] = lv_label_create( *ppClockContObj );

        /* TODO: ADD IF STATEMENT BASED ON THEME SELECT TEXT COLOR */
        lv_obj_set_style_text_color( ppClockLabelsArray[ i ], lv_color_white( ), LV_PART_MAIN );
    }

    /* Format the Clock data into a string format for use in label */
    Clock_ConvertTimeToString( ClockTimeStr,
                                    pCurrentTimeSettings->minutes,
                                    pCurrentTimeSettings->hour,
                                    pCurrentTimeSettings->eMeridiem  );
    Clock_ConvertDayToString( ClockDayStr, pCurrentTimeSettings->eDay );
    Clock_ConvertMonthToString( ClockMonthStr, pCurrentTimeSettings->eMonth );
    Clock_ConvertNumToString( ClockDateStr, ( uint32_t)pCurrentTimeSettings->date );
    Clock_ConvertNumToString( ClockYearStr, pCurrentTimeSettings->year );

    /* Set labels with default values */
    lv_label_set_text( ppClockLabelsArray[ Clock_eLabelTime ], ClockTimeStr );
    lv_label_set_text( ppClockLabelsArray[ Clock_eLabelDate ], ClockDateStr );
    lv_label_set_text( ppClockLabelsArray[ Clock_eLabelDay ], ClockDayStr );
    lv_label_set_text( ppClockLabelsArray[ Clock_eLabelMonth ], ClockMonthStr );
    lv_label_set_text( ppClockLabelsArray[ Clock_eLabelYear ], ClockYearStr );

    /* Set the label fonts */
    lv_obj_set_style_text_font(ppClockLabelsArray[ Clock_eLabelDay ], &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_font(ppClockLabelsArray[ Clock_eLabelMonth ], &lv_font_montserrat_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(ppClockLabelsArray[ Clock_eLabelDate ], &lv_font_montserrat_40, LV_PART_MAIN);
    lv_obj_set_style_text_font(ppClockLabelsArray[ Clock_eLabelYear ], &lv_font_montserrat_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(ppClockLabelsArray[ Clock_eLabelTime ], &lv_font_montserrat_40, LV_PART_MAIN);

    /* Align the labels */
    lv_obj_align(ppClockLabelsArray[ Clock_eLabelTime ], LV_ALIGN_CENTER, LV_PCT( -3 ), LV_PCT( 12 ));
    lv_obj_align(ppClockLabelsArray[ Clock_eLabelDate ], LV_ALIGN_TOP_LEFT, LV_PCT(8), LV_PCT(20));
    lv_obj_align(ppClockLabelsArray[ Clock_eLabelDay ], LV_ALIGN_TOP_LEFT, LV_PCT(8), LV_PCT(10));
    lv_obj_align(ppClockLabelsArray[ Clock_eLabelMonth ], LV_ALIGN_TOP_LEFT, LV_PCT(8), LV_PCT(15));
    lv_obj_align(ppClockLabelsArray[ Clock_eLabelYear ], LV_ALIGN_TOP_LEFT, LV_PCT(8), LV_PCT(35));

    /* TODO: Create a timer for 1 second, to update the seconds value */


}



/**
 * @brief Set the Clock Time Fields to Inital Values
 *
 * @param pClockSettings Pointer to the Clock Time Fields struct from Usr Clock Object
 */
static void Clock_SetInitialClockSettings( Clock_zClockTimeFields_t *pClockSettings )
{
    /* Set the fields to the default values */
    pClockSettings->seconds         = Clock_INITIAL_SECOND;
    pClockSettings->minutes         = Clock_INITIAL_MINUTE;
    pClockSettings->hour            = Clock_INITIAL_HOUR;
    pClockSettings->eDay            = Clock_INITIAL_DAY;
    pClockSettings->date            = Clock_INITIAL_DATE;
    pClockSettings->eMonth          = Clock_INITIAL_MONTH;
    pClockSettings->year            = Clock_INITIAL_YEAR;
    pClockSettings->eMeridiem       = Clock_INITIAL_MERIDIEM;
}



/**
 * @brief Convert a Clock_eMonths_t enum to string
 *
 * @param buffer String Buffer
 * @param eMonth Month Enum
 */
static void Clock_ConvertMonthToString( char *buffer, Clock_eMonths_t eMonth )
{
    sprintf( buffer, "%s", Clock_aMonthsOfTheYear[ eMonth ] );
}



/**
 * @brief Convert a Clock_eDays_t enum to string
 *
 * @param buffer String Buffer
 * @param eDay Day Enum
 */
static void Clock_ConvertDayToString( char *buffer, Clock_eDays_t eDay )
{
    sprintf( buffer, "%s", Clock_aDaysOfTheWeek[ eDay ] );
}



/**
 * @brief Convert a number to a string
 *
 * @param buffer String buffer
 * @param num Number to convert
 */
static void Clock_ConvertNumToString( char *buffer, uint32_t num )
{
    sprintf(buffer, "%lu", num);
}



/**
 * @brief Convert Hour/Min/Merdiem numerical values into a string representation
 *
 * @param buffer String Buffer
 * @param minutes Numerical value of minutes
 * @param hours Numerical value of hours
 * @param eMeridiem Meridiem Enum
 */
static void Clock_ConvertTimeToString( char *buffer, uint8_t minutes, uint8_t hours, Clock_eMeridiem_t eMeridiem )
{
    // Temporary buffer for formatted time
    char timeString[20];

    if( Clock_bIs24Htime == true )
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

        if (eMeridiem == Clock_eMeridiemAM) {
            snprintf(buffer, 24, "%s AM", timeString);
        } else {
            snprintf(buffer, 24, "%s PM", timeString);
        }
    }
}
