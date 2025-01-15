/* 
 * File:   spi.h
 * Author: Jacob Malin
 *
 * Created on November 1, 2024, 3:14 PM
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/io.h>
    
#include "FreeRTOS.h"
#include "semphr.h"

#include "input.h"
#include "output.h"

#define SPI_WAIT() while (!(SPI0.INTFLAGS & SPI_IF_bm))

    typedef struct {
        output_t *SDI, *SCK;
        input_t *SDO;
        SemaphoreHandle_t blockSPI;
    } spi_t;

    /**
     * Initializes the spi object.
     * @param PORT_t *sdi_port The port for SDI.
     * @param uint8_t sdi_pin The pin for SDI.
     * @param PORT_t *sdo_port The port for SDO.
     * @param uint8_t sdo_pin The pin for SDO.
     * @param PORT_t *sck_port The port for SCK.
     * @param uint8_t sck_pin The pin for SCK.
     * @return Returns a spi_t pointer.
     */
    spi_t *SPI(PORT_t *sdi_port, uint8_t sdi_pin,
        PORT_t *sdo_port, uint8_t sdo_pin,
        PORT_t *sck_port, uint8_t sck_pin);
    
    /**
     * Writes one byte.
     * @param uint8_t data One byte of data to transmit.
     */
    void _SPI_write(uint8_t data);
    
    /**
     * Reads one byte.
     * @return The byte of data read.
     */
    uint8_t _SPI_read(void);
    
    /**
     * Reads and write one byte.
     * @param uint8_t data One byte of data to transmit.
     * @return The byte of data read.
     */
    uint8_t _SPI_exchange(uint8_t data);
    
    /**
     * Slows down SPI to 1/16 the speed.
     */
    void SPI_slow(void);
    
    /**
     * Returns SPI to original fast speed.
     */
    void SPI_fast(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

