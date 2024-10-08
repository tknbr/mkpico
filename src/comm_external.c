// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Pico SDk includes
#include "pico/stdlib.h"
#include "bsp/board.h"

// General C includes
#include "stdio.h"

// TinyUSB includes
#include "tusb.h"

// Project includes
#include "comm_external.h"
#include "task_internal.h"
#include "usb_descriptors.h"
#include "keys.h"

// Report size defined by tinyUSB
#define KEY_REPORT_SIZE 6

// Modifier global
uint8_t modifier;

void comm_external_init(void)
{
    board_init();
    tusb_init();
    comm_external_queue = xQueueCreate(QUEUE_DEF_SIZE, sizeof(uint8_t));
    modifier = 0;
}

bool comm_external_key_exists_in_report(uint8_t *key, int index)
{
    bool ret = false;

    for(int i = index-1; i > 0; --i)
    {
        if (key[index] == key[i])
        {
            ret = true;
        }
    }

    return ret;
}

bool comm_external_key_received(uint8_t *key)
{
    int key_report_index = 0;
    int ret = false;

    while (pdTRUE == xQueueReceive(comm_external_queue, &key[key_report_index], 0))
    {
        // if we already have this key in the report, don't repeat it
        if (!comm_external_key_exists_in_report(key, key_report_index))
        {
            key_report_index++;
            ret = true;
        }

        if (key_report_index >= KEY_REPORT_SIZE) 
        {
            // reached limit, return
            break;
        }
        
    }

    return ret;
}

bool comm_external_send_usb(uint8_t *key)
{
    uint8_t key_report[6] = {0};
    bool default_key = false;
    
    for (int i = 0; i < KEY_REPORT_SIZE; ++i)
    {
        switch (key[i])
        {
            case K_SHFT:
                modifier |= MOD_SHFT;
                break;
            case K_CTRL:
                modifier |= MOD_CTRL;
                break;
            case K_ALT:
                modifier |= MOD_ALT;
                break;
            case 0:
                break;
            default:
                default_key = true;
                key_report[i] = key[i];
                break;
        }
    }

    if (default_key == true) {
        tud_hid_keyboard_report(0, modifier, key_report);
        modifier = 0;
    }

    return true;
}

bool comm_external_clear_usb_report(void)
{
    uint8_t key_report[6] = {0};
    return tud_hid_keyboard_report(0, 0, key_report);
}

void comm_external_task(void *pvParameters)
{
    comm_external_init();
    bool usb_sent = false;

    while(1)
    {
        // No task delay needed, tud_task should already do the work for us.
        tud_task();
        uint8_t key_report[KEY_REPORT_SIZE] = {0};

        if (tud_hid_ready()) {
            if (usb_sent)
            {
                comm_external_clear_usb_report();
                usb_sent = false;
            } 
            else if (comm_external_key_received(&key_report[0]))
            {
                comm_external_send_usb(&key_report[0]);
                usb_sent = true;
            }
        }
    }
}
