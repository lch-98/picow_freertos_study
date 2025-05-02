#include <cstdio>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

extern "C" {
    #include "FreeRTOS.h"
    #include "task.h"
}

void led_task(void *params)
{
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    stdio_init_all();

    if (cyw43_arch_init()) {
        std::printf("Wi-Fi init failed\n");
        return -1;
    }

    xTaskCreate(led_task, "LED_Task", 256, nullptr, 1, nullptr);
    vTaskStartScheduler();

    while (true) {
        // Should not reach here
    }

    return 0;
}
