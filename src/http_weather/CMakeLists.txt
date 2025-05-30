add_executable(http_weather
    http_weather.c
    ntp_sync/ntp_client.c
)

target_include_directories(http_weather PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(http_weather
    pico_stdlib
    pico_stdio_usb  # usb port connect -> /dev/ttyACM0, if you want chk terminal print
    pico_cyw43_arch_lwip_threadsafe_background
)

pico_add_extra_outputs(http_weather)