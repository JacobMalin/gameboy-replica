/* 
 * File:   button.h
 * Author: Jacob Malin
 *
 * Created on October 12, 2024, 6:57 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <avr/io.h>

#include "ext_input.h"

    typedef enum {
        KEY_UNCHANGED,
        KEY_UP,
        KEY_DOWN,
    } button_edge_t;

    typedef struct {
        input_t *PORT;
        bool state : 1; // True if button is up
    } button_t;

    /**
     * Initializes a button.
     * @param extender_t *extender The GPIO extender.
     * @param uint8_t pin The pin number.
     * @param bool do_pull_up If the pull up resistor should be enabled.
     * @return Returns an button_t pointer.
     */
    button_t *Button(extender_t *extender, const uint8_t pin, 
            const bool do_pull_up);

    /**
     * Gets if the button is high or low.
     * @param button_t *this A pointer to the button object.
     * @return True if high, else false
     */
    bool _Button_is_high(button_t * this);


    /**
     * Returns the edge state of the button. This was adapted from the FreeRTOS
     * example.
     * @param button_t *this A pointer to the button object.
     * @return The edge state of the button.
     */
    button_edge_t Button_get_edge(button_t * this);

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_H */