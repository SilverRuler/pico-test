
#include <stdio.h>
#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"

const char* str = "Test OK\n";
uint8_t idx = 0;

uint8_t char_to_hid(char c) {
    if (c >= 'a' && c <= 'z') return HID_KEY_A + (c - 'a');
    if (c >= 'A' && c <= 'Z') return HID_KEY_A + (c - 'A');
    if (c == ' ') return HID_KEY_SPACE;
    if (c == '\n') return HID_KEY_ENTER;
    if (c >= '0' && c <= '9') return HID_KEY_0 + (c - '0');
    return HID_KEY_NONE;
}

int main() {
    board_init();
    tusb_init();
    sleep_ms(3000); // Wait for USB host to be ready

    while (1) {
        tud_task();

        if (tud_hid_ready() && str[idx]) {
            uint8_t keycode[6] = { char_to_hid(str[idx++]) };
            tud_hid_keyboard_report(0, 0, keycode);
            sleep_ms(100);
            tud_hid_keyboard_report(0, 0, NULL);
            sleep_ms(100);
        }
    }
}
