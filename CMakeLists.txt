
cmake_minimum_required(VERSION 3.13)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(pico_hid_test_ok)
pico_sdk_init()

add_executable(pico_hid_test_ok main.c)

pico_enable_stdio_usb(pico_hid_test_ok 0)
pico_enable_stdio_uart(pico_hid_test_ok 0)

target_compile_definitions(pico_hid_test_ok PRIVATE
    CFG_TUSB_MCU=OPT_MCU_RP2040
    CFG_TUSB_RHPORT0_MODE=OPT_MODE_DEVICE
    CFG_TUSB_OS=OPT_OS_PICO
)

target_link_libraries(pico_hid_test_ok
    pico_stdlib
    tinyusb_device
    tinyusb_board
)

pico_add_extra_outputs(pico_hid_test_ok)
