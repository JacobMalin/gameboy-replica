/* 
 * File:   window_logo.h
 * Author: Jacob Malin
 *
 * Created on November 24, 2024, 6:19 AM
 */

#ifndef WINDOW_LOGO_H
#define	WINDOW_LOGO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "window.h"
#include "window_copyright.h"
    
#define LOGO_WAIT_BEFORE 30 // In frames (60 = 1s)
#define LOGO_STEP_TIME   13 // In frames (60 = 1s)
#define LOGO_TOTAL_STEPS 10 // In cells
#define LOGO_WAIT_AFTER  120 // In frames (60 = 1s)
#define LOGO_TRANSITION_WAIT LOGO_STEP_TIME*LOGO_TOTAL_STEPS

#define LOGO_OFFSET_X 4
#define LOGO_OFFSET_Y 7
#define LOGO_ROWS     3
#define LOGO_COLS     13
    
    /**
     * Initializes a window for the GameBoy.
     */
    void Window_Logo_init(void);

    /**
     * Swaps to the given window.
     * @param window_t *this The window to change.
     */
    void Window_Logo(window_t *this);

    /**
     * Renders the window for the first time.
     * @param window_t *this A pointer to the window object.
     */
    void Window_Logo_initial_render(window_t *this);

    /**
     * Handles a button press.
     * @param window_t **this A double pointer to the window object.
     * @param buttons_cmd button The button and its edge.
     */
    void Window_Logo_button_handle(window_t * * this, buttons_cmd button);

    /**
     * Renders updates to the window.
     * @param window_t *this A pointer to the window object.
     */
    void Window_Logo_render_handle(window_t * this);

#ifdef	__cplusplus
}
#endif

#endif	/* WINDOW_LOGO_H */

