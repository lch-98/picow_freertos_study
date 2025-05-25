add_executable(http_get
    http_get.c
)

target_include_directories(http_get PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(http_get
    pico_stdlib
    pico_stdio_usb  # usb port connect -> /dev/ttyACM0, if you want chk terminal print
    pico_cyw43_arch_lwip_threadsafe_background
)

pico_add_extra_outputs(http_get)
