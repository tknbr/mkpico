
#include "led.h"

#define GPIO_OUT 1

bool led_initialized = false;

void led_init(void)
{
    // init gpio
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    led_queue = xQueueCreate(10, sizeof(bool));
    led_initialized = true;
}

void led_blink(void)
{
    if (led_initialized)
    {
        bool test = 1;
	    xQueueSend(led_queue, &test, 0);
    }
}

void led_check(void)
{
    bool toggle;
    if (pdTRUE == xQueueReceive(led_queue, &toggle, 0))
    {
        // turn on
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        // wait
        vTaskDelay(25);
        // turn off
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
    }
}

void led_task(void *pvParameters)
{
    led_init();
    
    // endless loop
    while (1) { 
        led_check();
        vTaskDelay(TASK_DELAY_DEF);
    }
}