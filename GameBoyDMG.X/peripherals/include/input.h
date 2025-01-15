/* 
 * File:   input.h
 * Author: Jacob Malin
 *
 * Created on October 12, 2024, 6:40 PM
 */

#ifndef INPUT_H
#define	INPUT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <avr/io.h>
    
#include "FreeRTOS.h"

    typedef struct {
        register8_t *IN;
        uint8_t PIN_bm;
    } input_t;


    /**
     * Initializes an input pin.
     * @param PORT_t *port The port register.
     * @param uint8_t pin The pin number.
     * @param bool do_pull_up If the pull up resistor should be enabled.
     * @return Returns an input_t pointer.
     */
    input_t *Input(PORT_t *port, const uint8_t pin, const bool do_pull_up);

#ifdef	__cplusplus
}
#endif

#endif	/* INPUT_H */

