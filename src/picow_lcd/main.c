#include "pico/stdlib.h"
#include "lcd_sdk/lcd.h"

int main() {
    stdio_init_all();
    lcd_init();
    lcd_fill_screen(rgb565(0, 0, 0)); // 검정

    lcd_draw_text(10, 20, "Hello, ST7735!", rgb565(255, 255, 0), rgb565(0, 0, 0));

    while (1);
}