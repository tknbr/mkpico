#include "FreeRTOS.h" /* Must come first. */
#include "task.h"     /* RTOS task related API prototypes. */
#include "pico/stdlib.h"
#include "keyboard_internal.h"
#include "keystrokes.h"
#include <stdio.h>


/** Central logic brain
 *
 *  Receive keystrokes and decide what to do 
 */
void brain(void *pvParameters) {

    // initialize local variables like layer or buffer

    // while 1
        // check buffer for new keystrokes
        // decide what to do with new keystrokes
        // sleep

}

// divide between internal and external?
void communication(void *pvParameters) {

    // Initialize communication

    // while 1
        // receive data
        // send data
}

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
    stdio_init_all();
    // Define tasks
    xTaskCreate(toggle_led, "led", 250, NULL, 1, NULL); 
    xTaskCreate(keystrokes_task, "keystrokes", 550, NULL, 1, NULL);
	// Run scheduler    
    vTaskStartScheduler();

	while(1) {}
}
