/* 
 * File:   window_logo.c
 * Author: Jacob Malin
 *
 * Created on November 24, 2024, 6:19 AM
 */

#include "window_logo.h"

static uint16_t transition_clock;

void Window_Logo_init(void) {}

void Window_Logo(window_t *this) {
    transition_clock = 0;
    
    this->button_handler = &Window_Logo_button_handle;
    this->render_handler = &Window_Logo_render_handle;
    
    Window_Logo_initial_render(this);
}

void Window_Logo_initial_render(window_t *this) {    
    for (uint8_t i = 0; i < DISPLAY_ROWS; i++) {
        // Grab row from memory
        display_row row;
        for (uint8_t j = 0; j < DISPLAY_COLS; j++) {
            row[j] = WH_;
        }
        
        Display_display_row(this->Display, row, i);
    }
}

void Window_Logo_button_handle(window_t **this, buttons_cmd button) {
    if (button.edge != KEY_DOWN) return;
    
    Window_set(*this, &Window_Copyright); // Press down any key
}
 
void Window_Logo_render_handle(window_t *this) {
    // Initial wait before scrolling
    if (transition_clock < LOGO_WAIT_BEFORE) transition_clock++;
    
    // Vertical scroll
    else if (transition_clock < LOGO_WAIT_BEFORE + LOGO_TRANSITION_WAIT) {
        uint16_t scroll_clock = transition_clock - LOGO_WAIT_BEFORE;
        const cell_e *screen = Screen_get(this->SD, SCREEN_LOGO);
        
        uint8_t logo_step = scroll_clock / LOGO_STEP_TIME;
        uint8_t logo_mid_step = scroll_clock % LOGO_STEP_TIME;
        
        // Write cells of logo at an offset based on the transition_clock
        for (uint8_t i = 0; i < LOGO_ROWS; i++) {
            for (uint8_t j = 0; j < LOGO_COLS; j++) {
                uint8_t x = j + LOGO_OFFSET_X;
                uint8_t y = i + LOGO_OFFSET_Y;
                cell_e cell = screen[y * DISPLAY_COLS + x];
                int8_t display_y = y - LOGO_TOTAL_STEPS + logo_step;
                Display_write_cell_shift(this->Display, display_y, 
                            logo_mid_step + 1, x, cell);
            }
        }
        
        transition_clock += 2; // Skip every other pixel
    }
    
    // After wait
    else if (transition_clock < LOGO_WAIT_BEFORE + LOGO_TRANSITION_WAIT + 
            LOGO_WAIT_AFTER) {
        transition_clock++;
    }
    
    // Next window
    else Window_set(this, &Window_Copyright);
}