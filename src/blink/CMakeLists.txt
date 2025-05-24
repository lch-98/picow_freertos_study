add_executable(picow_blink
    main.cpp
)

target_include_directories(picow_blink PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    #${PICO_SDK_PATH}/src/rp2_common/pico_cyw43_arch/include
    #${PICO_SDK_PATH}/lib/cyw43-driver/src
)

target_link_libraries(picow_blink 
    pico_stdlib 
    pico_cyw43_arch_none 
    FreeRTOS-Kernel-Heap4
)

pico_add_extra_outputs(picow_blink)