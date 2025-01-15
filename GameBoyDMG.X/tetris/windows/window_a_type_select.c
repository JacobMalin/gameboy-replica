/* 
 * File:   window_a_type_select.c
 * Author: Jacob Malin
 *
 * Created on November 24, 2024, 6:19 AM
 */

#include "window_a_type_select.h"

const __memx cell_e DOT_STRING[] = {DT1, DT2, DT3, DT1, DT2, DT3};

static window_a_type_select_t data;
static window_a_type_select_t old;
static bool old_is_blink_black;

void Window_A_Type_Select_init(void) {
    data.level = 0;
    data.score_entry = 0; // No score being entered
    
    old.level = 0;
    old.score_entry = 0; // No score being entered
    
    // Clear score/name array
    for (uint8_t i = 0; i < NUM_LEVELS; i++) {
        for (uint8_t j = 0; j < SCORES_PER_LEVEL; j++) {
            for (uint8_t k = 0; k < DOT_LEN; k++) {
                data.scores[i][j].name[k] = '\0';
                old.scores[i][j].name[k] = '\0';
            }
            
            data.scores[i][j].score = NO_SCORE;
            old.scores[i][j].score = NO_SCORE;
        }
    }
}

void Window_A_Type_Select(window_t *this) {
    old_is_blink_black = this->is_blink_black;
    
    this->button_handler = &Window_A_Type_Select_button_handle;
    this->render_handler = &Window_A_Type_Select_render_handle;
    
    Window_A_Type_Select_initial_render(this);
}
 
void Window_A_Type_Select_initial_render(window_t *this) {
    const cell_e *screen = Screen_get(this->SD, SCREEN_A_TYPE_SELECT);
    
    data.char_index = 0;
    old.char_index = 0;
    data.sel_char = 'A';
    old.sel_char = 0; // Set old.sel_char to the wrong char so it will update
    
    for (uint8_t i = 0; i < DISPLAY_ROWS; i++) {
        // Grab row from memory
        display_row row;
        for (uint8_t j = 0; j < DISPLAY_COLS; j++) {
            row[j] = screen[i * DISPLAY_COLS + j];
        }
        
        // Modify row
        cell_e buf[DOT_LEN];
        switch (i) {
            case SELECT_LEVEL_ROW_1:
                if (data.level < NUM_LEVELS_HALF) {
                    uint8_t index = SELECT_LEVEL_COL_1 + 2 * data.level;
                    row[index] = NB0 + data.level;
                }
                break;
            case SELECT_LEVEL_ROW_2:
                if (data.level >= NUM_LEVELS_HALF) {
                    uint8_t half_level = data.level - NUM_LEVELS_HALF;
                    uint8_t index = SELECT_LEVEL_COL_1 + 2 * half_level;
                    row[index] = NB0 + data.level;
                }
                break;
            case HIGH_SCORE_ROW_1:
                Window_A_Type_Select_name_to_buffer(buf, 
                        data.scores[data.level][0].name);
                _Window_replace_range(row, HIGH_SCORE_COL_1, DOT_LEN, buf);
                Window_A_Type_Select_score_to_buffer(buf, 
                        data.scores[data.level][0].score);
                _Window_replace_range(row, HIGH_SCORE_COL_2, DOT_LEN, buf);
                break;
            case HIGH_SCORE_ROW_1 + 1:
                Window_A_Type_Select_name_to_buffer(buf, 
                        data.scores[data.level][1].name);
                _Window_replace_range(row, HIGH_SCORE_COL_1, DOT_LEN, buf);
                Window_A_Type_Select_score_to_buffer(buf, 
                        data.scores[data.level][1].score);
                _Window_replace_range(row, HIGH_SCORE_COL_2, DOT_LEN, buf);
                break;
            case HIGH_SCORE_ROW_1 + 2:
                Window_A_Type_Select_name_to_buffer(buf, 
                        data.scores[data.level][2].name);
                _Window_replace_range(row, HIGH_SCORE_COL_1, DOT_LEN, buf);
                Window_A_Type_Select_score_to_buffer(buf, 
                        data.scores[data.level][2].score);
                _Window_replace_range(row, HIGH_SCORE_COL_2, DOT_LEN, buf);
                break;
            default:
                break;
        }
        
        Display_display_row(this->Display, row, i);
    }
}

void Window_A_Type_Select_button_handle(window_t **this, buttons_cmd button) {    
    if (button.edge != KEY_DOWN) return;
    
    if (!data.score_entry) { // Select level
        switch (button.button) {
            case BTN_UP:    // Move up level selection menu
                if (data.level >= NUM_LEVELS_HALF) {
                    data.level -= NUM_LEVELS_HALF;
                }
                break;
            case BTN_DOWN:  // Move down level selection menu
                if (data.level < NUM_LEVELS_HALF) {
                    data.level += NUM_LEVELS_HALF;
                }
                break;
            case BTN_LEFT:  // Move left level selection menu
                if (data.level > 0) data.level--;
                break;
            case BTN_RIGHT: // Move right level selection menu
                if (data.level < NUM_LEVELS - 1) data.level++;
                break;
            case BTN_B:     // Return game selection window
                Window_set(*this, &Window_Select);
                break;
            case BTN_A:
            case BTN_START: // Start game !!
                Window_A_Type_Game_set_level(data.level); // Send level to game
                Window_set(*this, &Window_A_Type_Game);
                break;
            default:
                break;
        }
    } else { // Enter score
        switch (button.button) {
            case BTN_UP:    // Change to next letter/symbol
                if (data.sel_char == 4) data.sel_char = 'A';
                else if (data.sel_char == 'Z') data.sel_char = 1;
                else data.sel_char++;
                break;
            case BTN_DOWN:  // Change to previous letter/symbol
                if (data.sel_char == 1) data.sel_char = 'Z';
                else if (data.sel_char == 'A') data.sel_char = 4;
                else data.sel_char--;
                break;
            case BTN_A:     // Select next character
                // If last char, confirm name
                if (data.char_index == DOT_LEN - 1) {
                    // Store the char in the scores array
                    data.scores[data.level][data.score_entry - 1].name[data.char_index] = data.sel_char;
                    data.score_entry = 0; // Returns to level selection
                }
                else {
                    // Store the char in the scores array
                    data.scores[data.level][data.score_entry - 1].name[data.char_index] = data.sel_char;
                    data.char_index++; // Move one char right
                    // Retrieve the previously edited char (if it exists)
                    data.sel_char = data.scores[data.level][data.score_entry - 1].name[data.char_index];
                    // If the letter does not exist, set to A
                    if (data.sel_char == 0) {
                        data.sel_char = 'A';
                    }
                    // Set old.sel_char to the wrong value so that it'll update
                    old.sel_char = data.sel_char + 1;
                }
                break;
            case BTN_B:     // Select previous character
                if (data.char_index > 0) { // As long as not first character
                    // Store the char in the scores array
                    data.scores[data.level][data.score_entry - 1].name[data.char_index] = data.sel_char;
                    data.char_index--; // Move one char left
                    // Retrieve the previously edited char
                    data.sel_char = data.scores[data.level][data.score_entry - 1].name[data.char_index];
                    // Set old.sel_char to the wrong value so that it'll update
                    old.sel_char = data.sel_char + 1;
                }
                break;
            case BTN_START: // Confirm name
                // Store the char in the scores array
                data.scores[data.level][data.score_entry - 1].name[data.char_index] = data.sel_char;
                data.score_entry = 0; // Returns to level selection
                break;
            default:
                break;
        }
    }
}
 
void Window_A_Type_Select_render_handle(window_t *this) {
    bool blink_on_but_no_gray = this->is_blink_black || data.score_entry;
        
    // If level has changed
    if (data.level != old.level) {
        if (blink_on_but_no_gray) {
            if (data.level < NUM_LEVELS_HALF) { // Selection is in first half
                uint8_t col_num = SELECT_LEVEL_COL_1 + 2 * data.level;
                cell_e cell = NB0 + data.level;
                Display_write_cell(this->Display, SELECT_LEVEL_ROW_1, col_num, 
                        cell);
            } else { // Selection is in second half
                uint8_t half_level = data.level - NUM_LEVELS_HALF;
                uint8_t col_num = SELECT_LEVEL_COL_1 + 2 * half_level;
                cell_e cell = NB0 + data.level;
                Display_write_cell(this->Display, SELECT_LEVEL_ROW_2, col_num, 
                        cell);
            }
        }
        
        
        // Write the old level to be gray
        if (old.level < NUM_LEVELS_HALF) {
            uint8_t col_num = SELECT_LEVEL_COL_1 + 2 * old.level;
            cell_e cell = G_0 + old.level;
            Display_write_cell(this->Display, SELECT_LEVEL_ROW_1, col_num, 
                    cell);
        } else {
            uint8_t half_level = old.level - NUM_LEVELS_HALF;
            uint8_t col_num = SELECT_LEVEL_COL_1 + 2 * half_level;
            cell_e cell = G_0 + old.level;
            Display_write_cell(this->Display, SELECT_LEVEL_ROW_2, col_num, 
                    cell);
        }
        
        // Change top scores as level changes
        for (uint8_t i = 0; i < SCORES_PER_LEVEL; i++) {
            cell_e buf[DOT_LEN];
            Window_A_Type_Select_name_to_buffer(buf, 
                    data.scores[data.level][i].name);
            _Window_write_range(this, HIGH_SCORE_ROW_1 + i, HIGH_SCORE_COL_1, 
                    DOT_LEN, buf);
            Window_A_Type_Select_score_to_buffer(buf, 
                    data.scores[data.level][i].score);
            _Window_write_range(this, HIGH_SCORE_ROW_1 + i, HIGH_SCORE_COL_2, 
                    DOT_LEN, buf);
        }
        
        old.level = data.level;
    }
    
    // If blink changes
    if (this->is_blink_black != old_is_blink_black) {
        if (!data.score_entry) { // Level select
            if (this->is_blink_black) { // Change to black
                if (data.level < NUM_LEVELS_HALF) { // First half
                    uint8_t col_num = SELECT_LEVEL_COL_1 + 2 * data.level;
                    cell_e cell = NB0 + data.level;
                    Display_write_cell(this->Display, SELECT_LEVEL_ROW_1, col_num, 
                            cell);
                } else { // Second half
                    uint8_t half_level = data.level - NUM_LEVELS_HALF;
                    uint8_t col_num = SELECT_LEVEL_COL_1 + 2 * half_level;
                    cell_e cell = NB0 + data.level;
                    Display_write_cell(this->Display, SELECT_LEVEL_ROW_2, col_num, 
                            cell);
                }
            } else { // Change to gray
                if (data.level < NUM_LEVELS_HALF) { // First half
                    uint8_t col_num = SELECT_LEVEL_COL_1 + 2 * data.level;
                    cell_e cell = G_0 + data.level;
                    Display_write_cell(this->Display, SELECT_LEVEL_ROW_1, col_num, 
                            cell);
                } else { // Second half
                    uint8_t half_level = data.level - NUM_LEVELS_HALF;
                    uint8_t col_num = SELECT_LEVEL_COL_1 + 2 * half_level;
                    cell_e cell = G_0 + data.level;
                    Display_write_cell(this->Display, SELECT_LEVEL_ROW_2, col_num, 
                            cell);
                }
            }
        }
        
        // Name entry; every time the blink changes, swap to black or to WH_
        else {
            cell_e cell;
            uint8_t row_num = HIGH_SCORE_ROW_1 + data.score_entry - 1;
            uint8_t col_num = HIGH_SCORE_COL_1 + data.char_index;
            if (this->is_blink_black) cell = _WATS_char_to_cell(data.sel_char);
            else cell = WH_;
            Display_write_cell(this->Display, row_num, col_num, cell);
        }
        
        old_is_blink_black = this->is_blink_black;
    }
    
    if (data.score_entry) { // Enter name
        // If selected char is different, write new character
        if (data.sel_char != old.sel_char) {
            uint8_t row_num = HIGH_SCORE_ROW_1 + data.score_entry - 1;
            uint8_t col_num = HIGH_SCORE_COL_1 + data.char_index;
            cell_e cell = _WATS_char_to_cell(data.sel_char);
            Display_write_cell(this->Display, row_num, col_num, cell);
            
            old.sel_char = data.sel_char;
        }
        
        // If selected char index is different, write previous cell to black
        if (data.char_index != old.char_index) {
            uint8_t row_num = HIGH_SCORE_ROW_1 + data.score_entry - 1;
            uint8_t col_num = HIGH_SCORE_COL_1 + old.char_index;
            char c = data.scores[data.level][data.score_entry - 1].name[old.char_index];
            cell_e cell = _WATS_char_to_cell(c);
            Display_write_cell(this->Display, row_num, col_num, cell);
            
            old.char_index = data.char_index;
        }
    }
    
    // If score entry mode changed
    if (data.score_entry != old.score_entry) {
        // And is no longer score entry, write previous cell to black
        if (!data.score_entry) {
            uint8_t row_num = HIGH_SCORE_ROW_1 + old.score_entry - 1;
            uint8_t col_num = HIGH_SCORE_COL_1 + old.char_index;
            char c = data.scores[data.level][old.score_entry - 1].name[old.char_index];
            cell_e cell = _WATS_char_to_cell(c);
            Display_write_cell(this->Display, row_num, col_num, cell);
        }
        
        old.score_entry = data.score_entry;
    }
}

void Window_A_Type_Select_score_to_buffer(cell_e buf[], uint32_t score) {
    if (NO_SCORE) { // If no score, fill with dots
        for (uint8_t i = 0; i < DOT_LEN; i++) {
            buf[i] = DOT_STRING[i];
        }
    } else { // Fill with name from the left and rest with dots
        for (uint8_t i = 0; i < DOT_LEN; i++) {
            uint8_t col = DOT_LEN - i - 1;
            if (score <= 0) { // Rest of string is dots
                buf[col] = DOT_STRING[col];
            } else { // Given digit is set
                uint8_t digit = score % 10;
                buf[col] = NB0 + digit;

                score /= 10;
            }
        }
    }
}

void Window_A_Type_Select_name_to_buffer(cell_e buf[], char name[DOT_LEN]) {
    for (uint8_t i = 0; i < DOT_LEN; i++) {
        char c = name[i];
        buf[i] = _WATS_char_to_cell(c);
        // If func returns DT1, replace with regular dots
        if (buf[i] == DT1) buf[i] = DOT_STRING[i];
    }
}

cell_e _WATS_char_to_cell(char c) {
    switch (c) {
        case 0: // No character at index
            return DT1;
            break;
        case 1: // Period
            return PRD;
            break;
        case 2: // Dash
            return DSH;
            break;
        case 3: // X symbol
            return XXX;
            break;
        case 4: // Space
            return WH_;
            break;
        default: // Alphabet character
            return A__ + (c - 'A');
    }
}

void Window_A_Type_Select_new_score(uint32_t new_score) {
    // If better than 1st place score
    if (new_score > data.scores[data.level][0].score) {
        data.score_entry = 1;
        
        // Copy previous high score names lower
        for (uint8_t k = 0; k < DOT_LEN; k++) {
            data.scores[data.level][2].name[k] = data.scores[data.level][1].name[k];
            data.scores[data.level][1].name[k] = data.scores[data.level][0].name[k];
            data.scores[data.level][0].name[k] = '\0';
        }
        
        // Copy previous high scores lower
        data.scores[data.level][2].score = data.scores[data.level][1].score;
        data.scores[data.level][1].score = data.scores[data.level][0].score;
        data.scores[data.level][0].score = new_score;
    }
    
    // If better than 2nd place score
    else if (new_score > data.scores[data.level][1].score) {
        data.score_entry = 2;
        
        // Copy previous high score names lower
        for (uint8_t k = 0; k < DOT_LEN; k++) {
            data.scores[data.level][2].name[k] = data.scores[data.level][1].name[k];
            data.scores[data.level][1].name[k] = '\0';
        }
        
        // Copy previous high scores lower
        data.scores[data.level][2].score = data.scores[data.level][1].score;
        data.scores[data.level][1].score = new_score;
    }
    
    // If better than 3rd place score
    else if (new_score > data.scores[data.level][1].score) {
        data.score_entry = 3;
        
        // Clears previous 3rd place score name
        for (uint8_t k = 0; k < DOT_LEN; k++) {
            data.scores[data.level][2].name[k] = '\0';
        }
        
        // Clears previous 3rd place score
        data.scores[data.level][2].score = new_score;
    }
}