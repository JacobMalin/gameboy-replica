/* 
 * File:   ext_input.c
 * Author: Jacob Malin
 *
 * Created on November 16, 2024, 9:52 PM
 */

#include "ext_input.h"

input_t *Ext_Input(extender_t *extender, const uint8_t pin, 
            const bool do_pull_up) {
    input_t *Input = pvPortMalloc(sizeof(input_t));
    
    // Save values
    uint8_t bit_map = 0x1 << pin;

    // Set port direction to 0
    Extender_set_input(extender, bit_map);

    // Save bit map
    Input->PIN_bm = bit_map;
    
    // Save in register
    Input->IN = &extender->IN;

    // Find pin control
    if (do_pull_up) Extender_pull_up(extender, bit_map);

    return Input;
}
