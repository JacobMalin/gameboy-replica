/* 
 * File:   spi.c
 * Author: Jacob Malin
 *
 * Created on November 1, 2024, 3:14 PM
 */

#include "spi.h"

spi_t *SPI(PORT_t *sdi_port, uint8_t sdi_pin,
        PORT_t *sdo_port, uint8_t sdo_pin,
        PORT_t *sck_port, uint8_t sck_pin) {
    static spi_t SPI;

    // For some reason SDI and SDO are swapped on the AVR-BLE
    SPI.SDI = Output(sdi_port, sdi_pin);
    SPI.SDO = Input(sdo_port, sdo_pin, false);
    SPI.SCK = Output(sck_port, sck_pin);
    
    SPI.blockSPI = xSemaphoreCreateMutex();

    // Do not disable host mode when client line is selected
    SPI0.CTRLB = SPI_SSD_bm;
    
    // SPI runs at 10MHz
    SPI0.CTRLA = SPI_CLK2X_bm    // Enable double-speed
            | SPI_ENABLE_bm      // Enable module
            | SPI_MASTER_bm      // SPI module in host mode
            | SPI_PRESC_DIV4_gc; // Prescale

    return &SPI;
}

void _SPI_write(uint8_t data) {
    SPI0.DATA = data;

    SPI_WAIT(); // Wait until data is sent
}

uint8_t _SPI_read(void) {
    SPI0.DATA = 0x00;

    SPI_WAIT(); // Wait until data is sent

    return SPI0.DATA;
}

uint8_t _SPI_exchange(uint8_t data) {
    SPI0.DATA = data;

    SPI_WAIT(); // Wait until data is sent

    return SPI0.DATA;
}

void SPI_slow(void) {
    SPI0.CTRLA = SPI_CLK2X_bm /* Enable double-speed */
            | SPI_ENABLE_bm /* Enable module */
            | SPI_MASTER_bm /* SPI module in Master mode */
            | SPI_PRESC_DIV64_gc; /* Prescale */
}

void SPI_fast(void) {
    SPI0.CTRLA = SPI_CLK2X_bm /* Enable double-speed */
            | SPI_ENABLE_bm /* Enable module */
            | SPI_MASTER_bm /* SPI module in Master mode */
            | SPI_PRESC_DIV4_gc; /* Prescale */
}