/* 
 * File:   sd.c
 * Author: Jacob Malin
 *
 * Created on 2024/12/01, 15:12
 */

#include "sd.h"

#include "screen.h"

sd_t *SD(spi_t *SPI, PORT_t *cs_port, uint8_t cs_pin) {
    static sd_t SD;

    SD.SPI_Client = SPI_Client(SPI, cs_port, cs_pin);

    SPI_slow();
    _SD_setup(&SD);
    SPI_fast();

    return &SD;
}

void _SD_setup(sd_t *this) {
    uint8_t res[5], cmdAttempts;

    SD_power_up_seq(this);

    // Command card to idle
    cmdAttempts = 0;
    while ((res[0] = SD_go_idle_state(this)) != 0x01) {
        cmdAttempts++;
        if (cmdAttempts > 10) {
            return;
        }
    }

    // Send interface conditions
    SD_send_if_cond(this, res);
    if (res[0] != 0x01) {
        return;
    }

    // Check echo pattern
    if (res[4] != 0xAA) {
        return;
    }

    // Attempt to initialize card
    cmdAttempts = 0;
    do {
        if (cmdAttempts > 100) {
            return;
        }

        // Send app cmd
        res[0] = SD_send_app(this);

        // If no error in response
        if (res[0] < 2) {
            res[0] = SD_send_op_cond(this);
        } else {
        }

        // Wait
        _delay_ms(10);

        cmdAttempts++;
    } while (res[0] != SD_READY);
}

void SD_send_command(uint8_t cmd, uint32_t arg, uint8_t crc) {
    // Transmit command to sd card
    _SPI_write(cmd | 0x40);

    // Transmit argument
    _SPI_write((uint8_t) (arg >> 24));
    _SPI_write((uint8_t) (arg >> 16));
    _SPI_write((uint8_t) (arg >> 8));
    _SPI_write((uint8_t) (arg));

    // Transmit crc
    _SPI_write(crc | 0x01);
}

uint8_t SD_read_res1(void) {
    uint8_t i = 0, res1;

    // Keep polling until actual data received
    while ((res1 = _SPI_exchange(0xFF)) == 0xFF) {
        i++;

        // If no data received for 8 bytes, break
        if (i > 8) break;
    }

    return res1;
}

void SD_read_res7(uint8_t *res) {
    // read response 1 in R7
    res[0] = SD_read_res1();

    // if error reading R1, return
    if(res[0] > 1) return;

    // read remaining bytes
    res[1] = _SPI_exchange(0xFF);
    res[2] = _SPI_exchange(0xFF);
    res[3] = _SPI_exchange(0xFF);
    res[4] = _SPI_exchange(0xFF);
}

void SD_power_up_seq(sd_t *this) {
    // Take semaphore
    _SPI_Client_take_semaphore(this->SPI_Client);

    // Give SD card time to power up
    _delay_ms(1);

    // Send 80 clock cycles to synchronize
    for (uint8_t i = 0; i < 10; i++) _SPI_write(0xFF);

    // Return semaphore
    _SPI_write(0xFF);
    _SPI_Client_give_semaphore(this->SPI_Client);
}

uint8_t SD_go_idle_state(sd_t *this) {
    // Set chip select
    _SPI_Client_take_semaphore(this->SPI_Client);
    _SPI_write(0xFF);
    _SPI_Client_select_no_semaphore(this->SPI_Client);
    _SPI_write(0xFF);

    // Send CMD0
    SD_send_command(CMD0, CMD0_ARG, CMD0_CRC);

    // Read response
    uint8_t res1 = SD_read_res1();

    // Unset chip select
    _SPI_write(0xFF);
    _SPI_Client_deselect_no_semaphore(this->SPI_Client);
    _SPI_write(0xFF);
    _SPI_Client_give_semaphore(this->SPI_Client);

    return res1;
}

void SD_send_if_cond(sd_t *this, uint8_t *res) {
    // Set chip select
    _SPI_Client_take_semaphore(this->SPI_Client);
    _SPI_write(0xFF);
    _SPI_Client_select_no_semaphore(this->SPI_Client);
    _SPI_write(0xFF);

    // send CMD8
    SD_send_command(CMD8, CMD8_ARG, CMD8_CRC);

    // read response
    SD_read_res7(res);

    // Unset chip select
    _SPI_write(0xFF);
    _SPI_Client_deselect_no_semaphore(this->SPI_Client);
    _SPI_write(0xFF);
    _SPI_Client_give_semaphore(this->SPI_Client);
}

uint8_t SD_send_app(sd_t *this) {
    // Set chip select
    _SPI_Client_take_semaphore(this->SPI_Client);
    _SPI_write(0xFF);
    _SPI_Client_select_no_semaphore(this->SPI_Client);
    _SPI_write(0xFF);

    // Send CMD0
    SD_send_command(CMD55, CMD55_ARG, CMD55_CRC);

    // Read response
    uint8_t res1 = SD_read_res1();

    // Unset chip select
    _SPI_write(0xFF);
    _SPI_Client_deselect_no_semaphore(this->SPI_Client);
    _SPI_write(0xFF);
    _SPI_Client_give_semaphore(this->SPI_Client);

    return res1;
}

uint8_t SD_send_op_cond(sd_t *this) {
    // Set chip select
    _SPI_Client_take_semaphore(this->SPI_Client);
    _SPI_write(0xFF);
    _SPI_Client_select_no_semaphore(this->SPI_Client);
    _SPI_write(0xFF);

    // Send CMD0
    SD_send_command(ACMD41, ACMD41_ARG, ACMD41_CRC);

    // Read response
    uint8_t res1 = SD_read_res1();

    // Unset chip select
    _SPI_write(0xFF);
    _SPI_Client_deselect_no_semaphore(this->SPI_Client);
    _SPI_write(0xFF);
    _SPI_Client_give_semaphore(this->SPI_Client);

    return res1;
}

uint8_t SD_read_block(sd_t *this, uint32_t addr, uint8_t *buf,
        uint16_t buf_size) {
    uint8_t readAttempts = 0;
    
    uint8_t res = _SD_read_block(this, addr, buf, buf_size);
    while (SD_R1_ERROR(res) && readAttempts++ < SD_MAX_READ_BLOCK_ATTEMPTS) {
        SPI_slow();
        _SD_setup(this);
        SPI_fast();
        _delay_ms(100);
        res = _SD_read_block(this, addr, buf, buf_size);
    }
    
    return res;
}

uint8_t _SD_read_block(sd_t *this, uint32_t addr, uint8_t *buf,
        uint16_t buf_size) {
    uint8_t res1, read;
    uint16_t readAttempts;

    // Set chip select
    _SPI_Client_take_semaphore(this->SPI_Client);
    _SPI_write(0xFF);
    _SPI_Client_select_no_semaphore(this->SPI_Client);
    _SPI_write(0xFF);

    // send CMD17
    SD_send_command(CMD17, addr, CMD17_CRC);

    // Read R1
    res1 = SD_read_res1();

    // If response received from card
    if (res1 != 0xFF) {
        // Wait for a response token (timeout = 100ms)
        readAttempts = 0;
        while (++readAttempts != SD_MAX_READ_ATTEMPTS)
            if ((read = _SPI_exchange(0xFF)) != 0xFF) break;

        // If response token is 0xFE
        if (read == 0xFE) {
            // Read 512 byte block
            uint16_t i = 0;
            while (i < buf_size) {
                *buf++ = _SPI_exchange(0xFF);
                i++;
            }
            while (i < BLOCK_SIZE) {
                _SPI_write(0xFF);
                i++;
            }

            // Read 16-bit CRC
            _SPI_write(0xFF);
            _SPI_write(0xFF);
        }
    }

    // Unset chip select
    _SPI_write(0xFF);
    _SPI_Client_deselect_no_semaphore(this->SPI_Client);
    _SPI_write(0xFF);
    _SPI_Client_give_semaphore(this->SPI_Client);

    return res1;
}

uint8_t SD_write_block(sd_t *this, uint32_t addr, uint8_t *buf,
        uint16_t buf_size) {
    uint8_t readAttempts, read, res;

    // Set chip select
    _SPI_Client_take_semaphore(this->SPI_Client);
    _SPI_write(0xFF);
    _SPI_Client_select_no_semaphore(this->SPI_Client);
    _SPI_write(0xFF);

    // Send CMD24
    SD_send_command(CMD24, addr, CMD24_CRC);

    // Read response
    res = SD_read_res1();

    // If no error
    if (res == SD_READY) {
        // Send start token
        _SPI_write(SD_START_TOKEN);

        // Write buffer to card
        uint16_t i = 0;
        while (i < buf_size) {
            _SPI_write(buf[i]);
            i++;
        }
        while (i < BLOCK_SIZE) {
            _SPI_write(0x00);
            i++;
        }

        // Wait for a response (timeout = 250ms)
        readAttempts = 0;
        while (++readAttempts != SD_MAX_WRITE_ATTEMPTS) {
            if ((read = _SPI_exchange(0xFF)) != 0xFF) break;
        }

        // If data accepted
        if ((read & 0x1F) == 0x05) {
            // Wait for write to finish (timeout = 250ms)
            readAttempts = 0;
            while (_SPI_exchange(0xFF) == 0x00) {
                if (++readAttempts == SD_MAX_WRITE_ATTEMPTS) break;
            }
        }
    }

    // Unset chip select
    _SPI_write(0xFF);
    _SPI_Client_deselect_no_semaphore(this->SPI_Client);
    _SPI_write(0xFF);
    _SPI_Client_give_semaphore(this->SPI_Client);

    return res;
}