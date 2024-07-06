#include "FreeRTOS.h" 
#include "task.h" 
#include "queue.h"
#include "pico/stdlib.h"
#include "stdio.h"
#include "task_internal.h"
#include "comm_internal.h"

extern QueueHandle_t keystroke_queue;


#if defined(COMM_INTERNAL_I2C_ROLE_SLAVE)
void i2c_slave_handler()
{
	i2c_hw_t *hw = i2c_get_hw(I2C_PORT);

	// handle master read req
	if (hw->intr_stat & I2C_IC_INTR_STAT_R_RD_REQ_BITS)
	{
		// while transmit FIFO not full
		while (hw->status & I2C_IC_STATUS_TFNF_BITS)
		{
			// transmit keystroke
		}

		// clear the read req irq
		hw->clr_rd_req;
	}
}
#endif // COMM_INTERNAL_I2C_ROLE_SLAVE


void comm_internal_init(void)
{
	// Initialize i2c
	i2c_init(COMM_INTERNAL_I2C_PORT, COMM_INTERNAL_I2C_BAUDRATE);
	
	// set i2c pins
	gpio_set_function(COMM_INTERNAL_I2C_SDA_GPIO, GPIO_FUNC_I2C);
	gpio_set_function(COMM_INTERNAL_I2C_SCL_GPIO, GPIO_FUNC_I2C);
	gpio_pull_up(COMM_INTERNAL_I2C_SDA_GPIO);
	gpio_pull_up(COMM_INTERNAL_I2C_SCL_GPIO);

	#if defined(COMM_INTERNAL_I2C_ROLE_SLAVE)
	// set i2c slave address
	i2c_set_slave_mode(COMM_INTERNAL_I2C_PORT,
						true,
						COMM_INTERNAL_I2C_SLAVE_ADDR);

	// enable i2c irq
	irq_set_exclusive_handler(COMM_INTERNAL_I2C_IRQ,
								comm_internal_i2c_slave_hanlder);
 	irq_set_enabled(COMM_INTERNAL_I2C_IRQ, true);

	// enable i2c irq in the i2c hw
	i2c_hw_t *hw = i2c_get_hw(COMM_INTERNAL_I2C_PORT);
	hw->intr_mask = I2C_IC_INTR_STAT_R_RD_REQ_BITS | I2C_IC_INTR_STAT_R_RX_FULL_BITS;
	hw_enable = 1;
	#endif // COMM_INTERNAL_I2C_ROLE_SLAVE
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
