#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "keystrokes.h"
#include "task_internal.h"
#include "comm_internal.h"
#include "gpios.h"
#include "keymap.h"

#define UNPRESSED 0

extern QueueHandle_t keystroke_queue;

extern uint8_t columns_gpios[NUM_COLS];
extern uint8_t rows_gpios[NUM_ROWS];

__uint16_t switch_pressed[NUM_COLS][NUM_ROWS] = {{0}};

void keystrokes_init(void)
{
    // Initializes column gpios
    for (int i = 0; i < NUM_COLS; ++i)
    {
        gpio_init(columns_gpios[i]);
        gpio_set_dir(columns_gpios[i], GPIO_OUT);
    }

    // Initialize row gpios
    for (int j = 0; j < NUM_ROWS; ++j)
    {
        gpio_init(rows_gpios[j]);
        gpio_set_dir(rows_gpios[j], GPIO_IN);
        gpio_pull_down(rows_gpios[j]);
    }
}


void keystroke_send(keystroke_t *keystroke)
{
    #if defined(ROLE_MASTER)
    xQueueSend(keystroke_queue, keystroke, 0);
    #endif

    #if defined(ROLE_SLAVE)
    keystroke->col += 5;
    comm_internal_controller_send(keystroke);
    #endif
}

void keystrokes_check(void)
{
    for (int i = 0; i < NUM_COLS; ++i)
    {
        gpio_put(columns_gpios[i], 1);
        sleep_us(100);    
        for (int j = 0; j < NUM_ROWS; ++j)
        {
            if (gpio_get(rows_gpios[j]))
            {
                switch_pressed[i][j] += 1;

                if (switch_pressed[i][j] == 4)
                {
                    keystroke_t keystroke;
                    keystroke.split = 0;
                    keystroke.col = i;
                    keystroke.row = j;
                    keystroke_send(&keystroke);
                } else if (switch_pressed[i][j] > 7)
                {
                    keystroke_t keystroke;
                    keystroke.split = 0;
                    keystroke.col = i;
                    keystroke.row = j;
                    keystroke_send(&keystroke);
                }
            } else if (switch_pressed[i][j]){
                if (switch_pressed[i][j] > 0 && switch_pressed[i][j] < 4)
                {
                    keystroke_t keystroke;
                    keystroke.split = 0;
                    keystroke.col = i;
                    keystroke.row = j;
                    keystroke_send(&keystroke);
                }
                switch_pressed[i][j] = UNPRESSED;
            }
        
        } 
        gpio_put(columns_gpios[i], 0);
    }
}

void keystrokes_task(void *pvParameters)
{
    keystrokes_init();

    while(1)
    {
        keystrokes_check();
        vTaskDelay(TASK_DELAY_DEF);
    }
}
