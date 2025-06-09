/**
  ******************************************************************************
  * @file           : lcd.h
  * @brief          : Header for lcd module.
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
#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/spi_master.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_private/periph_ctrl.h"


/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/

extern esp_lcd_panel_io_handle_t LCD_zLcdIoHdl;
extern esp_lcd_panel_handle_t LCD_zLcdPanelHdl;

extern int32_t LCD_brightnessVal;


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

esp_err_t LCD_LcdControllerInit( void );
void LCD_SetDispOnOff( bool bIsOn );
void LCD_SetBacklightLvlPct( uint8_t uLvlPct );
void LCD_ControlLCDBackLightPWMTimer( bool bIsStart );

/* Exported defines ----------------------------------------------------------*/

/* LCD size */
#define LCD_H_RES 				(240)
#define LCD_V_RES 				(280)

/* LCD settings */
#define LCD_SPI_NUM 			(SPI2_HOST)
#define LCD_PIXEL_CLK_HZ 		(40 * 1000 * 1000)
#define LCD_CMD_BITS 			(8)
#define LCD_PARAM_BITS 			(8)
#define LCD_COLOR_SPACE 		(ESP_LCD_COLOR_SPACE_RGB)
#define LCD_BITS_PER_PIXEL 		(16)
#define LCD_DRAW_BUFF_DOUBLE 	(1)
#define LCD_DRAW_BUFF_HEIGHT 	(50)
#define LCD_BL_ON_LEVEL 		(1)
#define LCD_MAX_TRANSFER_SZ 	(LCD_H_RES * LCD_DRAW_BUFF_HEIGHT * sizeof(uint16_t))

/* LCD pins */
#define LCD_GPIO_SCLK 			(GPIO_NUM_6)
#define LCD_GPIO_MOSI 			(GPIO_NUM_7)
#define LCD_GPIO_RST 			(GPIO_NUM_8)
#define LCD_GPIO_DC 			(GPIO_NUM_4)
#define LCD_GPIO_CS 			(GPIO_NUM_5)
#define LCD_GPIO_BL 			(GPIO_NUM_15)

/* LCD backlight */
#define LEDC_PWM_TIMER          LEDC_TIMER_0
#define LEDC_PWM_MODE           LEDC_LOW_SPEED_MODE
#define LEDC_PWM_CHANNEL        LEDC_CHANNEL_0
#define LEDC_PWM_DUTY_RES       LEDC_TIMER_8_BIT // 0-255 duty
#define LEDC_PWM_FREQUENCY      5000             // 5 kHz


#ifdef __cplusplus
}
#endif

#endif /* __LCD_H */