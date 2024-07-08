#include "FreeRTOS.h" /* Must come first. */
#include "task.h"     /* RTOS task related API prototypes. */
#include "pico/stdlib.h"
#include "keyboard_internal.h"
#include "keystrokes.h"
#include "task_internal.h"
#include "comm_internal.h"
#include "brain.h"
#include <stdio.h>
#include "comm_external.h"


#define GPIO_OUT 1

void toggle_led(void *pvParameters) {
    
    // init gpio
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    // endless loop
    while (1) { 
    // turn on
        gpio_put(PICO_DEFAULT_LED_PIN, ROW);
    // wait
        vTaskDelay(500);
    // turn off
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
    // wait
        vTaskDelay(500);
    }
}


int main() {

    // Initialize pi
    //stdio_init_all();
    
	// Define tasks
    xTaskCreate(toggle_led,
				"led",
				TASK_DEFS); 
	xTaskCreate(brain_task,
				"brain",
				TASK_DEFS);
    xTaskCreate(keystrokes_task,
				"keystrokes",
				TASK_DEFS);
	xTaskCreate(comm_internal_task,
				"comm_internal",
				TASK_DEFS);
	xTaskCreate(comm_external_task,
				"comm_external",
				TASK_DEFS);
	// Run scheduler    
    vTaskStartScheduler();

	while(1) {}
}
