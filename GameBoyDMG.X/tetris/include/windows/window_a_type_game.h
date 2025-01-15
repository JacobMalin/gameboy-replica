/* 
 * File:   window_a_type_game.h
 * Author: Jacob Malin
 *
 * Created on November 24, 2024, 6:19 AM
 */

#ifndef WINDOW_A_TYPE_GAME_H
#define	WINDOW_A_TYPE_GAME_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "window.h"
#include "tetrimino.h"
#include "window_game_over.h"
#include "window_a_type_select.h"

#define HIGH_SCORE_ROW        3
#define HIGH_SCORE_RIGHT_COL 18
#define HIGH_SCORE_LEN        6
#define LEVEL_ROW             7
#define LEVEL_RIGHT_COL      17
#define LINES_ROW            10
#define LINES_RIGHT_COL      17

#define BOARD_ROWS 18
#define BOARD_COLS 10

#define BOARD_SPAWN_X 4
#define BOARD_SPAWN_Y 1

#define DAS_DELAY      24 // Delay before DAS properly kicks in (in frames)
#define HALF_DAS_DELAY 10 // When hold l/r starting during pause (in frames)
#define DAS_SPEED       9 // Interval between DAS activations (in frames)
#define SOFT_GRAVITY    3 // Speed of piece drop when soft dropping (in frames)
    
#define MAX_LEVEL 20
#define LINES_PER_LEVEL 10
#define LINE_CLEAR_ANIMATION_SPEED 8 // In frames

    // Forward declaration
    window_change_t Window_Game;

    typedef uint8_t board_t[BOARD_ROWS][BOARD_COLS];

    typedef struct {
        uint8_t level;
        uint16_t lines;
        uint32_t score;
        bool is_paused;
    } window_a_type_game_t;

    /**
     * Initializes a window for the GameBoy.
     */
    void Window_A_Type_Game_init(void);

    /**
     * Swaps to the given window.
     * @param window_t *this The window to change.
     */
    void Window_A_Type_Game(window_t * this);

    /**
     * Renders the window for the first time.
     * @param window_t *this A pointer to the window object.
     */
    void Window_A_Type_Game_initial_render(window_t * this);

    /**
     * Handles a button press.
     * @param window_t **this A double pointer to the window object.
     * @param buttons_cmd button The button and its edge.
     */
    void Window_A_Type_Game_button_handle(window_t **this,
            buttons_cmd button);

    /**
     * Renders updates to the window.
     * @param window_t *this A pointer to the window object.
     */
    void Window_A_Type_Game_render_handle(window_t * this);

    /**
     * The normal game loop when not paused nor in the line clear animation.
     * Toggles preview, computes DAS, applies gravity to the current piece, and
     * then renders to the display.
     * @param window_t *this A pointer to the window object.
     */
    void _WATG_normal_game_loop(window_t *this);

    /**
     * Updates the starting level.
     * @param uint8_t level The new starting level.
     */
    void Window_A_Type_Game_set_level(uint8_t level);

    /**
     * Renders the score to the screen.
     * @param window_t *this A pointer to the window object.
     */
    void Window_A_Type_Game_render_score(window_t * this);

    /**
     * Renders the level to the screen.
     * @param window_t *this A pointer to the window object.
     */
    void Window_A_Type_Game_render_level(window_t * this);

    /**
     * Renders the lines to the screen.
     * @param window_t *this A pointer to the window object.
     */
    void Window_A_Type_Game_render_lines(window_t * this);

    /**
     * Generates a new tetrimino.
     * @param window_t *this A pointer to the window object.
     */
    void _WATG_new_tetrimino(window_t *this);

    /**
     * Places the current piece in the graveyard and generates a new one.
     * @param tetrimino_t *tetri A pointer to a tetrimino.
     * @param uint8_t *board The board state.
     * @returns A bitfield from row 0 to BOARD_ROWS where a 1 is a full line.
     */
    uint32_t _WATG_check_line_clear(tetrimino_t *tetri, uint8_t *board);

    /**
     * Clears the relevant lines and moves the other lines down. Updates the
     * display.
     * @param window_t *this A pointer to the window object.
     * @param uint32_t line_check What lines are full.
     * @param uint8_t *board The board state.
     */
    void _WATG_line_clear_down(window_t *this, uint32_t line_check, 
            uint8_t *board);

    /**
     * Renders the lines to be cleared as gray.
     * @param window_t *this A pointer to the window object.
     * @param uint32_t line_check What lines are full.
     */
    void _WATG_line_clear_gray(window_t *this, uint32_t line_check);

    /**
     * Renders the lines to be cleared as blocks.
     * @param window_t *this A pointer to the window object.
     * @param uint32_t line_check What lines are full.
     * @param uint8_t *board The board state.
     */
    void _WATG_line_clear_render(window_t *this, uint32_t line_check, 
            uint8_t *board);

    /**
     * Renders the lines to be cleared as white.
     * @param window_t *this A pointer to the window object.
     * @param uint32_t line_check What lines are full.
     */
    void _WATG_line_clear_white(window_t *this, uint32_t line_check);

#ifdef	__cplusplus
}
#endif

#endif	/* WINDOW_A_TYPE_GAME_H */

