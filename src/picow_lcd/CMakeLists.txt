add_executable(picow_lcd
    main.c
    lcd_sdk/lcd.c
    lcd_sdk/font.c
    lcd_sdk/icon.c
)

target_include_directories(picow_lcd PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(picow_lcd 
    pico_stdlib
    hardware_spi
    hardware_gpio
)

pico_add_extra_outputs(picow_lcd)