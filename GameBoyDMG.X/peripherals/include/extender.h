/* 
 * File:   extender.h
 * Author: Jacob Malin
 *
 * Created on November 16, 2024, 8:27 PM
 */

#ifndef EXTENDER_H
#define	EXTENDER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "spi_client.h"
    
#define EXTENDER_IODIR_ADDR 0x00 // In/out designation
#define EXTENDER_GPPU_ADDR 0x06  // Control register
#define EXTENDER_GPIO_ADDR 0x09  // IN register

    typedef struct {
        spi_client_t *SPI_Client;
        uint8_t addr;
        register8_t IN;
        register8_t IODIR;
        register8_t GPPU;
    } extender_t;

    /**
     * Initializes a GPIO extender.
     * @param spi_t *SPI An SPI object.
     * @param PORT_t *cs_port The CS port for SPI.
     * @param uint8_t cs_pin The CS pin for SPI.
     * @param uint8_t addr The address of the GPIO extender;
     * @return Returns a extender_t pointer.
     */
    extender_t *Extender(spi_t *SPI, PORT_t *cs_port, uint8_t cs_pin, 
        uint8_t addr);

    /**
     * Reads from the extender.
     * @param extender_t *this A pointer to the extender object.
     * @param uint8_t cmd The address of the register to read from.
     */
    uint8_t _Extender_read(extender_t * this, uint8_t cmd);

    /**
     * Writes to the extender.
     * @param extender_t *this A pointer to the extender object.
     * @param uint8_t cmd The address of the register to write to.
     * @param uint8_t data The data to write.
     */
    void _Extender_write(extender_t * this, uint8_t cmd, uint8_t data);

    /**
     * Sets a pin to input.
     * @param extender_t *this A pointer to the extender object.
     * @param uint8_t bit_map The bit map of the pin.
     */
    void Extender_set_input(extender_t * this, uint8_t bit_map);
    
    /**
     * Sets the pull up for the pin.
     * @param extender_t *this A pointer to the extender object.
     * @param uint8_t bit_map The bit map of the pin.
     */
    void Extender_pull_up(extender_t * this, uint8_t bit_map);
    
    /**
     * Updates the input.
     * @param extender_t *this A pointer to the extender object.
     */
    void Extender_poll(extender_t * this);

#ifdef	__cplusplus
}
#endif

#endif	/* EXTENDER_H */

