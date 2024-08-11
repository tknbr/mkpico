// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"

// Pico SDk includes
#include "pico/stdlib.h"

// General C includes
#include <stdio.h>

// Project includes
#include "keyboard_internal.h"
#include "keystrokes.h"
#include "task_internal.h"
#include "brain.h"
#include "comm_external.h"
#include "comm_internal.h"
#include "led.h"


int main() {
    
    // Define tasks
    #if defined(ROLE_CONTROLLER)
    xTaskCreate(led_task,
                "led",
                TASK_DEFS); 

    xTaskCreate(brain_task,
                "brain",
                TASK_DEFS);
    #endif

    xTaskCreate(keystrokes_task,
                "keystrokes",
                TASK_DEFS);

    #if defined(ROLE_CONTROLLER)
    xTaskCreate(comm_external_task,
                "comm_external",
                TASK_DEFS);
    #endif

    comm_internal_init();

    // Run scheduler    
    vTaskStartScheduler();

    while(1) {}
}
