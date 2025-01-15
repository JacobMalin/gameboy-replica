/* 
 * File:   extender.c
 * Author: Jacob Malin
 *
 * Created on November 16, 2024, 8:27 PM
 */

#include "extender.h"

extender_t *Extender(spi_t *SPI, PORT_t *cs_port, uint8_t cs_pin, 
        uint8_t addr) {
    static extender_t Extender;

    Extender.SPI_Client = SPI_Client(SPI, cs_port, cs_pin);
    Extender.addr = addr;
    
    Extender.IN = 0x00;
    Extender.IODIR = 0x00;
    Extender.GPPU = 0x00;

    return &Extender;
}

uint8_t _Extender_read(extender_t * this, uint8_t cmd) {
    _SPI_Client_select(this->SPI_Client);
    
    uint8_t control_byte = (this->addr << 1) + 0x1; // Read
    uint8_t result;
    _SPI_exchange(control_byte);
    _SPI_exchange(cmd);
    result = _SPI_exchange(0x00);
    
    _SPI_Client_deselect(this->SPI_Client);
    
    return result;
}

void _Extender_write(extender_t * this, uint8_t cmd, uint8_t data) {
    _SPI_Client_select(this->SPI_Client);
    
    uint8_t control_byte = (this->addr << 1) + 0x0; // Write
    _SPI_write(control_byte);
    _SPI_write(cmd);
    _SPI_write(data);
    
    _SPI_Client_deselect(this->SPI_Client);
}

void Extender_set_input(extender_t * this, uint8_t bit_map) {
    this->IODIR |= bit_map;
    
    _Extender_write(this, EXTENDER_IODIR_ADDR, this->IODIR);
}

void Extender_pull_up(extender_t * this, uint8_t bit_map) {
    this->GPPU |= bit_map;
    
    _Extender_write(this, EXTENDER_GPPU_ADDR, this->GPPU);
}

void Extender_poll(extender_t * this) {
    this->IN = _Extender_read(this, EXTENDER_GPIO_ADDR);
}