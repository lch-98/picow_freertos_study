#include "pico/stdlib.h"
#include "lcd_sdk/lcd.h"

// bit map (16*16)
const uint16_t umbrella_bitmap[16 * 16] = {
    // 여기에 256개의 RGB565 색상값 넣으세요
    [0 ... 255] = 0xFFE0
};

int main() {
    stdio_init_all();
    lcd_init();
    lcd_fill_screen(rgb565(0, 0, 0)); // 검정

    lcd_draw_text(10, 20, "Robot Engineer!!", rgb565(255, 255, 0), rgb565(0, 0, 0));
    // x=48,y=64에 위치하는 (16 by 16 pixel)정사각형 그리기 예시
    // lcd_draw_bitmap(48, 64, 16, 16, umbrella_bitmap);
    // x=48,y=64에 위치하는 (16 by 16 pixel)정사각형을 두배 확대해서 32 by 32 pixel로 그리기 예시
    lcd_draw_bitmap_scaled(48, 64, 16, 16, umbrella_bitmap, 2);

    while (1);
}