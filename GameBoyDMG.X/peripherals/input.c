/*
 * File:   ext_input.c
 * Author: Jacob Malin
 *
 * Created on October 12, 2024, 6:29 PM
 */

#include "input.h"

input_t *Input(PORT_t *port, const uint8_t pin, const bool do_pull_up) {
    input_t *Input = pvPortMalloc(sizeof(input_t));
    
    // Save values
    uint8_t bit_map = 0x1 << pin;

    // Set port direction to 0 (input))
    port->DIRCLR = bit_map;

    // Save bit map
    Input->PIN_bm = bit_map;
    
    // Save in register
    Input->IN = &port->IN;

    // Set pull up
    register8_t *CTRL = &port->PIN0CTRL + pin; // This may not work on other boards
    if (do_pull_up) *CTRL |= PORT_PULLUPEN_bm;

    return Input;
}