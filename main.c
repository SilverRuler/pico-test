#include "bsp/board.h"
#include "tusb.h"

void hid_task(void);

int main(void) {
  board_init();
  tusb_init();

  while (1) {
    tud_task(); // tinyusb device task
    hid_task();
  }
}

void hid_task(void) {
  if (tud_hid_ready()) {
    uint8_t keycode[6] = { HID_KEY_T };

    tud_hid_keyboard_report(0, 0, keycode);
    sleep_ms(1000);
    tud_hid_keyboard_report(0, 0, NULL);
    sleep_ms(5000);
  }
}