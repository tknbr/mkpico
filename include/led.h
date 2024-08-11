#include "FreeRTOS.h"
#include "pico/stdlib.h"
#include "task.h"     /* RTOS task related API prototypes. */
#include "queue.h"
#include "task_internal.h"

QueueHandle_t led_queue;

// Led main task, to be executed by FreeRTOS scheduler periodically
void led_task(void *pvParameters);

// Makes pi pico led blink
void led_blink(void);

// Makes pi pico led on
void led_on(void);

// Makes pi pico led off
void led_off(void);