/* 
 * File:   window_a_type_game.c
 * Author: Jacob Malin
 *
 * Created on November 24, 2024, 6:19 AM
 */

#include "window_a_type_game.h"

static window_a_type_game_t data;
static window_a_type_game_t old;
static board_t board;

static tetrimino_t *current;
static tetrimino_t *next;

static bool is_left;
static bool is_right;
static uint8_t gravity_clock;
static uint8_t left_das_clock;
static uint8_t right_das_clock;

static bool is_soft;
static uint8_t soft_rows; // How many rows have been soft-dropped in a row

static bool do_preview = true;
static bool preview_on = true; // Old version of do_preview

static uint8_t is_line_clear = 0; // If the line clear animation is active
static uint32_t line_check; // Which lines have been cleared last (bitfield)
static uint8_t line_check_count; // How many lines have been cleared last

// Gravity per level. (Level 0 is 53 frames; Level 1 is 49 frames; ...)
const __memx uint8_t FRAMES_PER_ROW[] = {
    53, 49, 45, 41, 37, 33, 28, 22, 17, 11, 10, 9, 8, 7, 6, 6, 5, 5, 4, 4, 3
};

// Score per lines cleared
const __memx uint16_t SCORE_PER_LINES[] = {
    40, 100, 300, 1200
};

void Window_A_Type_Game_init(void) {
    data.level = 0;
    data.lines = 0;
    data.score = 0;
    data.is_paused = false;
    
    old.level = 0;
    old.lines = 0;
    old.score = 0;
    old.is_paused = false;
    
    // Clear board
    for (uint8_t i = 0; i < BOARD_ROWS; i++) {
        for (uint8_t j= 0; j < BOARD_COLS; j++) {
            board[i][j] = WH_;
        }
    }
}

void Window_A_Type_Game(window_t *this) {
    this->button_handler = &Window_A_Type_Game_button_handle;
    this->render_handler = &Window_A_Type_Game_render_handle;
    
    // Clear button-held-downs on entry
    is_left = false;
    is_right = false;
    is_soft = false;
    
    // Setup game
    data.lines = 0;
    data.score = 0;
    data.is_paused = false;
    old.lines = 0;
    old.score = 0;
    old.is_paused = false;
    
    // Clear board
    for (uint8_t i = 0; i < BOARD_ROWS; i++) {
        for (uint8_t j= 0; j < BOARD_COLS; j++) {
            board[i][j] = WH_;
        }
    }
    
    // Generate initial blocks and preview
    uint8_t current_index = Random_generate(TETRIMINO_COUNT);
    uint8_t next_index = Random_generate_avoid(TETRIMINO_COUNT, current_index);
    current = Tetrimino(current_index, BOARD_SPAWN_X, BOARD_SPAWN_Y);
    next = Tetrimino(next_index, BOARD_SPAWN_X, BOARD_SPAWN_Y);
    
    Window_A_Type_Game_initial_render(this);
}
 
void Window_A_Type_Game_initial_render(window_t *this) {
    const cell_e *screen = Screen_get(this->SD, SCREEN_A_TYPE_GAME);
    
    for (uint8_t i = 0; i < DISPLAY_ROWS; i++) {
        // Grab row from memory
        display_row row;
        for (uint8_t j = 0; j < DISPLAY_COLS; j++) {
            row[j] = screen[i * DISPLAY_COLS + j];
        }
        
        // Display tetriminoes
        Tetrimino_initial_render(current, row, i);
        Tetrimino_initial_preview(next, row, i);
        
        // Display initial level
        if (i == LEVEL_ROW) {
            row[LEVEL_RIGHT_COL] = NB0 + data.level;
        }
        
        Display_display_row(this->Display, row, i);
    }
}

void Window_A_Type_Game_button_handle(window_t **this, buttons_cmd button) {    
    if (button.edge == KEY_DOWN) {
        // Not paused
        if (!data.is_paused) {
            switch (button.button) {
                case BTN_DOWN:   // Soft drop
                    is_soft = true;
                    soft_rows = 0; // Reset soft rows on non-continuous drop
                    break;
                case BTN_LEFT:   // Move left
                    if (!is_right) Tetrimino_move_left(current, *board);
                    is_left = true;
                    left_das_clock = 0;
                    right_das_clock = 0;
                    break;
                case BTN_RIGHT:  // Move right
                    if (!is_left) Tetrimino_move_right(current, *board);
                    is_right = true;
                    left_das_clock = 0;
                    right_das_clock = 0;
                    break;
                case BTN_A:      // Clockwise rotate
                    Tetrimino_rotate_cw(current, *board);
                    break;
                case BTN_B:      // Counter-clockwise rotate
                    Tetrimino_rotate_ccw(current, *board);
                    break;
                case BTN_START:  // Pause game
                    data.is_paused = true;
                    break;
                case BTN_SELECT: // Show/hide preview
                    do_preview = !do_preview;
                    break;
                default:
                    break;
            }
        }
        
        // Paused
        else {
            switch (button.button) {
                case BTN_LEFT:   // Move left
                    is_left = true;
                    left_das_clock = HALF_DAS_DELAY;
                    right_das_clock = 0;
                    break;
                case BTN_RIGHT:  // Move right
                    is_right = true;
                    left_das_clock = 0;
                    right_das_clock = HALF_DAS_DELAY;
                    break;
                case BTN_START:  // Unpause game
                    data.is_paused = false;
                    break;
                case BTN_SELECT: // Show/hide preview
                    do_preview = !do_preview;
                    break;
                default:
                    break;
            }
        }
    }
    
    // KEY_UP
    else {
        switch (button.button) {
            case BTN_DOWN:   // Soft drop
                is_soft = false;
                break;
            case BTN_LEFT:   // Move left
                if (is_right) Tetrimino_move_right(current, *board);
                is_left = false;
                left_das_clock = 0;
                right_das_clock = 0;
                break;
            case BTN_RIGHT:  // Move right
                if (is_left) Tetrimino_move_left(current, *board);
                is_right = false;
                left_das_clock = 0;
                right_das_clock = 0;
                break;
            default:
                break;
        }
    }
}
 
void Window_A_Type_Game_render_handle(window_t *this) {
    // If pause state has changed
    if (data.is_paused != old.is_paused) {
        if (data.is_paused) {
            // Grab row from memory
            const cell_e *screen = Screen_get(this->SD, SCREEN_PAUSED);
            
            // Draw only over the board
            for (uint8_t i = 0; i < BOARD_ROWS; i++) {
                for (uint8_t j = 0; j < BOARD_COLS; j++) {
                    cell_e cell = screen[i * DISPLAY_COLS + BOARD_OFFSET + j];
                    Display_write_cell(this->Display, i, j + BOARD_OFFSET, 
                            cell);
                }
            }
            if (do_preview) Tetrimino_unpreview(next, this->Display);
        } else {
            // Redraw board state
            for (uint8_t i = 0; i < BOARD_ROWS; i++) {
                for (uint8_t j = 0; j < BOARD_COLS; j++) {
                    cell_e cell = board[i][j];
                    Display_write_cell(this->Display, i, j + BOARD_OFFSET, 
                            cell);
                }
            }
            
            // Redraw current tetrimino and preview tetrimino
            Tetrimino_initial_display(current, this->Display);
            if (do_preview) Tetrimino_preview(next, this->Display);
        }
        
        old.is_paused = data.is_paused;
    }
    
    // Normal game state (not paused)
    if (!data.is_paused) {
        // Line clear animation
        if (is_line_clear) {
            // G, Off, G, Off, G, Off, W, Down, New
            const uint8_t spd = LINE_CLEAR_ANIMATION_SPEED;
            switch (is_line_clear++) {
                case 0 * spd + 1:
                case 2 * spd + 1:
                case 4 * spd + 1: // Gray
                    _WATG_line_clear_gray(this, line_check);
                    break;
                case 1 * spd + 1:
                case 3 * spd + 1:
                case 5 * spd + 1: // Re-render lines
                    _WATG_line_clear_render(this, line_check, *board);
                    break;
                case 6 * spd + 1: // White
                    _WATG_line_clear_white(this, line_check);
                    break;
                case 7 * spd + 1: // Move down
                    _WATG_line_clear_down(this, line_check, *board);
                    break;
                case 8 * spd + 1: // New tetrimino & score/lines/level update
                    _WATG_new_tetrimino(this);
    
                    data.score += SCORE_PER_LINES[line_check_count - 1] * 
                            (data.level + 1);
                    data.lines += line_check_count;
                    if (data.level < MAX_LEVEL && 
                            data.lines >= (data.level + 1) * LINES_PER_LEVEL) {
                        data.level++;
                    }
                    is_line_clear = 0; // Last step, resume normal gameplay
                    break;
            }
        }
        
        else _WATG_normal_game_loop(this);
    }
}

void _WATG_normal_game_loop(window_t *this) {
    // Preview toggle
    if (do_preview != preview_on) {
        if (do_preview) {
            Tetrimino_preview(next, this->Display);
            preview_on = true;
        } else {
            Tetrimino_unpreview(next, this->Display);
            preview_on = false;
        }
    }

    // Delayed auto shift (DAS)
    if (is_left && !is_right) {
        if (left_das_clock >= DAS_DELAY) { // After DAS delay
            // Once per DAS_SPEED frames
            uint8_t das_interval = (left_das_clock - DAS_DELAY) % DAS_SPEED;
            if (das_interval == 0) Tetrimino_move_left(current, *board);
        }

        left_das_clock++;
    } else if (is_right && !is_left) {
        if (right_das_clock >= DAS_DELAY) { // After DAS delay
            // Once per DAS_SPEED frames
            uint8_t das_interval = (right_das_clock - DAS_DELAY) % DAS_SPEED;
            if (das_interval == 0) Tetrimino_move_right(current, *board);
        }

        right_das_clock++;
    }

    // Gravity
    uint8_t gravity_rate = FRAMES_PER_ROW[data.level] - 1;
    bool left_xor_right = (is_left && !is_right) || (!is_left && is_right);
    if (is_soft && !left_xor_right) gravity_rate = SOFT_GRAVITY - 1;
    if (gravity_clock >= gravity_rate) {
        if (!Tetrimino_move_down(current, *board)) { // Collision
            // If collision without moving from spawn; end game
            if (current->x == BOARD_SPAWN_X && current->y == BOARD_SPAWN_Y) {
                Window_A_Type_Select_new_score(data.score);
                Tetrimino_unpreview(next, this->Display);
                Tetrimino_initial_display(next, this->Display);
                Window_set(this, &Window_Game_Over);
            }

            // Normal collision
            else {
                // Place current in the graveyard
                Tetrimino_update_board(current, *board);

                // Check for line clear
                line_check = _WATG_check_line_clear(current, *board);

                // Remove current tetrimino
                Tetrimino_free(current);

                // Start line clear animation or generate new tetrimino
                if (line_check > 0) is_line_clear = 1;
                else _WATG_new_tetrimino(this);
            }
        } else { // No collision on down
            if (is_soft && !left_xor_right) soft_rows++;
        }

        gravity_clock = 0;
    } else gravity_clock++;

    // Render
    Tetrimino_display(current, this->Display);
    Window_A_Type_Game_render_score(this);
    Window_A_Type_Game_render_level(this);
    Window_A_Type_Game_render_lines(this);
}

void Window_A_Type_Game_set_level(uint8_t level) {
    data.level = level;
    old.level = level;
}

void Window_A_Type_Game_render_score(window_t *this) {
    if (old.score != data.score) {
        uint32_t score = data.score;
        
        // Grab each digit from the score and render
        for (uint8_t i = 0; i < HIGH_SCORE_LEN; i++) {
            if (score <= 0) break;
            
            uint8_t digit = score % 10;
            uint8_t col = HIGH_SCORE_RIGHT_COL - i;
            Display_write_cell(this->Display, HIGH_SCORE_ROW, col, NB0 + digit);
            
            score /= 10;
        }
        
        old.score = data.score;
    }
}

void Window_A_Type_Game_render_level(window_t *this) {
    if (old.level != data.level) {
        uint32_t level = data.level;
        
        // Grab each digit from the level and render
        for (uint8_t i = 0; i < HIGH_SCORE_LEN; i++) {
            if (level <= 0) break;
            
            uint8_t digit = level % 10;
            uint8_t col = LEVEL_RIGHT_COL - i;
            Display_write_cell(this->Display, LEVEL_ROW, col, NB0 + digit);
            
            level /= 10;
        }
        
        old.level = data.level;
    }
}

void Window_A_Type_Game_render_lines(window_t *this) {
    if (old.lines != data.lines) {
        uint32_t lines = data.lines;
        
        // Grab each digit from the lines and render
        for (uint8_t i = 0; i < HIGH_SCORE_LEN; i++) {
            if (lines <= 0) break;
            
            uint8_t digit = lines % 10;
            uint8_t col = LINES_RIGHT_COL - i;
            Display_write_cell(this->Display, LINES_ROW, col, NB0 + digit);
            
            lines /= 10;
        }
        
        old.lines = data.lines;
    }
}

void _WATG_new_tetrimino(window_t *this) {
    bool left_xor_right = (is_left && !is_right) || (!is_left && is_right);

    // Move next to current
    if (do_preview) Tetrimino_unpreview(next, this->Display);
    current = next;
    Tetrimino_initial_display(current, this->Display);

    // Make a new next
    uint8_t next_index = Random_generate_avoid(TETRIMINO_COUNT, current->type);
    next = Tetrimino(next_index, BOARD_SPAWN_X, BOARD_SPAWN_Y);
    if (do_preview) Tetrimino_preview(next, this->Display);

    // Increase score
    if (is_soft && !left_xor_right) data.score += soft_rows;

    // Clear DAS clocks and soft drop
    left_das_clock = 0;
    right_das_clock = 0;
    is_soft = false;
}

uint32_t _WATG_check_line_clear(tetrimino_t *tetri, uint8_t *board) {
    uint32_t res = 0;
    
    // Only rows that the current tetrimino has a block in can be cleared
    for (uint8_t i = 0; i < BLOCKS_IN_TETRIMINO; i++) {
        block_t block = tetri->blocks[i];
        uint8_t y = Tetrimino_get_block_y(tetri->rotation, tetri->y, block);
        
        // Check if row is full
        bool is_full = true;
        for (uint8_t j = 0; j < BOARD_COLS; j++) {
            uint8_t x = j;
            if (board[y * BOARD_COLS + x] == WH_) {
                is_full = false;
                break;
            }
        }
        
        uint32_t mask, one = 1;
        mask = one << y;
        
        if (is_full) res |= mask;
    }
    
    return res;
}

void _WATG_line_clear_down(window_t *this, uint32_t line_check, uint8_t *board) {
    uint8_t copy = 0; // Lines cleared so far
    // For all rows from bottom to top
    for (int8_t i = BOARD_ROWS - 1; i >= 0; i--) {
        uint32_t mask, one = 1;
        mask = one << i;
        
        if (copy > 0) { // If a line has been cleared so far
            // Then shift row down by 'copy' rows
            for (int8_t j = 0; j < BOARD_COLS; j++) {
                cell_e cell = board[i * BOARD_COLS + j];
                board[(i + copy) * BOARD_COLS + j] = cell;
                Display_write_cell(this->Display, i + copy, j + BOARD_OFFSET_X, 
                        cell);
            }
        }
        
        // If line_check indicate the row should be cleared, increment copy
        if ((line_check & mask) > 0) copy++;
    }
    
    line_check_count = copy;
}

void _WATG_line_clear_gray(window_t *this, uint32_t line_check) {
    for (int8_t i = BOARD_ROWS - 1; i >= 0; i--) {
        uint32_t mask, one = 1;
        mask = one << i;
        
        // If line_check indicate the row should be cleared, turn it grey
        if ((line_check & mask) > 0) {
            for (int8_t j = 0; j < BOARD_COLS; j++) {
                cell_e cell = GY_;
                Display_write_cell(this->Display, i, j + BOARD_OFFSET_X, cell);
            }
        }
    }
}

void _WATG_line_clear_render(window_t *this, uint32_t line_check, 
        uint8_t *board) {
    for (int8_t i = BOARD_ROWS - 1; i >= 0; i--) {
        uint32_t mask, one = 1;
        mask = one << i;
        
        // If line_check indicate the row should be cleared, re-render it
        if ((line_check & mask) > 0) {
            for (int8_t j = 0; j < BOARD_COLS; j++) {
                cell_e cell = board[i * BOARD_COLS + j];
                Display_write_cell(this->Display, i, j + BOARD_OFFSET_X, cell);
            }
        }
    }
}

void _WATG_line_clear_white(window_t *this, uint32_t line_check) {
    for (int8_t i = BOARD_ROWS - 1; i >= 0; i--) {
        uint32_t mask, one = 1;
        mask = one << i;
        
        // If line_check indicate the row should be cleared, turn it white
        if ((line_check & mask) > 0) {
            for (int8_t j = 0; j < BOARD_COLS; j++) {
                cell_e cell = WH_;
                Display_write_cell(this->Display, i, j + BOARD_OFFSET_X, cell);
            }
        }
    }
}