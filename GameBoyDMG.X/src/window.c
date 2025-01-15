/* 
 * File:   window.c
 * Author: Jacob Malin
 *
 * Created on November 19, 2024, 1:44 PM
 */

#include "window.h"

window_t *Window(sd_t *SD, display_t *Display) {
    static window_t Window;
    
    Window.SD = SD;
    Window.Display = Display;
    
    Window.is_blink_black = false;
    Window.blink_count = 0;
    
    // Load screens and cells into SD memory.
    Screen(SD);
    
    // Init windows
    Window_Logo_init();
    Window_Copyright_init();
    Window_Title_init();
    Window_Select_init();
    Window_A_Type_Select_init();
    Window_A_Type_Game_init();
    Window_Game_Over_init();
    
    return &Window;
}

void Window_set(window_t *this, window_change_t *change) {
    change(this);
}

void Window_handle_button(window_t **this, buttons_cmd button) {
    (*this)->button_handler(this, button);
}

void Window_render(window_t *this) {
    if (++this->blink_count >= BLINK_RATE) {
        this->blink_count = 0; // Reset blink count
        // Swap from black to gray or vice versa
        this->is_blink_black = !this->is_blink_black;
    }
    
    this->render_handler(this);
}

void _Window_replace_range(display_row row, uint8_t start_col,
        uint8_t num_cells, const cell_e copy[]) {
    for (uint8_t j = 0; j < num_cells; j++) {
        row[start_col + j] = copy[j];
    }
}

void _Window_write_range(window_t *this, uint8_t row_num, 
        uint8_t start_col, uint8_t num_cells, const cell_e copy[]) {
    for (uint8_t j = 0; j < num_cells; j++) {
        Display_write_cell(this->Display, row_num, start_col + j, copy[j]);
    }
}