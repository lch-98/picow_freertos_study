#include "pico/stdlib.h"
#include "lcd_sdk/lcd.h"

int main() {
    stdio_init_all();
    lcd_init();
    lcd_fill_screen(rgb565(0, 0, 0)); // 검정

    lcd_draw_text_mixed(5, 10, "기온 : -10.0℃ ", rgb565(255, 255, 0), rgb565(0, 0, 0));
    lcd_draw_text_mixed(5, 30, "날씨 : 맑음", rgb565(255, 255, 0), rgb565(0, 0, 0));
    
    while (1);
}