#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "pico/stdlib.h"
#include "stdio.h"
#include "keystrokes.h"
#include "comm_external.h"
#include "comm_internal.h"
#include "class/hid/hid_device.h"
#include "keymap.h"
#include "compile.h"
#include "task_internal.h"

#define NUM_SPLITS 2
#define NUM_LAYERS 1

extern QueueHandle_t keystroke_queue;
extern QueueHandle_t comm_external_queue;

#if defined(ROLE_SLAVE)
extern QueueHandle_t comm_internal_queue;
#endif

extern size_t keymap_layers;
extern uint8_t keymap[][NUM_ROWS][NUM_COLS];

uint8_t layer;

void brain_init(void)
{
    // init queues
    keystroke_queue = xQueueCreate(QUEUE_DEF_SIZE, sizeof(keystroke_t));

    // init layer
    layer = 0;
}

void brain_check(void)
{
    // check queues
    keystroke_t keystroke;
    while(pdTRUE == xQueueReceive(keystroke_queue, &keystroke, 0))
    {
        #if defined(ROLE_MASTER)
        uint8_t key = keymap[layer][keystroke.row][keystroke.col];
        //uint8_t key = HID_KEY_Q;
        xQueueSend(comm_external_queue, &key, 0);

        
        #endif
    }
}

void brain_task(void *pvParameters)
{
    //led_blink();
    brain_init();
    while(1)
    {
        brain_check();
        vTaskDelay(200);
    }
}
