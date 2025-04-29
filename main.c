#include "bsp/board.h"
#include "tusb.h"
#include "pico/stdlib.h"
#include <string.h>

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

// ---- TinyUSB required descriptors and callbacks ----

uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD()
};

uint8_t const *tud_descriptor_report_cb(void) {
  return desc_hid_report;
}

uint16_t tud_descriptor_report_size_cb(void) {
  return sizeof(desc_hid_report);
}

uint8_t const *tud_descriptor_device_cb(void) {
  static const tusb_desc_device_t desc_device = {
    .bLength = sizeof(tusb_desc_device_t),
    .bDescriptorType = TUSB_DESC_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = TUSB_CLASS_MISC,
    .bDeviceSubClass = MISC_SUBCLASS_COMMON,
    .bDeviceProtocol = MISC_PROTOCOL_IAD,
    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor = 0xCafe,
    .idProduct = 0x4000,
    .bcdDevice = 0x0100,
    .iManufacturer = 0x01,
    .iProduct = 0x02,
    .iSerialNumber = 0x03,
    .bNumConfigurations = 0x01
  };
  return (uint8_t const *)&desc_device;
}

#define CONFIG_TOTAL_LEN 32
uint8_t const *tud_descriptor_configuration_cb(uint8_t index) {
  static uint8_t desc_cfg[CONFIG_TOTAL_LEN] = {0}; // dummy config
  return desc_cfg;
}

void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id,
                           uint8_t report_type, uint8_t const* buffer, uint16_t bufsize) {
  // Optional: handle received HID reports from host
}

uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id,
                               hid_report_type_t report_type,
                               uint8_t* buffer, uint16_t reqlen) {
  // Optional: return HID report to host
  return 0;
}

uint8_t const *tud_hid_descriptor_report_cb(void) {
  return desc_hid_report;
}

uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
  static uint16_t desc_str[32];
  const char* str = "";

  switch(index) {
    case 0: {
      static const uint16_t lang_id[] = { 0x0409 };
      return lang_id;
    }
    case 1: str = "Maker"; break;
    case 2: str = "Pico HID"; break;
    case 3: str = "123456"; break;
    default: return NULL;
  }

  uint8_t chr_count = strlen(str);
  if (chr_count > 31) chr_count = 31;

  desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * chr_count + 2);
  for (uint8_t i = 0; i < chr_count; ++i)
    desc_str[1 + i] = str[i];

  return desc_str;
}