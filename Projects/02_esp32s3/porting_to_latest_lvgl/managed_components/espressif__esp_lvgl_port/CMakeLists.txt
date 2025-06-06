include($ENV{IDF_PATH}/tools/cmake/version.cmake) # $ENV{IDF_VERSION} was added after v4.3...

if("${IDF_VERSION_MAJOR}.${IDF_VERSION_MINOR}" VERSION_LESS "4.4")
    return()
endif()

set(ADD_SRCS "")
set(ADD_LIBS "")
set(PRIV_REQ "")
idf_build_get_property(target IDF_TARGET)
if(${target} STREQUAL "esp32p4")
    list(APPEND ADD_SRCS "src/common/ppa/lcd_ppa.c")
    list(APPEND ADD_LIBS idf::esp_driver_ppa)
    list(APPEND PRIV_REQ esp_driver_ppa)
endif()

# This component uses a CMake workaround, so we can compile esp_lvgl_port for both LVGL8.x and LVGL9.x
# At the time of idf_component_register() we don't know which LVGL version is used, so we only register an INTERFACE component (with no sources)
# Later, when we know the LVGL version, we create another CMake library called 'lvgl_port_lib' and link it to the 'esp_lvgl_port' INTERFACE component
idf_component_register(
        INCLUDE_DIRS "include"
        PRIV_INCLUDE_DIRS "priv_include"
        REQUIRES "esp_lcd"
        PRIV_REQUIRES "${PRIV_REQ}")

# Get LVGL version
idf_build_get_property(build_components BUILD_COMPONENTS)
if(lvgl IN_LIST build_components)
    set(lvgl_name lvgl) # Local component
    set(lvgl_ver $ENV{LVGL_VERSION}) # Get the version from env variable (set from LVGL v9.2)
else()
    set(lvgl_name lvgl__lvgl) # Managed component
    idf_component_get_property(lvgl_ver ${lvgl_name} COMPONENT_VERSION) # Get the version from esp-idf build system
endif()

if("${lvgl_ver}" STREQUAL "")
    message("Could not determine LVGL version, assuming v9.x")
    set(lvgl_ver "9.0.0")
endif()

# Select folder by LVGL version
message(STATUS "LVGL version: ${lvgl_ver}")
if(lvgl_ver VERSION_LESS "9.0.0")
    message(VERBOSE "Compiling esp_lvgl_port for LVGL8")
    set(PORT_FOLDER "lvgl8")
else()
    message(VERBOSE "Compiling esp_lvgl_port for LVGL9")
    set(PORT_FOLDER "lvgl9")
endif()

# Add LVGL port extensions
set(PORT_PATH "src/${PORT_FOLDER}")

idf_build_get_property(build_components BUILD_COMPONENTS)
if("espressif__button" IN_LIST build_components)
    list(APPEND ADD_SRCS "${PORT_PATH}/esp_lvgl_port_button.c")
    list(APPEND ADD_LIBS idf::espressif__button)
endif()
if("button" IN_LIST build_components)
    list(APPEND ADD_SRCS "${PORT_PATH}/esp_lvgl_port_button.c")
    list(APPEND ADD_LIBS idf::button)
endif()
if("espressif__esp_lcd_touch" IN_LIST build_components)
    list(APPEND ADD_SRCS "${PORT_PATH}/esp_lvgl_port_touch.c")
    list(APPEND ADD_LIBS idf::espressif__esp_lcd_touch)
endif()
if("esp_lcd_touch" IN_LIST build_components)
    list(APPEND ADD_SRCS "${PORT_PATH}/esp_lvgl_port_touch.c")
    list(APPEND ADD_LIBS idf::esp_lcd_touch)
endif()
if("espressif__knob" IN_LIST build_components)
    list(APPEND ADD_SRCS "${PORT_PATH}/esp_lvgl_port_knob.c")
    list(APPEND ADD_LIBS idf::espressif__knob)
endif()
if("knob" IN_LIST build_components)
    list(APPEND ADD_SRCS "${PORT_PATH}/esp_lvgl_port_knob.c")
    list(APPEND ADD_LIBS idf::knob)
endif()
if("espressif__usb_host_hid" IN_LIST build_components)
    list(APPEND ADD_SRCS "${PORT_PATH}/esp_lvgl_port_usbhid.c" "images/${PORT_FOLDER}/img_cursor.c")
    list(APPEND ADD_LIBS idf::espressif__usb_host_hid)
endif()
if("usb_host_hid" IN_LIST build_components)
    list(APPEND ADD_SRCS "${PORT_PATH}/esp_lvgl_port_usbhid.c" "images/${PORT_FOLDER}/img_cursor.c")
    list(APPEND ADD_LIBS idf::usb_host_hid)
endif()

# Include SIMD assembly source code for rendering, only for (9.1.0 <= LVG_version < 9.2.0) and only for esp32 and esp32s3
if((lvgl_ver VERSION_GREATER_EQUAL "9.1.0") AND (lvgl_ver VERSION_LESS "9.2.0"))
    if(CONFIG_IDF_TARGET_ESP32 OR CONFIG_IDF_TARGET_ESP32S3)
        message(VERBOSE "Compiling SIMD")
        if(CONFIG_IDF_TARGET_ESP32S3)
            file(GLOB_RECURSE ASM_SRCS ${PORT_PATH}/simd/*_esp32s3.S)    # Select only esp32s3 related files
        else()
            file(GLOB_RECURSE ASM_SRCS ${PORT_PATH}/simd/*_esp32.S)      # Select only esp32 related files
        endif()

        # Explicitly add all assembly macro files
        file(GLOB_RECURSE ASM_MACROS ${PORT_PATH}/simd/lv_macro_*.S)
        list(APPEND ADD_SRCS ${ASM_MACROS})
        list(APPEND ADD_SRCS ${ASM_SRCS})

        # Include component libraries, so lvgl component would see lvgl_port includes
        idf_component_get_property(lvgl_lib ${lvgl_name} COMPONENT_LIB)
        target_include_directories(${lvgl_lib} PRIVATE "include")

        # Force link .S files
        set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY INTERFACE_LINK_LIBRARIES "-u lv_color_blend_to_argb8888_esp")
        set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY INTERFACE_LINK_LIBRARIES "-u lv_color_blend_to_rgb565_esp")
        set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY INTERFACE_LINK_LIBRARIES "-u lv_color_blend_to_rgb888_esp")
        set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY INTERFACE_LINK_LIBRARIES "-u lv_rgb565_blend_normal_to_rgb565_esp")
        set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY INTERFACE_LINK_LIBRARIES "-u lv_rgb888_blend_normal_to_rgb888_esp")
    endif()
endif()

# Here we create the real lvgl_port_lib
add_library(lvgl_port_lib STATIC
    ${PORT_PATH}/esp_lvgl_port.c
    ${PORT_PATH}/esp_lvgl_port_disp.c
    ${ADD_SRCS}
    )
target_include_directories(lvgl_port_lib PUBLIC "include")
target_include_directories(lvgl_port_lib PRIVATE "priv_include")
target_link_libraries(lvgl_port_lib PUBLIC
    idf::esp_lcd
    idf::${lvgl_name}
    )
target_link_libraries(lvgl_port_lib PRIVATE
    idf::esp_timer
    ${ADD_LIBS}
    )

# Finally, link the lvgl_port_lib its esp-idf interface library
target_link_libraries(${COMPONENT_LIB} INTERFACE lvgl_port_lib)
