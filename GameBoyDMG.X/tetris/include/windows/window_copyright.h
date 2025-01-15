/* 
 * File:   window_copyright.h
 * Author: Jacob Malin
 *
 * Created on November 24, 2024, 6:19 AM
 */

#ifndef WINDOW_COPYRIGHT_H
#define	WINDOW_COPYRIGHT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "window.h"
#include "window_title.h"
    
#define COPYRIGHT_TRANSITION_WAIT 60*5 // In frames (about 5 seconds)
    
    /**
     * Initializes a window for the GameBoy.
     */
    void Window_Copyright_init(void);

    /**
     * Swaps to the given window.
     * @param window_t *this The window to change.
     */
    void Window_Copyright(window_t *this);

    /**
     * Renders the window for the first time.
     * @param window_t *this A pointer to the window object.
     */
    void Window_Copyright_initial_render(window_t *this);

    /**
     * Handles a button press.
     * @param window_t **this A double pointer to the window object.
     * @param buttons_cmd button The button and its edge.
     */
    void Window_Copyright_button_handle(window_t * * this, buttons_cmd button);

    /**
     * Renders updates to the window.
     * @param window_t *this A pointer to the window object.
     */
    void Window_Copyright_render_handle(window_t * this);

#ifdef	__cplusplus
}
#endif

#endif	/* WINDOW_COPYRIGHT_H */

