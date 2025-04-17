# Install script for directory: /Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/local/Cellar/llvm/20.1.2/bin/llvm-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/lvgl//src")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/include/lvgl/" TYPE DIRECTORY FILES "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/lvgl/lv_version.h;/usr/local/include/lvgl/lvgl.h;/usr/local/include/lvgl/lv_conf.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/include/lvgl" TYPE FILE FILES
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl/lv_version.h"
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl/lvgl.h"
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lv_conf.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/lvgl//examples")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/include/lvgl/" TYPE DIRECTORY FILES "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl/examples" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/lvgl//demos")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/include/lvgl/" TYPE DIRECTORY FILES "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl/demos" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/build/lvgl/lvgl.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/build/lib/liblvgl.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblvgl.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblvgl.a")
    execute_process(COMMAND "/usr/local/Cellar/llvm/20.1.2/bin/llvm-ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblvgl.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lvgl" TYPE FILE FILES
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl/lv_version.h"
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl/lvgl.h"
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lv_conf.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/build/lib/liblvgl_thorvg.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblvgl_thorvg.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblvgl_thorvg.a")
    execute_process(COMMAND "/usr/local/Cellar/llvm/20.1.2/bin/llvm-ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblvgl_thorvg.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lvgl" TYPE FILE FILES
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl/lv_version.h"
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl/lvgl.h"
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lv_conf.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/build/lib/liblvgl_demos.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblvgl_demos.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblvgl_demos.a")
    execute_process(COMMAND "/usr/local/Cellar/llvm/20.1.2/bin/llvm-ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblvgl_demos.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lvgl" TYPE FILE FILES
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl/lv_version.h"
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl/lvgl.h"
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lv_conf.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/build/lib/liblvgl_examples.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblvgl_examples.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblvgl_examples.a")
    execute_process(COMMAND "/usr/local/Cellar/llvm/20.1.2/bin/llvm-ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblvgl_examples.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lvgl" TYPE FILE FILES
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl/lv_version.h"
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lvgl/lvgl.h"
    "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/lv_conf.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/zafeer/Documents/GITHUB/Custom-ESP32-S3-Smartwatch/Projects/01_simulation_macOS/lv_port_pc_vscode/build/lvgl/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
