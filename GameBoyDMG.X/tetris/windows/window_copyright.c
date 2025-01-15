/* 
 * File:   window_copyright.c
 * Author: Jacob Malin
 *
 * Created on November 24, 2024, 6:19 AM
 */

#include "window_copyright.h"

static uint16_t transition_clock;

void Window_Copyright_init(void) {}

void Window_Copyright(window_t *this) {
    transition_clock = 0;
    
    this->button_handler = &Window_Copyright_button_handle;
    this->render_handler = &Window_Copyright_render_handle;
    
    Window_Copyright_initial_render(this);
}

void Window_Copyright_initial_render(window_t *this) {
    const cell_e *screen = Screen_get(this->SD, SCREEN_COPYRIGHT);
    
    for (uint8_t i = 0; i < DISPLAY_ROWS; i++) {
        // Grab row from memory
        display_row row;
        for (uint8_t j = 0; j < DISPLAY_COLS; j++) {
            row[j] = screen[i * DISPLAY_COLS + j];
        }
        
        Display_display_row(this->Display, row, i);
    }
}

void Window_Copyright_button_handle(window_t **this, buttons_cmd button) {
    if (button.edge != KEY_DOWN) return;
    
    Window_set(*this, &Window_Title); // Press down any key
}
 
void Window_Copyright_render_handle(window_t *this) {
    if (transition_clock >= COPYRIGHT_TRANSITION_WAIT) {
        Window_set(this, &Window_Title);
    }
    transition_clock++;
}