/* 
 * File:   window_game_over.h
 * Author: Jacob Malin
 *
 * Created on November 24, 2024, 6:19 AM
 */

#ifndef WINDOW_GAME_OVER_H
#define	WINDOW_GAME_OVER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "window.h"
#include "window_a_type_select.h"
    
#define TRANSITION_SPEED 1 // In frames
#define TRANSITION_WAIT 60 // In frames (about 1 second)
    
#define BOARD_OFFSET 2
#define BOARD_COLS 10
    
    /**
     * Initializes a window for the GameBoy.
     */
    void Window_Game_Over_init(void);

    /**
     * Swaps to the given window.
     * @param window_t *this The window to change.
     */
    void Window_Game_Over(window_t *this);

    /**
     * Handles a button press.
     * @param window_t **this A double pointer to the window object.
     * @param buttons_cmd button The button and its edge.
     */
    void Window_Game_Over_button_handle(window_t * * this, buttons_cmd button);

    /**
     * Renders updates to the window.
     * @param window_t *this A pointer to the window object.
     */
    void Window_Game_Over_render_handle(window_t * this);

#ifdef	__cplusplus
}
#endif

#endif	/* WINDOW_GAME_OVER_H */

