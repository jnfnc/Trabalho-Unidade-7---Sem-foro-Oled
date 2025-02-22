# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")


include(pico_sdk_import.cmake)

project(semaforo_oled C CXX ASM)


pico_sdk_init()


add_executable(semaforo_oled semaforo_oled.c inc/ssd1306_i2c.c)

pico_set_program_name(semaforo_oled "semaforo_oled")
pico_set_program_version(semaforo_oled "0.1")


pico_enable_stdio_uart(semaforo_oled 0)
pico_enable_stdio_usb(semaforo_oled 1)


target_link_libraries(semaforo_oled
        pico_stdlib
        hardware_i2c
        hardware_gpio
        hardware_pwm)  


target_include_directories(semaforo_oled PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PICO_SDK_PATH}/src/common/pico_stdlib/include
        ${PICO_SDK_PATH}/src/rp2_common/hardware_pwm/include)  


target_link_libraries(semaforo_oled 
        
        )

pico_add_extra_outputs(semaforo_oled)
