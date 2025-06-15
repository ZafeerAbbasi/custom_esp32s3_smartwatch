idf_component_register(SRCS "FT3168/ft3168.c" "SH8601A0/sh8601a0.c" "TCA9554/tca9554.c"
                  INCLUDE_DIRS "."
                  REQUIRES "esp_io_expander_tca9554" "esp_lcd_touch_ft5x06" "esp_lcd_sh8601" "lvgl" )