/* 
 * File:   tetrimino.c
 * Author: Jacob Malin
 *
 * Created on December 3, 2024, 9:02 PM
 */

#include "tetrimino.h"

// For each tetrimino_e
const __memx block_t INITIAL[TETRIMINO_COUNT][BLOCKS_IN_TETRIMINO] = {
    {{-1, 0, TML}, {0, 0, TML}, {1, 0, TML}, {-1, 1, TML}},
    {{-1, 0, TMJ}, {0, 0, TMJ}, {1, 0, TMJ}, {1, 1, TMJ}},
    {{-1, 0, TI1}, {0, 0, TI2}, {1, 0, TI2}, {2, 0, TI3}},
    {{0, 0, TMO}, {1, 0, TMO}, {0, 1, TMO}, {1, 1, TMO}},
    {{-1, 0, TMZ}, {0, 0, TMZ}, {0, 1, TMZ}, {1, 1, TMZ}},
    {{0, 0, TMS}, {1, 0, TMS}, {-1, 1, TMS}, {0, 1, TMS}},
    {{-1, 0, TMT}, {0, 0, TMT}, {1, 0, TMT}, {0, 1, TMT}},
};

// For each tetrimino_e
const __memx uint8_t NUM_ROTATIONS[TETRIMINO_COUNT] = { 4, 4, 2, 1, 2, 2, 4 };

tetrimino_t *Tetrimino(tetrimino_e type, uint8_t x, uint8_t y) {
    tetrimino_t *Tetrimino = pvPortMalloc(sizeof(tetrimino_t));

    Tetrimino->type = type;
    Tetrimino->x = x;
    Tetrimino->y = y;
    for (uint8_t i = 0; i < BLOCKS_IN_TETRIMINO; i++) {
        Tetrimino->blocks[i] = INITIAL[type][i];
    }
    Tetrimino->rotation = 0; // Unrotated

    return Tetrimino;
}

void Tetrimino_free(tetrimino_t *this) {
    vPortFree(this);
}

void Tetrimino_initial_render(tetrimino_t *this, display_row row, 
        uint8_t row_num) {
    for (uint8_t i = 0; i < BLOCKS_IN_TETRIMINO; i++) {
        block_t block = this->blocks[i];
        uint8_t x = this->x + block.x + BOARD_OFFSET_X;
        uint8_t y = this->y + block.y;
        
        if (y  == row_num) row[x] = block.cell;
    }
    
    this->last_render_x = this->x;
    this->last_render_y = this->y;
    this->last_rotation = this->rotation;
}

void Tetrimino_initial_display(tetrimino_t *this, display_t *display) {
    for (uint8_t i = 0; i < BLOCKS_IN_TETRIMINO; i++) {
        block_t block = this->blocks[i];
        uint8_t x = Tetrimino_get_block_x(this->rotation, this->x, block);
        uint8_t y = Tetrimino_get_block_y(this->rotation, this->y, block);
        x += BOARD_OFFSET_X;

        cell_e cell = block.cell;
        // Tetrimino I has different cells based on rotation
        if (this->type == TETRIMINO_I && this->rotation == 3) cell += 3;
        Display_write_cell(display, y, x, cell);
    }

    this->last_render_x = this->x;
    this->last_render_y = this->y;
    this->last_rotation = this->rotation;
}

void Tetrimino_initial_preview(tetrimino_t *this, display_row row, 
        uint8_t row_num) {    
    for (uint8_t i = 0; i < BLOCKS_IN_TETRIMINO; i++) {
        block_t block = this->blocks[i];
        // Ignore actual position and render at preview position
        uint8_t x = PREVIEW_OFFSET_X + block.x;
        uint8_t y = PREVIEW_OFFSET_Y + block.y;
        
        if (y  == row_num) row[x] = block.cell;
    }
}

void Tetrimino_display(tetrimino_t *this, display_t *display) {
    // If x, y, or rotation has changed
    if (this->x != this->last_render_x || this->y != this->last_render_y || 
            this->rotation != this->last_rotation) {
        _Tetrimino_undisplay(this, display);

        // Check for all new blocks, if none match with the old blocks, 
        // render them
        for (uint8_t i = 0; i < BLOCKS_IN_TETRIMINO; i++) {
            block_t block = this->blocks[i];
            uint8_t x = Tetrimino_get_block_x(this->rotation, this->x, block);
            uint8_t y = Tetrimino_get_block_y(this->rotation, this->y, block);
            x += BOARD_OFFSET_X;
            
            // Compare against old position
            bool do_render = true;
            // Tetrimino I must always be re-rendered
            if (this->type != TETRIMINO_I) {
                for (uint8_t j = 0; j < BLOCKS_IN_TETRIMINO; j++) {
                    block_t old_block = this->blocks[j];
                    uint8_t old_x = Tetrimino_get_block_x(this->last_rotation, 
                            this->last_render_x, old_block);
                    uint8_t old_y = Tetrimino_get_block_y(this->last_rotation, 
                            this->last_render_y, old_block);
                    old_x += BOARD_OFFSET_X;

                    // If both coords match, do not render
                    if (old_x == x && old_y == y) {
                        do_render = false;
                        break;
                    }
                }
            }
            
            cell_e cell = block.cell;
            // Tetrimino I has different cells based on rotation
            if (this->type == TETRIMINO_I && this->rotation == 3) cell += 3;
            // If the block does not match with any new block and the y value is
            // not y == -1, then render
            if (do_render && y != 0xFF) Display_write_cell(display, y, x, cell);
        }

        this->last_render_x = this->x;
        this->last_render_y = this->y;
        this->last_rotation = this->rotation;
    }
}

void Tetrimino_preview(tetrimino_t *this, display_t *display) {
    for (uint8_t i = 0; i < BLOCKS_IN_TETRIMINO; i++) {
        block_t block = this->blocks[i];
        // Ignore actual position and render at preview position
        uint8_t x = PREVIEW_OFFSET_X + block.x;
        uint8_t y = PREVIEW_OFFSET_Y + block.y;
        Display_write_cell(display, y, x, block.cell);
    }
}

void _Tetrimino_undisplay(tetrimino_t *this, display_t *display) {
    // Check for all old blocks, if none match with the new blocks, undisplay
    // them
    for (uint8_t i = 0; i < BLOCKS_IN_TETRIMINO; i++) {
        block_t block = this->blocks[i];
        uint8_t x = Tetrimino_get_block_x(this->last_rotation, 
                this->last_render_x, block);
        uint8_t y = Tetrimino_get_block_y(this->last_rotation, 
                this->last_render_y, block);
        x += BOARD_OFFSET_X;
        
        // Compare against new position
        bool do_render = true;
        for (uint8_t j = 0; j < BLOCKS_IN_TETRIMINO; j++) {
            block_t new_block = this->blocks[j];
            uint8_t new_x = Tetrimino_get_block_x(this->rotation, this->x, 
                    new_block);
            uint8_t new_y = Tetrimino_get_block_y(this->rotation, this->y, 
                    new_block);
            new_x += BOARD_OFFSET_X;
            
            // If both coords match, do not render
            if (new_x == x && new_y == y) {
                do_render = false;
                break;
            }
        }
        
        // If the block does not match with any new block and the y value is not
        // y == -1, then undisplay
        if (do_render && y != 0xFF) Display_write_cell(display, y, x, WH_);
    }
}

void Tetrimino_unpreview(tetrimino_t *this, display_t *display) {
    for (uint8_t i = 0; i < BLOCKS_IN_TETRIMINO; i++) {
        block_t block = this->blocks[i];
        // Ignore actual position and unrender at preview position
        uint8_t x = PREVIEW_OFFSET_X + block.x;
        uint8_t y = PREVIEW_OFFSET_Y + block.y;
        
        Display_write_cell(display, y, x, WH_);
    }
}

bool Tetrimino_move_down(tetrimino_t *this, uint8_t *board) {
    // Move down
    this->y++;
    
    // Check for collision
    if (_Tetrimino_collision(this, board)) {
        this->y--; // Unmove down
        return false;
    }
    
    return true;
}

bool Tetrimino_move_left(tetrimino_t *this, uint8_t *board) {
    // Move left
    this->x--;
    
    // Check for collision
    if (_Tetrimino_collision(this, board)) {
        this->x++; // Unmove left
        return false;
    }
    
    return true;
}

bool Tetrimino_move_right(tetrimino_t *this, uint8_t *board) {
    // Move right
    this->x++;
    
    // Check for collision
    if (_Tetrimino_collision(this, board)) {
        this->x--; // Unmove right
        return false;
    }
    
    return true;
}

bool Tetrimino_rotate_cw(tetrimino_t *this, uint8_t *board) {
    // Rotate clockwise
    uint8_t prev_rotation = this->rotation;
    if (this->type != TETRIMINO_I) {
        this->rotation++;
        if (this->rotation >= NUM_ROTATIONS[this->type]) {
            this->rotation -= NUM_ROTATIONS[this->type];
        }
    }
    else { // I tetrimino is weird
        if (this->rotation == 0) this->rotation = 3;
        else if (this->rotation == 3) this->rotation = 0;
    }
    
    // Check for collision
    if (_Tetrimino_collision(this, board)) {
        this->rotation = prev_rotation;
        return false;
    }
    
    return true;
}

bool Tetrimino_rotate_ccw(tetrimino_t *this, uint8_t *board) {
    // Rotate clockwise
    uint8_t prev_rotation = this->rotation;
    if (this->type != TETRIMINO_I) {
        if (this->rotation == 0) {
            this->rotation = NUM_ROTATIONS[this->type] - 1;
        }
        else this->rotation--;
    }
    else { // I tetrimino is weird
        if (this->rotation == 0) this->rotation = 3;
        else if (this->rotation == 3) this->rotation = 0;
    }
    
    // Check for collision
    if (_Tetrimino_collision(this, board)) {
        this->rotation = prev_rotation;
        return false;
    }
    
    return true;
}

bool _Tetrimino_collision(tetrimino_t *this, uint8_t *board) {
    for (uint8_t i = 0; i < BLOCKS_IN_TETRIMINO; i++) {
        block_t block = this->blocks[i];
        uint8_t x = Tetrimino_get_block_x(this->rotation, this->x, block);
        uint8_t y = Tetrimino_get_block_y(this->rotation, this->y, block);
        
        if (y == 0xFF) continue; // If above board
        // If left of, right of, or below the board. Or if that space of the
        // board is occupied, return collision
        if (x < 0 || x >= BOARD_COLS || y >= BOARD_ROWS || 
                board[y * BOARD_COLS + x] != WH_) {
            return true;
        }
    }
    
    return false;
}

void Tetrimino_update_board(tetrimino_t *this, uint8_t *board) {
    for (uint8_t i = 0; i < BLOCKS_IN_TETRIMINO; i++) {
        block_t block = this->blocks[i];
        uint8_t x = Tetrimino_get_block_x(this->rotation, this->x, block);
        uint8_t y = Tetrimino_get_block_y(this->rotation, this->y, block);
        
        cell_e cell = block.cell;
        // Tetrimino I has different cells based on rotation
        if (this->type == TETRIMINO_I && this->rotation == 3) cell += 3;
        board[y * BOARD_COLS + x] = cell;
    }
}

uint8_t Tetrimino_get_block_x(uint8_t rotation, uint8_t this_x, block_t block) {
    uint8_t x = this_x;
    switch (rotation) {
        case 0: // No rotation
            x += block.x;
            break;
        case 1: // 90 deg clockwise
            x -= block.y;
            break;
        case 2: // 180 deg clockwise
            x -= block.x;
            break;
        case 3: // 270 deg clockwise
            x += block.y;
            break;
    }
    return x;
}

uint8_t Tetrimino_get_block_y(uint8_t rotation, uint8_t this_y, block_t block) {
    uint8_t y = this_y;
    switch (rotation) {
        case 0: // No rotation
            y += block.y;
            break;
        case 1: // 90 deg clockwise
            y += block.x;
            break;
        case 2: // 180 deg clockwise
            y -= block.y;
            break;
        case 3: // 270 deg clockwise
            y -= block.x;
            break;
    }
    return y;
}