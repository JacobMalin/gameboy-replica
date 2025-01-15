/* 
 * File:   tetrimino.h
 * Author: Jacob Malin
 *
 * Created on December 3, 2024, 9:02 PM
 */

#ifndef TETRIMINO_H
#define	TETRIMINO_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <avr/io.h>
    
#include "display.h"
    
#define BLOCKS_IN_TETRIMINO 4
#define BOARD_OFFSET_X 2 // In cells
    
#define BOARD_ROWS 18
#define BOARD_COLS 10
    
#define PREVIEW_OFFSET_X 16 // In cells
#define PREVIEW_OFFSET_Y 14 // In cells
    
    typedef enum {
        TETRIMINO_L,
        TETRIMINO_J,
        TETRIMINO_I,
        TETRIMINO_O,
        TETRIMINO_Z,
        TETRIMINO_S,
        TETRIMINO_T,
        TETRIMINO_COUNT,
    } tetrimino_e;
    
    typedef struct {
        int8_t x : 3; // Relative position from center of rotation
        int8_t y : 3; // Relative position from center of rotation
        cell_e cell : 9;
    } block_t;

    typedef struct {
        tetrimino_e type;
        uint8_t x : 5; // Center of rotation (from the top left of the board)
        uint8_t y : 5; // Center of rotation (from the top left of the board)
        block_t blocks[BLOCKS_IN_TETRIMINO];
        uint8_t rotation : 2; // Clockwise
        
        uint8_t last_render_x : 5;
        uint8_t last_render_y : 5;
        uint8_t last_rotation : 2;
    } tetrimino_t;

    /**
     * Initializes a tetrimino.
     * @param display_t *display The display to render to.
     * @param tetrimino_e type The tetrimino type.
     * @param uint8_t x The starting horizontal center of rotation.
     * @param uint8_t x The starting vertical center of rotation.
     * @return Returns an tetrimino_t pointer.
     */
    tetrimino_t *Tetrimino(tetrimino_e type, uint8_t x, uint8_t y);

    /**
     * Frees a tetrimino.
     * @param tetrimino_t *this The tetrimino object.
     */
    void Tetrimino_free(tetrimino_t *this);

    /**
     * Modifies a row to include a tetrimino.
     * @param tetrimino_t *this The tetrimino object.
     * @param display_row row The row to edit.
     * @param uint8_t row_num The index of the row.
     */
    void Tetrimino_initial_render(tetrimino_t *this, display_row row, 
        uint8_t row_num);
    
    /**
     * Writes a tetrimino to the display for the first time.
     * @param tetrimino_t *this The tetrimino object.
     * @param display_t *display The display to render to.
     */
    void Tetrimino_initial_display(tetrimino_t *this, display_t *display);

    /**
     * Modifies a row to include a tetrimino in the preview area.
     * @param tetrimino_t *this The tetrimino object.
     * @param display_row row The row to edit.
     * @param uint8_t row_num The index of the row.
     */
    void Tetrimino_initial_preview(tetrimino_t *this, display_row row, 
        uint8_t row_num);

    /**
     * Writes a tetrimino to the display. Replaces previous position with WH_.
     * @param tetrimino_t *this The tetrimino object.
     * @param display_t *display The display to render to.
     */
    void Tetrimino_display(tetrimino_t *this, display_t *display);

    /**
     * Writes a tetrimino to the preview area.
     * @param tetrimino_t *this The tetrimino object.
     * @param display_t *display The display to render to.
     */
    void Tetrimino_preview(tetrimino_t *this, display_t *display);

    /**
     * Writes white squares in place of the tetrimino.
     * @param tetrimino_t *this The tetrimino object.
     * @param display_t *display The display to render to.
     */
    void _Tetrimino_undisplay(tetrimino_t *this, display_t *display);

    /**
     * Writes white squares in place of the tetrimino in the preview area.
     * @param tetrimino_t *this The tetrimino object.
     * @param display_t *display The display to render to.
     */
    void Tetrimino_unpreview(tetrimino_t *this, display_t *display);

    /**
     * Moves down the tetrimino. If the tetrimino could not be moved, false is 
     * returned.
     * @param tetrimino_t *this The tetrimino object.
     * @param cell_e *board The board state. This is used to check for 
     * collision.
     * @return True on success, false if collision.
     */
    bool Tetrimino_move_down(tetrimino_t *this, uint8_t *board);

    /**
     * Moves the tetrimino left. If the tetrimino could not be moved, false is 
     * returned.
     * @param tetrimino_t *this The tetrimino object.
     * @param cell_e *board The board state. This is used to check for 
     * collision.
     * @return True on success, false if collision.
     */
    bool Tetrimino_move_left(tetrimino_t *this, uint8_t *board);

    /**
     * Moves the tetrimino right. If the tetrimino could not be moved, false is 
     * returned.
     * @param tetrimino_t *this The tetrimino object.
     * @param cell_e *board The board state. This is used to check for 
     * collision.
     * @return True on success, false if collision.
     */
    bool Tetrimino_move_right(tetrimino_t *this, uint8_t *board);

    /**
     * Rotates the tetrimino clockwise. If the tetrimino could not be rotated, 
     * false is returned.
     * @param tetrimino_t *this The tetrimino object.
     * @param cell_e *board The board state. This is used to check for 
     * collision.
     * @return True on success, false if collision.
     */
    bool Tetrimino_rotate_cw(tetrimino_t *this, uint8_t *board);

    /**
     * Rotates the tetrimino counter-clockwise. If the tetrimino could not be 
     * rotated, false is returned.
     * @param tetrimino_t *this The tetrimino object.
     * @param cell_e *board The board state. This is used to check for 
     * collision.
     * @return True on success, false if collision.
     */
    bool Tetrimino_rotate_ccw(tetrimino_t *this, uint8_t *board);

    /**
     * Check for collision with board state and edges of board (not including 
     * the top).
     * @param tetrimino_t *this The tetrimino object.
     * @param cell_e *board The board state.
     * @return True on collision, false if safe.
     */
    bool _Tetrimino_collision(tetrimino_t *this, uint8_t *board);

    /**
     * Update board with final tetrimino position.
     * @param tetrimino_t *this The tetrimino object.
     * @param uint8_t *board The board state.
     */
    void Tetrimino_update_board(tetrimino_t *this, uint8_t *board);

    /**
     * Gets the x position of a block, accounting for rotation.
     * @param uint8_t rotation The rotation of the tetrimino.
     * @param uint8_t this_x The x position of the center.
     * @param block_t block The block of the tetrimino.
     */
    uint8_t Tetrimino_get_block_x(uint8_t rotation, uint8_t this_x, 
        block_t block);

    /**
     * Gets the y position of a block, accounting for rotation.
     * @param uint8_t rotation The rotation of the tetrimino.
     * @param uint8_t this_y The y position of the center.
     * @param block_t block The block of the tetrimino.
     */
    uint8_t Tetrimino_get_block_y(uint8_t rotation, uint8_t this_y, 
        block_t block);

#ifdef	__cplusplus
}
#endif

#endif	/* TETRIMINO_H */

