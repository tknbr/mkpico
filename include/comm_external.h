
#include "FreeRTOS.h"
#include "queue.h"

QueueHandle_t comm_external_queue;

// Comm external main task, to be executed by FreeRTOS scheduler
void comm_external_task(void *pvParameters);
