idf_component_register(SRCS "main.c" "img_test.c"
                    INCLUDE_DIRS "."
                    REQUIRES "LIB_I2C" "LIB_LCD" "LIB_TOUCH")
