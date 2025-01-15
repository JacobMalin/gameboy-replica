/* 
 * File:   spi_client.c
 * Author: Jacob Malin
 *
 * Created on November 10, 2024, 6:45 PM
 */

#include "spi_client.h"

spi_client_t *SPI_Client(spi_t *SPI, PORT_t *cs_port, uint8_t cs_pin) {
    spi_client_t *SPI_Client = pvPortMalloc(sizeof(spi_client_t));

    SPI_Client->SPI = SPI;
    SPI_Client->CS = Output(cs_port, cs_pin);
    
    _SPI_Client_deselect_no_semaphore(SPI_Client);

    return SPI_Client;
}

void _SPI_Client_take_semaphore(spi_client_t *this) {
    xSemaphoreTake(this->SPI->blockSPI, portMAX_DELAY);
    _SPI_write(0xFF);
}

void _SPI_Client_give_semaphore(spi_client_t *this) {
    _SPI_write(0xFF);
    xSemaphoreGive(this->SPI->blockSPI);
}

void _SPI_Client_select(spi_client_t *this) {
    _SPI_Client_take_semaphore(this);
    Output_CLR(this->CS); // Low is selected
}

void _SPI_Client_deselect(spi_client_t *this) {
    Output_SET(this->CS); // High is deselected
    _SPI_Client_give_semaphore(this);
}

void _SPI_Client_select_no_semaphore(spi_client_t *this) {
    Output_CLR(this->CS); // Low is selected
}

void _SPI_Client_deselect_no_semaphore(spi_client_t *this) {
    Output_SET(this->CS); // High is deselected
}

void SPI_Client_send_byte(spi_client_t *this, uint8_t data) {
    _SPI_Client_select(this);
    
    _SPI_write(data);
    
    _SPI_Client_deselect(this);
}

void SPI_Client_send_bytes(spi_client_t *this, uint8_t data[], uint8_t len) {
    _SPI_Client_select(this);
    
    for (uint8_t i = 0; i < len; i++) {
        _SPI_write(data[i]);
    }
    
    _SPI_Client_deselect(this);
}

uint8_t SPI_Client_read_byte(spi_client_t *this) {
    _SPI_Client_select(this);
    
    uint8_t data = _SPI_read();
    
    _SPI_Client_deselect(this);
    
    return data;
}