/* 
 * File:   window.h
 * Author: Jacob Malin
 *
 * Created on November 19, 2024, 1:44 PM
 */

#ifndef WINDOW_H
#define	WINDOW_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "FreeRTOS.h"

#include "screen.h"
#include "buttons.h"
#include "display.h"
    
#define BLINK_RATE 16 // Every 16 frames, change blink mode; Used for selection.
    
    // Forward declaration
    void Window_Logo_init(void);
    void Window_Copyright_init(void);
    void Window_Title_init(void);
    void Window_Select_init(void);
    void Window_A_Type_Select_init(void);
    void Window_A_Type_Game_init(void);
    void Window_Game_Over_init(void);

    typedef struct window_st window_t;

    typedef void (button_handler_t) (window_t **this, buttons_cmd button);
    typedef void (render_handler_t) (window_t *this);

    struct window_st {
        sd_t *SD;
        display_t *Display;
        button_handler_t *button_handler;
        render_handler_t *render_handler;
        
        bool is_blink_black; // If false, grey
        uint8_t blink_count;
    };

    typedef void (window_change_t) (window_t * this);

    /**
     * Initializes a window for the GameBoy. This window is unusable until set
     * with Window_set.
     * @param sd_t *SD A pointer to the sd object.
     * @param display_t *Display A pointer to the display object.
     * @return Returns a window_t pointer.
     */
    window_t *Window(sd_t *SD, display_t *Display);

    /**
     * Changes to a new window.
     * @param window_t *this A pointer to the window object.
     * @param window_init_t *init A window initialization function.
     */
    void Window_set(window_t * this, window_change_t *change);

    /**
     * Handles a button press.
     * @param window_t **this A double pointer to the window object.
     * @param buttons_cmd button The button and its edge.
     */
    void Window_handle_button(window_t * * this, buttons_cmd button);

    /**
     * Renders the window.
     * @param window_t *this A pointer to the window object.
     * to render.
     */
    void Window_render(window_t * this);

    /**
     * Copies a short array into a row.
     * @param display_row row The row to modify.
     * @param uint8_t start_col The column of the first cell.
     * @param uint8_t num_cells The number of cells to copy.
     * @param const cell_e copy[] The cells to copy.
     */
    void _Window_replace_range(display_row row, uint8_t start_col,
            uint8_t num_cells, const cell_e copy[]);

    /**
     * Writes a selection of cells.
     * @param window_t *this A pointer to the window object.
     * @param uint8_t row_num The row index.
     * @param uint8_t start_col The column of the first cell.
     * @param uint8_t num_cells The number of cells to copy.
     * @param const cell_e copy[] The cells to copy.
     */
    void _Window_write_range(window_t * this, uint8_t row_num,
            uint8_t start_col, uint8_t num_cells, const cell_e copy[]);

#ifdef	__cplusplus
}
#endif

#endif	/* WINDOW_H */

