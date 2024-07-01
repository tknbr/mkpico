#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "pico/stdlib.h"
#include "stdio.h"
#include "keystrokes.h"

extern QueueHandle_t keystroke_queue;

void brain_init(void)
{
	// init queues
	keystroke_queue = xQueueCreate(10, sizeof(keystroke_t));
}

void brain_check(void)
{
	// check queues
	keystroke_t keystroke;
	while(xQueueReceive(keystroke_queue, &keystroke, 0))
	{
		printf("Keystroke received in brain, col %d, row %d \n", keystroke.col, keystroke.row);
	}
}

void brain_task(void *pvParameters)
{
	brain_init();
	while(1)
	{
		brain_check();
		vTaskDelay(200);
	}
}
