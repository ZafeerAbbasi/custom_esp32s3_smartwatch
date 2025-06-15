idf_component_register(
    SRCS "main.c"
    REQUIRES "LIB_HAL" "LIB_COMMON"
    INCLUDE_DIRS ".")

set_source_files_properties(
    ${LV_DEMOS_SOURCES}
    PROPERTIES COMPILE_OPTIONS
    -DLV_LVGL_H_INCLUDE_SIMPLE)
