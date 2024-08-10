#include "FreeRTOS.h" /* Must come first. */
#include "task.h"     /* RTOS task related API prototypes. */
#include "pico/stdlib.h"
#include "keyboard_internal.h"
#include "keystrokes.h"
#include "task_internal.h"
#include "brain.h"
#include <stdio.h>
#include "comm_external.h"
#include "comm_internal.h"
#include "led.h"

int main() {

    // Initialize pi
    //stdio_init_all();
    
    // Define tasks
    xTaskCreate(led_task,
                "led",
                TASK_DEFS); 
    xTaskCreate(brain_task,
                "brain",
                TASK_DEFS);
    xTaskCreate(keystrokes_task,
                "keystrokes",
                TASK_DEFS);
    xTaskCreate(comm_external_task,
                "comm_external",
                TASK_DEFS);

    comm_internal_init();

    // Run scheduler    
    vTaskStartScheduler();

    while(1) {}
}
