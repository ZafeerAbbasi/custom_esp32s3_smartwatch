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

#define CLOCK_INITIAL_SECOND                ((uint8_t) 0)
#define CLOCK_INITIAL_MINUTE                ((uint8_t) 54)
#define CLOCK_INITIAL_HOUR                  ((uint8_t) 16)
#define CLOCK_INITIAL_DATE                  ((uint8_t) 24)
#define CLOCK_INITIAL_YEAR                  ((uint16_t) 2025)
#define CLOCK_INITIAL_MERIDIEM              CLOCK_eMeridiemPM
#define CLOCK_INITIAL_DAY                   CLOCK_eDayThursday
#define CLOCK_INITIAL_MONTH                 CLOCK_eMonthApr

/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/

bool CLOCK_bIs24Htime = false;
const char *CLOCK_aDaysOfTheWeek[ ] =
{
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};
const char *CLOCK_aMonthsOfTheYear[ ] =
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

static void clock_SetInitialClockSettings( CLOCK_zClockTimeFields_t *ClockSettings );
static void clock_ConvertMonthToString( char *buffer, CLOCK_eMonths_t eMonth );
static void clock_ConvertDayToString( char *buffer, CLOCK_eDays_t eDay );
static void clock_ConvertNumToString( char *buffer, uint32_t num );
static void clock_ConvertTimeToString( char *buffer, uint8_t minutes, uint8_t hours, CLOCK_eMeridiem_t eMeridiem );

/* User code -----------------------------------------------------------------*/

/**
 * @brief Initialize the Clock Screen
 *
 * @param pUserClockObj Pointer to the User Clock Object from the Main Watch Object
 * @param pParentObj Pointer to the parent obj ( Main Watch Container )
 */
void CLOCK_Init( CLOCK_zUserClockObj_t *pUserClockObj, lv_obj_t *pParentObj )
{
    lv_obj_t *pMainContainerObj                             = pParentObj;
    lv_obj_t *pClockContainerObj                            = pUserClockObj->pClockContainerObj;
    lv_obj_t **ppClockLabelsArray                           = pUserClockObj->aClockLabelObjs;
    CLOCK_zClockTimeFields_t *pCurrentTimeSettings          = &pUserClockObj->zCurrentClockSettings;
    char clockTimeStr[ 25 ]                                 = { 0 };
    char clockDayStr[ 15 ]                                  = { 0 };
    char clockDateStr[ 15 ]                                 = { 0 };
    char clockMonthStr[ 15 ]                                = { 0 };
    char clockYearStr[ 15 ]                                 = { 0 };

    /* Set the Clock Settings to default values */
    clock_SetInitialClockSettings( &pUserClockObj->zCurrentClockSettings );

    /* Create Clock Container Obj on main container and remove default styling */
    pClockContainerObj = lv_obj_create( pMainContainerObj );
    COMMON_RegisterUserObj( pClockContainerObj, COMMON_eTypeDontTrack );
    lv_obj_remove_style_all( pClockContainerObj );
    lv_obj_set_size( pClockContainerObj, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT );

    /* Configure Clock Container Background */
    lv_obj_set_style_bg_opa( pClockContainerObj, LV_OPA_TRANSP, LV_PART_MAIN );

    /* Initialize the label objs */
    for( int i = 0; i < CLOCK_eLabelCount; i++ )
    {
        ppClockLabelsArray[ i ] = lv_label_create( pClockContainerObj );

        /* TODO: ADD IF STATEMENT BASED ON THEME SELECT TEXT COLOR */
        lv_obj_set_style_text_color( ppClockLabelsArray[ i ], lv_color_white( ), LV_PART_MAIN );
    }

    /* Format the clock data into a string format for use in label */
    clock_ConvertTimeToString( clockTimeStr,
                                    pCurrentTimeSettings->minutes,
                                    pCurrentTimeSettings->hour,
                                    pCurrentTimeSettings->eMeridiem  );
    clock_ConvertDayToString( clockDayStr, pCurrentTimeSettings->eDay );
    clock_ConvertMonthToString( clockMonthStr, pCurrentTimeSettings->eMonth );
    clock_ConvertNumToString( clockDateStr, ( uint32_t)pCurrentTimeSettings->date );
    clock_ConvertNumToString( clockYearStr, pCurrentTimeSettings->year );

    /* Set labels with default values */
    lv_label_set_text( ppClockLabelsArray[ CLOCK_eLabelTime ], clockTimeStr );
    lv_label_set_text( ppClockLabelsArray[ CLOCK_eLabelDate ], clockDateStr );
    lv_label_set_text( ppClockLabelsArray[ CLOCK_eLabelDay ], clockDayStr );
    lv_label_set_text( ppClockLabelsArray[ CLOCK_eLabelMonth ], clockMonthStr );
    lv_label_set_text( ppClockLabelsArray[ CLOCK_eLabelYear ], clockYearStr );

    /* Set the label fonts */
    lv_obj_set_style_text_font(ppClockLabelsArray[ CLOCK_eLabelDay ], &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_font(ppClockLabelsArray[ CLOCK_eLabelMonth ], &lv_font_montserrat_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(ppClockLabelsArray[ CLOCK_eLabelDate ], &lv_font_montserrat_40, LV_PART_MAIN);
    lv_obj_set_style_text_font(ppClockLabelsArray[ CLOCK_eLabelYear ], &lv_font_montserrat_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(ppClockLabelsArray[ CLOCK_eLabelTime ], &lv_font_montserrat_40, LV_PART_MAIN);

    /* Align the labels */
    lv_obj_align(ppClockLabelsArray[ CLOCK_eLabelTime ], LV_ALIGN_CENTER, LV_PCT( -3 ), LV_PCT( 12 ));
    lv_obj_align(ppClockLabelsArray[ CLOCK_eLabelDate ], LV_ALIGN_TOP_LEFT, LV_PCT(8), LV_PCT(20));
    lv_obj_align(ppClockLabelsArray[ CLOCK_eLabelDay ], LV_ALIGN_TOP_LEFT, LV_PCT(8), LV_PCT(10));
    lv_obj_align(ppClockLabelsArray[ CLOCK_eLabelMonth ], LV_ALIGN_TOP_LEFT, LV_PCT(8), LV_PCT(15));
    lv_obj_align(ppClockLabelsArray[ CLOCK_eLabelYear ], LV_ALIGN_TOP_LEFT, LV_PCT(8), LV_PCT(35));

    /* TODO: Create a timer for 1 second, to update the seconds value */


}



/**
 * @brief Set the Clock Time Fields to Inital Values
 *
 * @param pClockSettings Pointer to the Clock Time Fields struct from User Clock Object
 */
static void clock_SetInitialClockSettings( CLOCK_zClockTimeFields_t *pClockSettings )
{
    /* Set the fields to the default values */
    pClockSettings->seconds         = CLOCK_INITIAL_SECOND;
    pClockSettings->minutes         = CLOCK_INITIAL_MINUTE;
    pClockSettings->hour            = CLOCK_INITIAL_HOUR;
    pClockSettings->eDay            = CLOCK_INITIAL_DAY;
    pClockSettings->date            = CLOCK_INITIAL_DATE;
    pClockSettings->eMonth          = CLOCK_INITIAL_MONTH;
    pClockSettings->year            = CLOCK_INITIAL_YEAR;
    pClockSettings->eMeridiem       = CLOCK_INITIAL_MERIDIEM;
}



/**
 * @brief Convert a CLOCK_eMonths_t enum to string
 *
 * @param buffer String Buffer
 * @param eMonth Month Enum
 */
static void clock_ConvertMonthToString( char *buffer, CLOCK_eMonths_t eMonth )
{
    sprintf( buffer, "%s", CLOCK_aMonthsOfTheYear[ eMonth ] );
}



/**
 * @brief Convert a CLOCK_eDays_t enum to string
 *
 * @param buffer String Buffer
 * @param eDay Day Enum
 */
static void clock_ConvertDayToString( char *buffer, CLOCK_eDays_t eDay )
{
    sprintf( buffer, "%s", CLOCK_aDaysOfTheWeek[ eDay ] );
}



/**
 * @brief Convert a number to a string
 *
 * @param buffer String buffer
 * @param num Number to convert
 */
static void clock_ConvertNumToString( char *buffer, uint32_t num )
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
static void clock_ConvertTimeToString( char *buffer, uint8_t minutes, uint8_t hours, CLOCK_eMeridiem_t eMeridiem )
{
    // Temporary buffer for formatted time
    char timeString[20];

    if( CLOCK_bIs24Htime == true )
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

        if (eMeridiem == CLOCK_eMeridiemAM) {
            snprintf(buffer, 24, "%s AM", timeString);
        } else {
            snprintf(buffer, 24, "%s PM", timeString);
        }
    }
}
