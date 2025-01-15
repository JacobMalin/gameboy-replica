/*
 * File:   output.c
 * Author: Jacob Malin
 *
 * Created on October 12, 2024, 6:06 PM
 */

#include "output.h"

output_t *Output(PORT_t *port, uint8_t pin) {
    output_t *Output = pvPortMalloc(sizeof(output_t));

    // Save values
    uint8_t bit_map = 0x1 << pin;

    // Set port direction to 1 (output)
    port->DIRSET = bit_map;

    // Save output register and bit map
    Output->OUTSET = &port->OUTSET;
    Output->OUTCLR = &port->OUTCLR;
    Output->OUTTGL = &port->OUTTGL;
    Output->PIN_bm = bit_map;

    // Disable output
    Output_CLR(Output);

    return Output;
}

void Output_SET(output_t *this) {
    *this->OUTSET = this->PIN_bm;
}

void Output_CLR(output_t *this) {
    *this->OUTCLR = this->PIN_bm;
}

void Output_TGL(output_t *this) {
    *this->OUTTGL = this->PIN_bm;
}