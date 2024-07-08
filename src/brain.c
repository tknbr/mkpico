#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "pico/stdlib.h"
#include "stdio.h"
#include "keystrokes.h"
#include "comm_external.h"
#include "class/hid/hid_device.h"

#define NUM_SPLITS 2
#define NUM_LAYERS 1

extern QueueHandle_t keystroke_queue;
extern QueueHandle_t comm_external_queue;

char key_mapping[NUM_LAYERS][NUM_SPLITS][NUM_ROWS][NUM_COLUMNS] = 
	  {{  {{'q', 'w', 'e', 'r', 't'},
		   {'a', 's', 'd', 'f', 'g'},
		   {'z', 'x', 'c', 'v', 'b'},
		   {NULL, NULL, NULL, '-', '-'}},

          {{'p', 'o', 'i', 'u', 'y'},
           {'-', 'l', 'k', 'j', 'h'},
		   {'-', '-', '-', 'm', 'n'},
		   {NULL, NULL, NULL, '-', '-'}} }};


void brain_init(void)
{
	// init queues
	keystroke_queue = xQueueCreate(10, sizeof(keystroke_t));
}

void brain_check(void)
{
	// check queues
	keystroke_t keystroke;
	while(pdTRUE == xQueueReceive(keystroke_queue, &keystroke, 0))
	{
		//printf("Keystroke received in brain, col %d, row %d \n", keystroke.col, keystroke.row);
		uint8_t key;
		switch(keystroke.row) {
			case 0: 
				key = HID_KEY_A;
				break;
			case 1:
				key = HID_KEY_B;
				break;
			case 2:
				key = HID_KEY_C;
				break;
			case 3:
				key = HID_KEY_D;
				break;
			default:
				key = HID_KEY_E;
				break;
		}
		xQueueSend(comm_external_queue, &key, 0);
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
