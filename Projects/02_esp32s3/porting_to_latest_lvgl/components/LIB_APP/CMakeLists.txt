# Get all .c files in this component
file(GLOB_RECURSE SOURCES "*.c")

# Get all folders (for includes)
file(GLOB_RECURSE INCLUDE_DIRS LIST_DIRECTORIES true "*")
list(FILTER INCLUDE_DIRS INCLUDE REGEX ".*/$")  # Keep only directories

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS "APP_CLOCK" "APP_COMMON" "APP_CTRL_PANEL" "APP_MAIN"
    REQUIRES "espressif__esp_lvgl_port"
)