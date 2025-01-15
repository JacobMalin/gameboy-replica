/* 
 * File:   window_select.h
 * Author: Jacob Malin
 *
 * Created on November 24, 2024, 6:19 AM
 */

#ifndef WINDOW_SELECT_H
#define	WINDOW_SELECT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "window.h"
#include "window_a_type_select.h"
    
#define SELECT_BLACK_LEN 6 // Cells in "A-TYPE", "B-TYPE", etc.

#define SELECT_GAME_ROW 5
#define SELECT_MUSIC_ROW_1 12
#define SELECT_MUSIC_ROW_2 14
#define SELECT_LEFT_COL 3
#define SELECT_RIGHT_COL 11
    
    typedef enum {
        MUSIC_A,
        MUSIC_B,
        MUSIC_C,
        MUSIC_OFF,
    } __attribute__((__packed__)) music_type_e;

    typedef struct {
        bool select_game : 1; // False if music selection
        bool is_a_type : 1;
        music_type_e music_type : 2;
    } window_select_t;
    
    typedef enum {
        TEXT_GAME_A,
        TEXT_GAME_B,
        TEXT_MUSIC_A,
        TEXT_MUSIC_B,
        TEXT_MUSIC_C,
        TEXT_MUSIC_OFF,
    } text_e;
    
    typedef uint8_t text_t; // bitfield that follows the text_e enum
    
    /**
     * Initializes a window for the GameBoy.
     */
    void Window_Select_init(void);

    /**
     * Swaps to the given window.
     * @param window_t *this The window to change.
     */
    void Window_Select(window_t *this);

    /**
     * Renders the window for the first time.
     * @param window_t *this A pointer to the window object.
     */
    void Window_Select_initial_render(window_t * this);

    /**
     * Handles a button press.
     * @param window_t **this A double pointer to the window object.
     * @param buttons_cmd button The button and its edge.
     */
    void Window_Select_button_handle(window_t * * this, buttons_cmd button);

    /**
     * Renders updates to the window.
     * @param window_t *this A pointer to the window object.
     */
    void Window_Select_render_handle(window_t * this);

    /**
     * Sets the color of text.
     * @param window_t *this A pointer to the window object.
     * @param text_t is_black The black values.
     * @param uint8_t bit The bit position in the is_black enum.
     * @param uint8_t row The row index.
     * @param uint8_t col The column index.
     * @param const cell_e *black The black text.
     * @param const cell_e *gray The gray text.
     */
    void _Window_Select_set_color(window_t *this, text_t is_black, uint8_t bit, 
        uint8_t row, uint8_t col, const cell_e *black, const cell_e *gray);



#ifdef	__cplusplus
}
#endif

#endif	/* WINDOW_SELECT_H */

