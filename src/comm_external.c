#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "tusb.h"
#include "bsp/board.h"
#include "comm_external.h"
#include "task_internal.h"
#include "usb_descriptors.h"


void comm_external_init(void)
{
	board_init();
	tusb_init();
	comm_external_queue = xQueueCreate(10, sizeof(uint8_t));
}

bool comm_external_key_received(uint8_t *key)
{
	if (pdTRUE == xQueueReceive(comm_external_queue, key, 0))
	{
		return true;
	}
	return false;
}

bool comm_external_send_usb(uint8_t *key)
{
	uint8_t key_report[6] = {0};
	key_report[0] = *key;

	tud_hid_keyboard_report(0, 0, key_report);
}

bool comm_external_clear_usb_report(void)
{
	uint8_t key_report[6] = {0};
	tud_hid_keyboard_report(0, 0, key_report);
}

void comm_external_task(void *pvParameters)
{
	comm_external_init();
	
	TickType_t task_delay = TASK_DELAY_DEF;
	bool usb_sent = false;	
	uint8_t key;

	while(1)
	{
		tud_task();

		if (tud_hid_ready()) {
			if (usb_sent)
			{
				comm_external_clear_usb_report();
				usb_sent = false;
			} 
			else if (comm_external_key_received(&key))
			{
				comm_external_send_usb(&key);
				usb_sent = true;
				task_delay = TASK_DELAY_DEF;
			}
			else
			{
				task_delay = TASK_DELAY_DEF;
			}
		}

		vTaskDelay(task_delay);
	}
}
