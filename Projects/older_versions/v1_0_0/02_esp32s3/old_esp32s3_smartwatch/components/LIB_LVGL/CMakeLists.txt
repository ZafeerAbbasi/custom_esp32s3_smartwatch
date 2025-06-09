idf_component_register(SRCS "lvgl_app.c"
                  INCLUDE_DIRS "."
                  REQUIRES "LIB_HAL" "espressif__esp_lvgl_port" )