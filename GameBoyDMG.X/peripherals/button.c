/*
 * File:   button.c
 * Author: Jacob Malin
 *
 * Created on October 12, 2024, 6:04 PM
 */

#include "button.h"

button_t *Button(extender_t *extender, const uint8_t pin, const bool do_pull_up) {
    button_t *Button = pvPortMalloc(sizeof(button_t));

    // Save values
    Button->PORT = Ext_Input(extender, pin, do_pull_up);
    Button->state = true; // Buttons start up

    return Button;
}

bool _Button_is_high(button_t *this) {
    return (*this->PORT->IN & this->PORT->PIN_bm) > 0;
}

button_edge_t Button_get_edge(button_t *this) {
    bool button_state = _Button_is_high(this);
    button_edge_t ret_val = KEY_UNCHANGED;

    // If button pushed
    if (button_state != this->state) {
        ret_val = button_state ? KEY_UP : KEY_DOWN; // High is up
        this->state = button_state;
    }

    return ret_val;
}