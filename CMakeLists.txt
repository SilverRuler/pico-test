cmake_minimum_required(VERSION 3.13)
set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(pico_hid_test_ok)
pico_sdk_init()

add_executable(pico_hid_test_ok
    main.c
)

target_include_directories(pico_hid_test_ok PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(pico_hid_test_ok pico_stdlib tinyusb_device tinyusb_board)

pico_add_extra_outputs(pico_hid_test_ok)