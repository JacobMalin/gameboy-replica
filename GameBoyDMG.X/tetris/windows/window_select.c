/* 
 * File:   window_select.c
 * Author: Jacob Malin
 *
 * Created on November 24, 2024, 6:19 AM
 */

#include "window_select.h"

const cell_e BLACK_A_TYPE[] = {A__, DSH, T__, Y__, P__, E__};
const cell_e BLACK_B_TYPE[] = {B__, DSH, T__, Y__, P__, E__};
const cell_e BLACK_C_TYPE[] = {C__, DSH, T__, Y__, P__, E__};
const cell_e BLACK_OFF[]    = {WH_, O__, F__, F__, WH_, WH_};

const cell_e GRAY_A_TYPE[] = {A_G, DSG, T_G, Y_G, P_G, E_G};
const cell_e GRAY_B_TYPE[] = {B_G, DSG, T_G, Y_G, P_G, E_G};
const cell_e GRAY_C_TYPE[] = {C_G, DSG, T_G, Y_G, P_G, E_G};
const cell_e GRAY_OFF[]    = {WH_, O_G, F_G, F_G, WH_, WH_};

static window_select_t data;
static text_t old_is_black;

void Window_Select_init(void) {
    data.select_game = true; // Start at game selection
    data.is_a_type = true;
    data.music_type = MUSIC_A;
}

void Window_Select(window_t *this) {
    data.select_game = true; // Start at game selection
    
    // A-TYPE game and A-TYPE music start black
    old_is_black = 0x1 << TEXT_GAME_A | 0x1 << TEXT_MUSIC_A;
    
    this->button_handler = &Window_Select_button_handle;
    this->render_handler = &Window_Select_render_handle;
    
    // Set/start music not implemented
    
    Window_Select_initial_render(this);
}
 
void Window_Select_initial_render(window_t *this) {
    const cell_e *screen = Screen_get(this->SD, SCREEN_SELECT);
    
    for (uint8_t i = 0; i < DISPLAY_ROWS; i++) {
        // Grab row from memory
        display_row row;
        for (uint8_t j = 0; j < DISPLAY_COLS; j++) {
            row[j] = screen[i * DISPLAY_COLS + j];
        }
        
        // Modify row
        switch (i) {
            case SELECT_GAME_ROW:
                if (data.is_a_type) {
                    _Window_replace_range(row, SELECT_LEFT_COL, 
                            SELECT_BLACK_LEN, BLACK_A_TYPE);
                } else {
                    _Window_replace_range(row, SELECT_RIGHT_COL, 
                            SELECT_BLACK_LEN, BLACK_B_TYPE);
                }
                break;
            case SELECT_MUSIC_ROW_1:
                if (data.music_type == MUSIC_A) {
                    _Window_replace_range(row, SELECT_LEFT_COL, 
                            SELECT_BLACK_LEN, BLACK_A_TYPE);
                } else if (data.music_type == MUSIC_B) {
                    _Window_replace_range(row, SELECT_RIGHT_COL, 
                            SELECT_BLACK_LEN, BLACK_B_TYPE);
                }
                break;
            case SELECT_MUSIC_ROW_2:
                if (data.music_type == MUSIC_C) {
                    _Window_replace_range(row, SELECT_LEFT_COL, 
                            SELECT_BLACK_LEN, BLACK_C_TYPE);
                } else if (data.music_type == MUSIC_OFF) {
                    _Window_replace_range(row, SELECT_RIGHT_COL, 
                            SELECT_BLACK_LEN, BLACK_OFF);
                }
                break;
            default:
                break;
        }
        
        Display_display_row(this->Display, row, i);
    }
}

void Window_Select_button_handle(window_t **this, buttons_cmd button) {    
    if (button.edge != KEY_DOWN) return;
    
    if (data.select_game) { // Select game
        switch (button.button) {
            case BTN_LEFT:  // Choose A-TYPE game
                data.is_a_type = true;
                break;
            case BTN_RIGHT: // Choose B-TYPE game
                data.is_a_type = false;
                break;
            case BTN_A:     // Move to music selection
                if (data.is_a_type) data.select_game = false;
                
                // B-type game not implemented
                // data.select_game = false;
                break;
            case BTN_START: // Start game
                if (data.is_a_type) {
                    Window_set(*this, &Window_A_Type_Select);
                }

                // B-type game not implemented
                // else *this = Window_set(*this, &Window_B_Type_Select);
                break;
            default:
                break;
        }
    } else { // Select music
        switch (button.button) {
            case BTN_UP:   // Move up in music menu
                if (data.music_type == MUSIC_C)   data.music_type = MUSIC_A;
                if (data.music_type == MUSIC_OFF) data.music_type = MUSIC_B;
                break;
            case BTN_DOWN:  // Move down in music menu
                if (data.music_type == MUSIC_A) data.music_type = MUSIC_C;
                if (data.music_type == MUSIC_B) data.music_type = MUSIC_OFF;
                break;
            case BTN_LEFT:  // Move left in music menu
                if (data.music_type == MUSIC_B)   data.music_type = MUSIC_A;
                if (data.music_type == MUSIC_OFF) data.music_type = MUSIC_C;
                break;
            case BTN_RIGHT: // Move right in music menu
                if (data.music_type == MUSIC_A) data.music_type = MUSIC_B;
                if (data.music_type == MUSIC_C) data.music_type = MUSIC_OFF;
                break;
            case BTN_B:     // Move back to game selection
                data.select_game = true;
                break;
            case BTN_A:
            case BTN_START: // Start game
                if (data.is_a_type) {
                    Window_set(*this, &Window_A_Type_Select);
                }

                // B-type game not implemented
                // else *this = Window_set(*this, &Window_B_Type_Select);
                
                // Set music not implemented
                break;
            default:
                break;
        }
    }
}
 
void Window_Select_render_handle(window_t *this) {
    text_t is_black = 0x00;
    
    // Set is_black fields
    if (this->is_blink_black || !data.select_game) { // Game is_black
        if (data.is_a_type) is_black |= 0x1 << TEXT_GAME_A;
        else is_black |= 0x1 << TEXT_GAME_B;
    }
    if (this->is_blink_black || data.select_game) { // Music is_black
        switch (data.music_type) {
            case MUSIC_A:
                is_black |= 0x1 << TEXT_MUSIC_A;
                break;
            case MUSIC_B:
                is_black |= 0x1 << TEXT_MUSIC_B;
                break;
            case MUSIC_C:
                is_black |= 0x1 << TEXT_MUSIC_C;
                break;
            case MUSIC_OFF:
                is_black |= 0x1 << TEXT_MUSIC_OFF;
                break;
        }
    }
    
    // Game color
    _Window_Select_set_color(this, is_black, TEXT_GAME_A, 
            SELECT_GAME_ROW, SELECT_LEFT_COL, BLACK_A_TYPE, GRAY_A_TYPE);
    _Window_Select_set_color(this, is_black, TEXT_GAME_B, 
            SELECT_GAME_ROW, SELECT_RIGHT_COL, BLACK_B_TYPE, GRAY_B_TYPE);
    
    // Music color
    _Window_Select_set_color(this, is_black, TEXT_MUSIC_A, 
            SELECT_MUSIC_ROW_1, SELECT_LEFT_COL, BLACK_A_TYPE, GRAY_A_TYPE);
    _Window_Select_set_color(this, is_black, TEXT_MUSIC_B, 
            SELECT_MUSIC_ROW_1, SELECT_RIGHT_COL, BLACK_B_TYPE, GRAY_B_TYPE);
    _Window_Select_set_color(this, is_black, TEXT_MUSIC_C, 
            SELECT_MUSIC_ROW_2, SELECT_LEFT_COL, BLACK_C_TYPE, GRAY_C_TYPE);
    _Window_Select_set_color(this, is_black, TEXT_MUSIC_OFF, 
            SELECT_MUSIC_ROW_2, SELECT_RIGHT_COL, BLACK_OFF, GRAY_OFF);
}

void _Window_Select_set_color(window_t *this, text_t is_black, uint8_t bit, 
    uint8_t row, uint8_t col, const cell_e *black, const cell_e *gray) {
    uint8_t bit_mask = 0x1 << bit;
    if ((is_black & bit_mask) != (old_is_black & bit_mask)) {
        if (is_black & bit_mask) {
            _Window_write_range(this, row, col, SELECT_BLACK_LEN, black);
        } else {
            _Window_write_range(this, row, col, SELECT_BLACK_LEN, gray);
        }
        if (is_black & bit_mask) old_is_black |= bit_mask;
        else old_is_black &= ~bit_mask;
    }
}