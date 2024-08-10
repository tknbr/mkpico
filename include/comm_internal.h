#include "hardware/i2c.h"
#include "compile.h"
#include "keystrokes.h"
#include <stdint.h> // uint8_t

#if defined(ROLE_MASTER)
#  define COMM_INTERNAL_I2C_PERIPHERAL
#endif

#if defined(ROLE_SLAVE)
#  define COMM_INTERNAL_I2C_CONTROLLER
#endif

#define COMM_INTERNAL_I2C_BAUDRATE 100000

#define COMM_INTERNAL_I2C_PORT i2c1
#define COMM_INTERNAL_I2C_IRQ I2C1_IRQ
#define COMM_INTERNAL_I2C_SDA_GPIO 2
#define COMM_INTERNAL_I2C_SCL_GPIO 3

#define COMM_INTERNAL_I2C_SLAVE_ADDR 41

#define COMM_INTERNAL_WRITE_TIMEOUT 100

// Declare the bits in the registers we use
#define I2C_DATA_CMD_FIRST_BYTE 0x00000800
#define I2C_DATA_CMD_DATA       0x000000ff
#define I2C_INTR_STAT_READ_REQ  0x00000020
#define I2C_INTR_STAT_RX_FULL   0x00000004
#define I2C_INTR_MASK_READ_REQ  0x00000020
#define I2C_INTR_MASK_RX_FULL   0x00000004

QueueHandle_t comm_internal_queue;

typedef struct I2C_PACKET_HEADER_e {
    uint8_t operation;
    uint8_t len;
} I2C_PACKET_HEADER_t;

typedef struct I2C_PACKET_CRC_e {
    uint8_t crc;
} I2C_PACKET_CRC_t;


#if defined(COMM_INTERNAL_I2C_CONTROLLER)

void comm_internal_controller_send(keystroke_t *keystroke);

#endif // COMM_INTERNAL_I2C_CONTROLLER

void comm_internal_init();
