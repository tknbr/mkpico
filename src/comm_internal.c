#include "FreeRTOS.h" 
#include "task.h" 
#include "queue.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "stdio.h"
#include "task_internal.h"
#include "comm_internal.h"
#include "compile.h"
#include "led.h"

extern QueueHandle_t keystroke_queue;
extern QueueHandle_t comm_internal_queue;


#if defined(COMM_INTERNAL_I2C_PERIPHERAL)

keystroke_t keystroke;
bool start;

void i2c1_irq_handler() {
	volatile i2c_hw_t *i2c_hw = i2c_get_hw(COMM_INTERNAL_I2C_PORT);
    
    // Handle RX_FULL event (I2C_SLAVE_RECEIVE)
    if (i2c_hw->intr_stat & I2C_IC_INTR_STAT_R_RX_FULL_BITS) {

		unsigned char data = i2c_hw->data_cmd;
		
		if (!start && data == 0x42)
		{
			start = true;
		} else if (start && keystroke.col == 0xff)
		{
			keystroke.col = data;
		} else if (start && keystroke.col != 0xff)
		{
			keystroke.row = data;
			xQueueSendFromISR(keystroke_queue, &keystroke, 0);
			keystroke.col = 0xff;
			keystroke.row = 0xff;
			start = false;

			//led_blink();
		} else {
			keystroke.col = 0xff;
			keystroke.row = 0xff;
			start = false;
		}

		// Clear RX_FULL interrupt
        i2c_hw->clr_rx_done;
		
    }

	// Handle STOP_DET event (I2C_SLAVE_FINISH)
    if (i2c_hw->intr_stat & I2C_IC_INTR_STAT_R_STOP_DET_BITS) {
        keystroke.col = 0xff;
        keystroke.row = 0xff;
		start = false;
        i2c_hw->clr_stop_det;
    }
    
    // Clear other interrupt statuses
    i2c_hw->clr_rx_under;
    i2c_hw->clr_rx_over;
    i2c_hw->clr_tx_over;
    i2c_hw->clr_rd_req;
    i2c_hw->clr_tx_abrt;
    i2c_hw->clr_start_det;
    i2c_hw->clr_gen_call;
    
}


void comm_internal_peripheral_init()
{

	i2c_init(COMM_INTERNAL_I2C_PORT, COMM_INTERNAL_I2C_BAUDRATE);

	gpio_init(COMM_INTERNAL_I2C_SDA_GPIO);
	gpio_set_function(COMM_INTERNAL_I2C_SDA_GPIO, GPIO_FUNC_I2C);
	gpio_pull_up(COMM_INTERNAL_I2C_SDA_GPIO);

	gpio_init(COMM_INTERNAL_I2C_SCL_GPIO);
	gpio_set_function(COMM_INTERNAL_I2C_SCL_GPIO, GPIO_FUNC_I2C);
	gpio_pull_up(COMM_INTERNAL_I2C_SCL_GPIO);

	// Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(COMM_INTERNAL_I2C_SDA_GPIO, COMM_INTERNAL_I2C_SCL_GPIO, GPIO_FUNC_I2C));


	i2c_set_slave_mode(COMM_INTERNAL_I2C_PORT, true, COMM_INTERNAL_I2C_SLAVE_ADDR);
    irq_set_exclusive_handler(I2C1_IRQ, i2c1_irq_handler);
    irq_set_enabled(I2C1_IRQ, true);

    // enable i2c irq in the i2c hw
	volatile i2c_hw_t *hw = i2c_get_hw(COMM_INTERNAL_I2C_PORT);
	hw->intr_mask = (I2C_IC_INTR_MASK_M_RD_REQ_BITS | I2C_IC_INTR_MASK_M_RX_FULL_BITS);;
	hw->clr_intr;
	hw->enable = 1;

	keystroke.col = 0xff;
	keystroke.row = 0xff;

	start = false;
}
#endif // COMM_INTERNAL_I2C_PERIPHERAL


#if defined(COMM_INTERNAL_I2C_CONTROLLER)

void comm_internal_controller_send(keystroke_t *keystroke)
{
	const unsigned char col = keystroke->col;
	const unsigned char row = keystroke->row;
	const unsigned char start = 0x42;

	i2c_write_timeout_us(COMM_INTERNAL_I2C_PORT,
						COMM_INTERNAL_I2C_SLAVE_ADDR,
						&start,
						1,
						false,
						COMM_INTERNAL_WRITE_TIMEOUT);

	sleep_us(500);

	i2c_write_timeout_us(COMM_INTERNAL_I2C_PORT,
						COMM_INTERNAL_I2C_SLAVE_ADDR,
						&col,
						1,
						false,
						COMM_INTERNAL_WRITE_TIMEOUT);

	sleep_us(500);

	i2c_write_timeout_us(COMM_INTERNAL_I2C_PORT,
						COMM_INTERNAL_I2C_SLAVE_ADDR,
						&row,
						1,
						false,
						COMM_INTERNAL_WRITE_TIMEOUT);
	//led_blink();
}

void comm_internal_controller_init()
{
	
	i2c_init(COMM_INTERNAL_I2C_PORT, COMM_INTERNAL_I2C_BAUDRATE);

	gpio_init(COMM_INTERNAL_I2C_SDA_GPIO);
	gpio_set_function(COMM_INTERNAL_I2C_SDA_GPIO, GPIO_FUNC_I2C);
	gpio_pull_up(COMM_INTERNAL_I2C_SDA_GPIO);

	gpio_init(COMM_INTERNAL_I2C_SCL_GPIO);
	gpio_set_function(COMM_INTERNAL_I2C_SCL_GPIO, GPIO_FUNC_I2C);
	gpio_pull_up(COMM_INTERNAL_I2C_SCL_GPIO);

	// Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(COMM_INTERNAL_I2C_SDA_GPIO, COMM_INTERNAL_I2C_SCL_GPIO, GPIO_FUNC_I2C));

	//led_blink();
}

#endif // COMM_INTERNAL_I2C_CONTROLLER

void comm_internal_init()
{
#if defined(COMM_INTERNAL_I2C_CONTROLLER)
	comm_internal_controller_init();
#endif

#if defined (COMM_INTERNAL_I2C_PERIPHERAL)
	comm_internal_peripheral_init();
#endif
} 
