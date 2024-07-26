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

#define KEY_REPORT_SIZE 6


void comm_external_init(void)
{
	board_init();
	tusb_init();
	comm_external_queue = xQueueCreate(QUEUE_DEF_SIZE, sizeof(uint8_t));
}

bool comm_external_key_received(uint8_t *key)
{
	int key_report_index = 0;
	int ret = false;

	while (pdTRUE == xQueueReceive(comm_external_queue, &key[key_report_index], 0))
	{
		key_report_index++;
		ret = true;
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
	
	for (int i = 0; i < KEY_REPORT_SIZE; ++i)
	{
		key_report[i] = key[i];
	}

	return tud_hid_keyboard_report(0, 0, key_report);
}

bool comm_external_clear_usb_report(void)
{
	uint8_t key_report[6] = {0};
	return tud_hid_keyboard_report(0, 0, key_report);
}

void comm_external_task(void *pvParameters)
{
	comm_external_init();
	
	TickType_t task_delay = TASK_DELAY_DEF;
	bool usb_sent = false;

	while(1)
	{
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
