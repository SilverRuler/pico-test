#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#ifndef CFG_TUSB_MCU
#define CFG_TUSB_MCU             OPT_MCU_RP2040
#endif

#ifndef CFG_TUSB_RHPORT0_MODE
#define CFG_TUSB_RHPORT0_MODE    OPT_MODE_DEVICE
#endif

#ifndef CFG_TUSB_OS
#define CFG_TUSB_OS              OPT_OS_NONE
#endif

#ifndef CFG_TUD_HID
#define CFG_TUD_HID              1
#endif

#ifndef CFG_TUD_HID_EP_BUFSIZE
#define CFG_TUD_HID_EP_BUFSIZE   64
#endif

#endif /* _TUSB_CONFIG_H_ */