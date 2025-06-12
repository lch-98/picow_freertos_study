#include "pico/stdlib.h"
#include "lcd_sdk/lcd.h"
#include "lcd_sdk/icon.h"

int main() {
    stdio_init_all();
    lcd_init();
    lcd_fill_screen(rgb565(255, 255, 255)); // 흰색

    lcd_draw_text_mixed(5, 10, "기온 : N/A℃ ", rgb565(25, 25, 112), rgb565(255, 255, 255));
    lcd_draw_text_mixed(5, 30, "날씨 : N/A", rgb565(25, 25, 112), rgb565(255, 255, 255));
    lcd_draw_signnum_string_scaled(4, 53, "23:55", rgb565(25, 25, 112), rgb565(255, 255, 255), 3);
    lcd_draw_bitmap_scaled(40, 105, 50, 50, umbrella_bitmap, 1);

    while (1);
}