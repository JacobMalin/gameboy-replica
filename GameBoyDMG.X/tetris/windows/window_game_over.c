/* 
 * File:   window_game_over.c
 * Author: Jacob Malin
 *
 * Created on November 24, 2024, 6:19 AM
 */

#include "window_game_over.h"

static bool is_transition;
static uint16_t transition_clock;

void Window_Game_Over_init(void) {}

void Window_Game_Over(window_t *this) {
    is_transition = true;
    transition_clock = 0;
    
    this->button_handler = &Window_Game_Over_button_handle;
    this->render_handler = &Window_Game_Over_render_handle;
}

void Window_Game_Over_button_handle(window_t **this, buttons_cmd button) {
    if (button.edge != KEY_DOWN) return;
    
    if (!is_transition) {
        switch (button.button) {
            case BTN_A:
            case BTN_START:
                Window_set(*this, &Window_A_Type_Select);
                break;
            default:
                break;
        }
    }
}
 
void Window_Game_Over_render_handle(window_t *this) {
    uint16_t transition_time = TRANSITION_SPEED * DISPLAY_ROWS;
    
    // Blocks up write
    if (transition_clock < transition_time) {
        if (transition_clock % TRANSITION_SPEED == 0) {
            uint8_t i = DISPLAY_ROWS - transition_clock / TRANSITION_SPEED - 1;
            for (uint8_t j = 0; j < BOARD_COLS; j++) {
                Display_write_cell(this->Display, i, j + BOARD_OFFSET, TSN);
            }
        }
        transition_clock++;
    } 
    
    // Wait before game over text
    else if (transition_clock < transition_time + TRANSITION_WAIT) {
        transition_clock++;
    }
    
    // Game over write
    else if (transition_clock < 2 * transition_time + TRANSITION_WAIT) {
        uint16_t transition_clock_2 = transition_clock - transition_time - 
                TRANSITION_WAIT;
        if (transition_clock_2 % TRANSITION_SPEED == 0) {
            uint8_t i = DISPLAY_ROWS - transition_clock_2 / TRANSITION_SPEED - 1;
            
            // Grab row from memory
            const cell_e *screen = Screen_get(this->SD, SCREEN_GAME_OVER);
            for (uint8_t j = 0; j < BOARD_COLS; j++) {
                cell_e cell = screen[i * DISPLAY_COLS + BOARD_OFFSET + j];
                Display_write_cell(this->Display, i, j + BOARD_OFFSET, cell);
            }
        }
        transition_clock++;
    }
    
    // Transition is complete, no more animation
    else if (is_transition) {
        is_transition = false;
    }
}