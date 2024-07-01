#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define NUM_COLUMNS 5
#define NUM_ROWS 4

int columns_gpios[NUM_COLUMNS] = {5, 6, 7, 9, 10};
int rows_gpios[NUM_ROWS] = {11, 12, 13, 14};

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
		vTaskDelay(10);
		for (int j = 0; j < NUM_ROWS; ++j)
		{
			if (gpio_get(rows_gpios[j]))
			{
				printf("COL %d ROW %d selected\n", i, j);
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
		vTaskDelay(500);
		printf("keystrokes check\n");
	}
}
