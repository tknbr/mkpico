#include "FreeRTOS.h" 
#include "task.h" 
#include "queue.h"
#include "pico/stdlib.h"
#include "stdio.h"
#include "task_internal.h"
#include "comm_internal.h"

extern QueueHandle_t keystroke_queue;

void comm_internal_init(void)
{
	i2c_init(COMM_INTERNAL_I2C_PORT, COMM_INTERNAL_I2C_BAUDRATE);
	gpio_set_function(COMM_INTERNAL_I2C_SDA_GPIO, GPIO_FUNC_I2C);
	gpio_set_function(COMM_INTERNAL_I2C_SCL_GPIO, GPIO_FUNC_I2C);
	gpio_pull_up(COMM_INTERNAL_I2C_SDA_GPIO);
	gpio_pull_up(COMM_INTERNAL_I2C_SCL_GPIO);
}

void comm_internal_receive(void)
{
	// Request keys pressed

	// If key pressed
		// request keystrokes (col and row)
		// add col and row to keystroke_queue;
}

void comm_internal_task(void *pvParameters)
{
	comm_internal_init();
	while(1)
	{
		comm_internal_receive();
		vTaskDelay(TASK_DELAY_DEF);
	}
} 
