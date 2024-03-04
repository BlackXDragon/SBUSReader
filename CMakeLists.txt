cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(SBUSReader C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

pico_sdk_init()

add_library(${PROJECT_NAME} STATIC src/SBUS.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC pico_stdlib hardware_uart hardware_gpio)

add_executable(${PROJECT_NAME}_test main.c)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME} pico_stdlib hardware_uart hardware_gpio)

pico_enable_stdio_usb(${PROJECT_NAME}_test 1)
pico_enable_stdio_uart(${PROJECT_NAME}_test 0)

pico_add_extra_outputs(${PROJECT_NAME}_test)