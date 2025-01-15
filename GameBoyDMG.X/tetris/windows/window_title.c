/* 
 * File:   window_title.c
 * Author: Jacob Malin
 *
 * Created on November 19, 2024, 2:08 PM
 */

#include "window_title.h"

static window_title_t data;
static window_title_t old;

void Window_Title_init(void) {
    data.is_one_player = true;
    
    old.is_one_player = true;
}

void Window_Title(window_t *this) {
    this->button_handler = &Window_Title_button_handle;
    this->render_handler = &Window_Title_render_handle;
    
    Window_Title_initial_render(this);
}

void Window_Title_initial_render(window_t *this) {
    const cell_e *screen = Screen_get(this->SD, SCREEN_TITLE);
    
    for (uint8_t i = 0; i < DISPLAY_ROWS; i++) {
        // Grab row from memory
        display_row row;
        for (uint8_t j = 0; j < DISPLAY_COLS; j++) {
            row[j] = screen[i * DISPLAY_COLS + j];
        }
        
        // Modify row
        // Writes play symbol to appropriate player count
        if (i == TITLE_PLAY_ROW) {
            if (data.is_one_player) row[TITLE_PLAY_ONE_PLAYER_COL] = PLY;
            else row[TITLE_PLAY_TWO_PLAYER_COL] = PLY;
        }
        
        // Render row
        Display_display_row(this->Display, row, i);
    }
}

void Window_Title_button_handle(window_t **this, buttons_cmd button) {    
    if (button.edge != KEY_DOWN) return;
    
    switch (button.button) {
        case BTN_LEFT:   // One player game
            data.is_one_player = true;
            break;
        case BTN_RIGHT:  // Two player game
            data.is_one_player = false;
            break;
        case BTN_SELECT: // Swap player game
            data.is_one_player = !data.is_one_player;
            break;
        case BTN_START:  // Start game
            if (data.is_one_player) {
                Window_set(*this, &Window_Select);
            }
            
            // Two player game not implemented
            // else Window_set(*this, &Window_Two_Player_Select);
            break;
        default:
            break;
    }
}

void Window_Title_render_handle(window_t *this) {
    // If player count has changed, move play symbol
    if (data.is_one_player != old.is_one_player) {
        if (data.is_one_player) { // If one player
            Display_write_cell(this->Display, TITLE_PLAY_ROW, 
                    TITLE_PLAY_ONE_PLAYER_COL, PLY);
            Display_write_cell(this->Display, TITLE_PLAY_ROW, 
                    TITLE_PLAY_TWO_PLAYER_COL, WH_);
        } else { // If two players
            Display_write_cell(this->Display, TITLE_PLAY_ROW, 
                    TITLE_PLAY_ONE_PLAYER_COL, WH_);
            Display_write_cell(this->Display, TITLE_PLAY_ROW, 
                    TITLE_PLAY_TWO_PLAYER_COL, PLY);
        }
        
        old.is_one_player = data.is_one_player;
    }
}