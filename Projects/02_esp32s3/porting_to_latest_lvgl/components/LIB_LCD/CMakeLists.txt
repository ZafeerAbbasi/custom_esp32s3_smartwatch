idf_component_register(SRCS "lcd.c"
                  INCLUDE_DIRS "."
                  REQUIRES "driver" "espressif__esp_lcd_touch")