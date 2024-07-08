
#include "FreeRTOS.h"
#include "queue.h"

QueueHandle_t comm_external_queue;

void comm_external_task(void *pvParameters);
