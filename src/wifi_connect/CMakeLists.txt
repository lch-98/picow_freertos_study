add_executable(wifi_connect
    wifi_connect.c
)

target_include_directories(wifi_connect PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}  # target for "src/wifi_connect" folder
    ${CMAKE_CURRENT_LIST_DIR}/.. # target for "src" folder
)

target_link_libraries(wifi_connect 
    pico_stdlib 
    pico_stdio_usb  # if you want chk terminal print
    pico_cyw43_arch_lwip_threadsafe_background
)

pico_add_extra_outputs(wifi_connect)