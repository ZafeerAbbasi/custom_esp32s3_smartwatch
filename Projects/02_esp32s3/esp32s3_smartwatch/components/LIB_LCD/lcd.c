/**
  ******************************************************************************
  * @file           : lcd.c
  * @brief          : Low Level LCD Driver for ST7789 LCD Controller.
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

#include "lcd.h"


/* Typedef -------------------------------------------------------------------*/


/* Define --------------------------------------------------------------------*/


/* Macro ---------------------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/

/* LCD IO and panel */
esp_lcd_panel_io_handle_t LCD_zLcdIoHdl = NULL;
esp_lcd_panel_handle_t LCD_zLcdPanelHdl = NULL;

static const char *lcd_pTag = "MODULE_LCD";
static bool LCD_bIsBacklightOn = false;

/* Function prototypes -------------------------------------------------------*/

static void lcd_BackLightPWMInit( void );

/* User code -----------------------------------------------------------------*/

/**
 * @brief Initialize the LCD
 * 
 * @return esp_err_t ESP_OK on success, error code on failure
 */
esp_err_t LCD_LcdControllerInit( void )
{
    esp_err_t ret = ESP_OK;

    // /* LCD backlight */
    lcd_BackLightPWMInit( );

    /* Initialize the LCD SPI Bus */
    const spi_bus_config_t zLcdSpiBusConifg = 
    {
        .sclk_io_num        = LCD_GPIO_SCLK,
        .mosi_io_num        = LCD_GPIO_MOSI,
        .miso_io_num        = GPIO_NUM_NC,      // Not used
        .quadwp_io_num      = GPIO_NUM_NC,      // Not used
        .quadhd_io_num      = GPIO_NUM_NC,      // Not used
        .max_transfer_sz    = LCD_MAX_TRANSFER_SZ
    };
    ESP_GOTO_ON_ERROR( 
        spi_bus_initialize( LCD_SPI_NUM, &zLcdSpiBusConifg, SPI_DMA_CH_AUTO ), 
        err, 
        lcd_pTag, 
        "SPI bus initialization failed" );


    /* Initialize the LCD Panel IO */
    const esp_lcd_panel_io_spi_config_t zLcdPanelIoConfig = 
    {
        .dc_gpio_num       = LCD_GPIO_DC,
        .cs_gpio_num       = LCD_GPIO_CS,
        .pclk_hz           = LCD_PIXEL_CLK_HZ,
        .lcd_cmd_bits      = LCD_CMD_BITS,
        .lcd_param_bits    = LCD_PARAM_BITS,
        .spi_mode          = 0,
        .trans_queue_depth = 10
    };
    ESP_GOTO_ON_ERROR( 
        esp_lcd_new_panel_io_spi( 
            ( esp_lcd_spi_bus_handle_t )LCD_SPI_NUM, 
            &zLcdPanelIoConfig, 
            &LCD_zLcdIoHdl ),
        err,
        lcd_pTag,
        "New panel IO failed" );


    /* Install LCD Controller Driver */
    const esp_lcd_panel_dev_config_t zLcdPanelConfig = 
    {
        .reset_gpio_num    = LCD_GPIO_RST,
        .color_space       = LCD_COLOR_SPACE,
        .bits_per_pixel    = LCD_BITS_PER_PIXEL
    };
    ESP_GOTO_ON_ERROR( 
        esp_lcd_new_panel_st7789( 
            LCD_zLcdIoHdl, 
            &zLcdPanelConfig, 
            &LCD_zLcdPanelHdl ),
        err,
        lcd_pTag,
        "New panel failed" );

    
    /* Activate LCD */
    esp_lcd_panel_reset( LCD_zLcdPanelHdl );
    esp_lcd_panel_init( LCD_zLcdPanelHdl );
    esp_lcd_panel_mirror( LCD_zLcdPanelHdl, true, true );
    LCD_SetDispOnOff( true );

    /* LCD backlight on */
    LCD_SetBacklightLvlPct( 100 );

    /* Set Panel Gap and invert colors */
    esp_lcd_panel_set_gap( LCD_zLcdPanelHdl, 0, 20 );
    esp_lcd_panel_invert_color( LCD_zLcdPanelHdl, true );

    return ret;

err:
    /* Delete LCD panel on error */        
    if ( LCD_zLcdPanelHdl )
    {
        esp_lcd_panel_del( LCD_zLcdPanelHdl );
    }

    /* Delete LCD IO on error */
    if ( LCD_zLcdIoHdl )
    {
        esp_lcd_panel_io_del( LCD_zLcdIoHdl );
    }

    /* Free the SPI bus on error */
    spi_bus_free( LCD_SPI_NUM );

    return ret;
}



/**
 * @brief Set the LCD Backlight Level in percentage
 * 
 * @param uLvlPct Backlight level in percentage (0-100)
 */
void LCD_SetBacklightLvlPct( uint8_t uLvlPct )
{
    if( uLvlPct >= 100 ) // Check if the percentage is greater than 100
    {
        uLvlPct = 100;
    }
    else if( uLvlPct <= 0 ) // Check if the percentage is less than 0
    {
        uLvlPct = 0;
    }

    /* Calculate the Duty Cycle */
    uint32_t dutyCycle = ( uLvlPct * 255 ) / 100;

    /* Set the duty cycle for the backlight */
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_PWM_CHANNEL, dutyCycle);
    ledc_update_duty(LEDC_PWM_MODE, LEDC_PWM_CHANNEL);
}



/**
 * @brief Set the LCD display on or off
 * 
 * @param bIsOn true to turn on the display, false to turn it off 
 */
void LCD_SetDispOnOff( bool bIsOn )
{
    esp_lcd_panel_disp_on_off( LCD_zLcdPanelHdl, bIsOn );
}



/**
 * @brief Start/Stop the LCD Backlight PWM Timer
 * 
 * @param bIsStart true to start the timer, false to stop it
 */
void LCD_ControlLCDBackLightPWMTimer( bool bIsStart )
{
    if( bIsStart == true )
    {
        if( LCD_bIsBacklightOn == false )
        {
            /* Enable clock access and re-configure */
            periph_module_enable( PERIPH_LEDC_MODULE );
            lcd_BackLightPWMInit( );

            /* Update Flag */
            LCD_bIsBacklightOn = true;
        }
    }
    else
    {
        if( LCD_bIsBacklightOn == true )
        {
            /* Stop LEDC and Disable clock access */
            ledc_stop( LEDC_PWM_MODE, LEDC_PWM_CHANNEL, 0 );
            periph_module_disable( PERIPH_LEDC_MODULE );

            /* Update Flag */
            LCD_bIsBacklightOn = false;
        }
    }
}



/**
 * @brief Initialize the LCD Backlight PWM
 * 
 */
static void lcd_BackLightPWMInit( void )
{
    /* Timer configuration */
    ledc_timer_config_t zLcdPwmTimerConfig = 
    {
        .speed_mode         = LEDC_PWM_MODE,
        .timer_num          = LEDC_PWM_TIMER,
        .duty_resolution    = LEDC_PWM_DUTY_RES,
        .freq_hz            = LEDC_PWM_FREQUENCY,
        .clk_cfg            = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK( ledc_timer_config( &zLcdPwmTimerConfig ) );

    /* Channel configuration */
    ledc_channel_config_t zLcdPwmChannelConfig = 
    {
        .speed_mode         = LEDC_PWM_MODE,
        .channel            = LEDC_PWM_CHANNEL,
        .timer_sel          = LEDC_PWM_TIMER,
        .intr_type          = LEDC_INTR_DISABLE,
        .gpio_num           = LCD_GPIO_BL,
        .duty               = 0,
        .hpoint             = 0
    };
    ESP_ERROR_CHECK( ledc_channel_config( &zLcdPwmChannelConfig ) );

    /* Update Flag */
    LCD_bIsBacklightOn = true;
}