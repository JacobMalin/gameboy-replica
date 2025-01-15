/* 
 * File:   spi_client.h
 * Author: Jacob Malin
 *
 * Created on November 10, 2024, 6:45 PM
 */

#ifndef SPI_CLIENT_H
#define	SPI_CLIENT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/io.h>
    
#include "FreeRTOS.h"
#include "semphr.h"
    
#include "spi.h"
#include "output.h"

    typedef struct {
        spi_t *SPI;
        output_t *CS;
    } spi_client_t;

    /**
     * Initializes a client for spi.
     * @param spi_t *SPI An SPI object.
     * @param PORT_t *cs_port The port for CS.
     * @param uint8_t cs_pin The pin for CS.
     * @return Returns a spi_t pointer.
     */
    spi_client_t *SPI_Client(spi_t *SPI, PORT_t *cs_port, uint8_t cs_pin);

    /**
     * Takes the semaphore.
     * @param spi_t *this A pointer to the spi object.
     */
    void _SPI_Client_take_semaphore(spi_client_t * this);

    /**
     * Releases the semaphore.
     * @param spi_t *this A pointer to the spi object.
     */
    void _SPI_Client_give_semaphore(spi_client_t * this);

    /**
     * Pulls the CS pin low.
     * @param spi_t *this A pointer to the spi object.
     */
    void _SPI_Client_select(spi_client_t * this);

    /**
     * Releases the CS pin (to high).
     * @param spi_t *this A pointer to the spi object.
     */
    void _SPI_Client_deselect(spi_client_t * this);

    /**
     * Pulls the CS pin low and does not reserve the semaphore.
     * @param spi_t *this A pointer to the spi object.
     */
    void _SPI_Client_select_no_semaphore(spi_client_t * this);

    /**
     * Releases the CS pin and does not release the semaphore.
     * @param spi_t *this A pointer to the spi object.
     */
    void _SPI_Client_deselect_no_semaphore(spi_client_t * this);

    /**
     * Sends one byte of data to the client.
     * @param spi_t *this A pointer to the spi client object.
     * @param uint8_t data The data to send.
     */
    void SPI_Client_send_byte(spi_client_t * this, uint8_t data);

    /**
     * Sends multiple bytes of data to the client.
     * @param spi_t *this A pointer to the spi client object.
     * @param uint8_t data[] A list of bytes to send.
     * @param uint8_t len The length of the data list.
     */
    void SPI_Client_send_bytes(spi_client_t * this, uint8_t data[], uint8_t len);

    /**
     * Reads one byte of data from the client.
     * @param spi_t *this A pointer to the spi client object.
     * @return The byte of data that was read.
     */
    uint8_t SPI_Client_read_byte(spi_client_t * this);

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_CLIENT_H */

