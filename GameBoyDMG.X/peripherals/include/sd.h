/* 
 * File:   sd.h
 * Author: Jacob Malin
 *
 * Created on 2024/12/01, 15:12
 * Most functions from http://www.rjhcoding.com/avrc-sd-interface-1.php
 */

#ifndef SD_H
#define	SD_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef F_CPU
#define F_CPU 20000000
#endif

#include <avr/io.h>
#include <util/delay.h>
    
#include "spi_client.h"
    
#define BLOCK_SIZE 512 // Bytes
#define FIRST_SCREEN_BLOCK 0x0
#define FIRST_CELL_BLOCK   0x100

#define CMD0        0
#define CMD0_ARG    0x00000000
#define CMD0_CRC    0x94
    
#define CMD8        8
#define CMD8_ARG    0x0000001AA
#define CMD8_CRC    0x86 //(1000011 << 1)

#define CMD17                      17
#define CMD17_CRC                  0x00
#define SD_MAX_READ_ATTEMPTS       3907*3
#define SD_MAX_READ_BLOCK_ATTEMPTS 5

#define CMD24                   24
#define CMD24_CRC               0x00
#define SD_MAX_WRITE_ATTEMPTS   3907

#define CMD55       55
#define CMD55_ARG   0x00000000
#define CMD55_CRC   0x00

#define ACMD41      41
#define ACMD41_ARG  0x40000000
#define ACMD41_CRC  0x00
    
#define SD_READY       0x00
#define SD_START_TOKEN 0xFE
    
#define SD_R1_ERROR(X)   X >= 0x02

    typedef struct {
        spi_client_t *SPI_Client;
    } sd_t;

    /**
     * Initializes an sd card.
     * @param spi_t *SPI An SPI object.
     * @param PORT_t *cs_port The CS port for SPI.
     * @param uint8_t cs_pin The CS pin for SPI.
     * @return Returns an sd_t pointer.
     */
    sd_t *SD(spi_t *SPI, PORT_t *cs_port, uint8_t cs_pin);

    /**
     * Initializes the card. Silently fails on failure.
     * @param sd_t *this A pointer to the sd object.
     */
    void _SD_setup(sd_t * this);

    /**
     * Sends a command to the card.
     * @param uint8_t cmd The command code.
     * @param uint32_t arg The arguments of the command.
     * @param uint8_t crc The cyclic redundancy check.
     */
    void SD_send_command(uint8_t cmd, uint32_t arg, uint8_t crc);

    /**
     * Reads the R1 result type.
     * @return The response.
     */
    uint8_t SD_read_res1(void);

    /**
     * Reads the R7 result type.
     * @param uint8_t *res The response.
     */
    void SD_read_res7(uint8_t *res);

    /**
     * Runs the power up sequence for the card.
     * @param sd_t *this A pointer to the sd object.
     */
    void SD_power_up_seq(sd_t * this);

    /**
     * Starts SPI mode on the card.
     * @param sd_t *this A pointer to the sd object.
     * @return The response.
     */
    uint8_t SD_go_idle_state(sd_t *this);

    /**
     * Sends interface conditions.
     * @param sd_t *this A pointer to the sd object.
     * @param uint8_t *res The response.
     */
    void SD_send_if_cond(sd_t *this, uint8_t *res);

    /**
     * Prepares for an application command.
     * @param sd_t *this A pointer to the sd object.
     * @return The response.
     */
    uint8_t SD_send_app(sd_t *this);

    /**
     * Starts the initialization.
     * @param sd_t *this A pointer to the sd object.
     * @return The response.
     */
    uint8_t SD_send_op_cond(sd_t *this);

    /**
     * Attempt to read a single 512 byte block up to 5 times.
     * @param sd_t *this A pointer to the sd object.
     * @param uint32_t addr The address to read.
     * @param uint8_t *buf The buffer to write to.
     * @param uint16_t buf_size The length of the buffer, data past this is
     * discarded.
     * @return The response.
     */
    uint8_t SD_read_block(sd_t *this, uint32_t addr, uint8_t *buf, 
            uint16_t buf_size);

    /**
     * Read single 512 byte block.
     * @param sd_t *this A pointer to the sd object.
     * @param uint32_t addr The address to read.
     * @param uint8_t *buf The buffer to write to.
     * @param uint16_t buf_size The length of the buffer, data past this is
     * discarded.
     * @return The response.
     */
    uint8_t _SD_read_block(sd_t *this, uint32_t addr, uint8_t *buf, 
            uint16_t buf_size);

    /**
     * Write single 512 byte block.
     * @param sd_t *this A pointer to the sd object.
     * @param uint32_t addr The address to write to.
     * @param uint8_t *buf The buffer to read from.
     * @param uint16_t buf_size The length of the buffer, data past this is
     * filled with 0s.
     * @return The response.
     */
    uint8_t SD_write_block(sd_t *this, uint32_t addr, uint8_t *buf, 
            uint16_t buf_size);

#ifdef	__cplusplus
}
#endif

#endif	/* SD_H */

