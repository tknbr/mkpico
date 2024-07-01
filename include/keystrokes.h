#include "FreeRTOS.h"
#include "queue.h"

typedef struct keystroke_e {
	int split;
	int col;
	int row;
} keystroke_t;

QueueHandle_t keystroke_queue;

void keystrokes_task(void *pvParameters);
