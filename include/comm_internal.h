#include "hardware/i2c.h"
#include <stdint.h> // uint8_t

#define COMM_INTERNAL_I2C_PORT i2c1
#define COMM_INTERNAL_I2C_SDA_GPIO 2
#define COMM_INTERNAL_I2C_SCL_GPIO 3

#define COMM_INTERNAL_I2C_BAUDRATE 400000

#define COMM_INTERNAL_I2C_SLAVE_ADDR 41

#define COMM_INTERNAL_I2C_OP_REQ_N_KEYSTROKES 0x01
#define COMM_INTERNAL_I2C_OP_REQ_KEYSTROKES 0x02

typedef struct I2C_PACKET_HEADER_e {
	uint8_t operation;
	uint8_t len;
} I2C_PACKET_HEADER_t;

typedef struct I2C_PACKET_CRC_e {
	uint8_t crc;
} I2C_PACKET_CRC_t;

void comm_internal_task(void *pvParameters);
