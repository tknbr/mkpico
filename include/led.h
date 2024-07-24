#include "FreeRTOS.h"
#include "pico/stdlib.h"
#include "task.h"     /* RTOS task related API prototypes. */
#include "queue.h"
#include "task_internal.h"

QueueHandle_t led_queue;

void led_task(void *pvParameters);

void led_blink(void);