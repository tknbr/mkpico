// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Pico SDk includes
#include "pico/stdlib.h"

// General C includes
#include "stdio.h"

// Project includes
#include "keystrokes.h"
#include "comm_external.h"
#include "comm_internal.h"
#include "keymap.h"
#include "compile.h"
#include "task_internal.h"

// Queue used to receive keystrokes
extern QueueHandle_t keystroke_queue;
// Queue used to send keys externaly
extern QueueHandle_t comm_external_queue;
// Number of layers available
extern size_t keymap_layers;
// Keymap with the relation row/col key
extern uint8_t keymap[][NUM_ROWS][NUM_COLS];

// Current layer
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
        uint8_t key = keymap[layer][keystroke.row][keystroke.col];
        switch (key)
        {
            case K_LYRUP:
                if (layer+1 < keymap_layers)
                {
                    ++layer;
                    led_on();
                }
                break;
            case K_LYRDWN:
                if (layer-1 >= 0)
                {
                    --layer;
                    led_off();
                }
                break;
            case K_NULL:
                break;
            default:
                xQueueSend(comm_external_queue, &key, 0);
                break;
        }
    }
}

void brain_task(void *pvParameters)
{
    brain_init();
    while(1)
    {
        brain_check();
        vTaskDelay(TASK_DELAY_DEF);
    }
}
