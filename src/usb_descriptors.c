#include "tusb.h"

// HID Report Descriptor
uint8_t const desc_hid_report[] = {
    TUD_HID_REPORT_DESC_KEYBOARD()
};

// Device descriptor
tusb_desc_device_t const desc_device = {
    .bLength = sizeof(tusb_desc_device_t),
    .bDescriptorType = TUSB_DESC_DEVICE,
    .bcdUSB = 0x0200,

    .bDeviceClass = TUSB_CLASS_HID,                  // HID class
    .bDeviceSubClass = HID_SUBCLASS_BOOT,            // Boot subclass
    .bDeviceProtocol = HID_ITF_PROTOCOL_KEYBOARD,        // Keyboard protocol
    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,

    .idVendor = 0xCafe,                              // Vendor ID
    .idProduct = 0x4000,                             // Product ID
    .bcdDevice = 0x0100,                             // Device release number

    .iManufacturer = 0x01,                           // Manufacturer string index
    .iProduct = 0x02,                                // Product string index
    .iSerialNumber = 0x03,                           // Serial number string index

    .bNumConfigurations = 0x01                       // Number of configurations
};

// Configuration descriptor
uint8_t const desc_configuration[] = {
    // Configuration Descriptor
    TUD_CONFIG_DESCRIPTOR(1,                           // Configuration number
                          1,                           // Number of interfaces
                          0,                           // Configuration string index
                          (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN),  // Total length of data for this configuration
                          0,                           // Attributes (bus-powered)
                          100),                        // Maximum power consumption in 2mA units (100 * 2mA = 200mA)

    // HID Descriptor
    TUD_HID_DESCRIPTOR(0,                              // Interface number
                       0,                              // String index
                       HID_ITF_PROTOCOL_KEYBOARD,      // Protocol code
                       sizeof(desc_hid_report),        // HID report descriptor length
                       0x81,                           // Endpoint address (IN endpoint)
                       CFG_TUD_HID_EP_BUFSIZE,         // Endpoint size
                       10)                             // Polling interval in milliseconds
};

// String Descriptors
char const* string_desc_arr[] = {
    (const char[]) { 0x09, 0x04 }, // Supported language (English - 0x0409)
    "TinyUSB",                     // Manufacturer string
    "TinyUSB Device",              // Product string
    "123456",                      // Serial number string
};

uint16_t _desc_str[32];

// Device descriptor callback
uint8_t const* tud_descriptor_device_cb(void) {
    return (uint8_t const*)&desc_device;
}

// Configuration descriptor callback
uint8_t const* tud_descriptor_configuration_cb(uint8_t index) {
    (void)index;
    return desc_configuration;
}

// HID report descriptor callback
uint8_t const* tud_hid_descriptor_report_cb(uint8_t instance) {
    (void)instance;
    return desc_hid_report;
}

// Callback invoked when received GET REPORT request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    // Not used in this example, so we return 0
    return 0;
}

// Callback invoked when received SET REPORT request or via OUT endpoint
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    // Not used in this example, so we do nothing
}


// String descriptor callback
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void)langid;

    if (index == 0) {
        memcpy(&_desc_str[1], string_desc_arr[0], 2);
        _desc_str[0] = (TUSB_DESC_STRING << 8) | 4;
    } else {
        if (!(index < sizeof(string_desc_arr) / sizeof(string_desc_arr[0]))) return NULL;

        const char* str = string_desc_arr[index];
        uint8_t chr_count = strlen(str);
        if (chr_count > 31) chr_count = 31;
        for (uint8_t i = 0; i < chr_count; i++) {
            _desc_str[1 + i] = str[i];
        }
        _desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * chr_count + 2);
    }
    return _desc_str;
}

