#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "keystrokes.h"
#include "task_internal.h"

#define PRESSED true
#define UNPRESSED false

extern QueueHandle_t keystroke_queue;

int columns_gpios[NUM_COLUMNS] = {5, 6, 7, 9, 10};
int rows_gpios[NUM_ROWS] = {11, 12, 13, 14};

bool switch_pressed[NUM_COLUMNS][NUM_ROWS] = {{0}};

void keystrokes_init(void)
{
	// Initializes column gpios
	for (int i = 0; i < NUM_COLUMNS; ++i)
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

void keystrokes_check(void)
{
	for (int i = 0; i < NUM_COLUMNS; ++i)
	{
		gpio_put(columns_gpios[i], 1);
	    sleep_us(100);	
		for (int j = 0; j < NUM_ROWS; ++j)
		{
			if (gpio_get(rows_gpios[j]))
			{
				switch_pressed[i][j] = PRESSED;		
			} else if (switch_pressed[i][j]){
				switch_pressed[i][j] = UNPRESSED;		
				keystroke_t keystroke;
				keystroke.split = 0;
				keystroke.col = i;
				keystroke.row = j;
				xQueueSend(keystroke_queue, &keystroke, 0);
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
