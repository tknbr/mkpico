cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

# Pull in FreeRTOS
set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_LIST_DIR}/../FreeRTOS-Kernel)
include(toolchain-rp2040.cmake)

# Project name
project(mkpico)

pico_sdk_init()

# Configuration projects
add_executable(mkpico
    src/main.c
	src/keystrokes.c
	src/brain.c
	src/hooks.c
)

target_include_directories(mkpico PRIVATE
    config/
	include/
)

target_link_libraries(mkpico PRIVATE
    pico_stdlib
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap4
)

target_compile_options(mkpico PRIVATE -Wall)

# enable usb output, disable uart output
pico_enable_stdio_usb(mkpico 1)
pico_enable_stdio_uart(mkpico 0)

# Run the entire project in SRAM
# pico_set_binary_type(mkpico copy_to_ram)

pico_add_extra_outputs(mkpico)
