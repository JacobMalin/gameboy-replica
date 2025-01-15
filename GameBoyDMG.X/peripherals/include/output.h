/*
 * File:   output.h
 * Author: Jacob Malin
 *
 * Created on October 12, 2024, 6:06 PM
 */

#ifndef OUTPUT_H
#define	OUTPUT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/io.h>
    
#include "FreeRTOS.h"

    typedef struct {
        register8_t *OUTSET;
        register8_t *OUTCLR;
        register8_t *OUTTGL;
        uint8_t PIN_bm;
    } output_t;

    /**
     * Initializes an output pin.
     * @param PORT_t *port The port register.
     * @param uint8_t pin The pin number.
     * @return Returns an output_t pointer.
     */
    output_t *Output(PORT_t *port, uint8_t pin);

    /**
     * Sets the output bit to 1.
     * @param output_t *this A pointer to the output object.
     */
    void Output_SET(output_t * this);

    /**
     * Sets the output bit to 0.
     * @param output_t *this A pointer to the output object.
     */
    void Output_CLR(output_t * this);

    /**
     * Toggles the output bit.
     * @param output_t *this A pointer to the output object.
     */
    void Output_TGL(output_t * this);

#ifdef	__cplusplus
}
#endif

#endif	/* OUTPUT_H */
