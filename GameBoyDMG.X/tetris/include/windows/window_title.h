/* 
 * File:   window_title.h
 * Author: Jacob Malin
 *
 * Created on November 19, 2024, 2:08 PM
 */

#ifndef WINDOW_TITLE_H
#define	WINDOW_TITLE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "window.h"
#include "window_select.h"

#define TITLE_PLAY_ROW 14
#define TITLE_PLAY_ONE_PLAYER_COL 1
#define TITLE_PLAY_TWO_PLAYER_COL 11

    typedef struct {
        bool is_one_player;
    } window_title_t;

    /**
     * Initializes a window for the GameBoy.
     */
    void Window_Title_init(void);

    /**
     * Swaps to the given window.
     * @param window_t *this The window to change.
     */
    void Window_Title(window_t *this);

    /**
     * Renders the window for the first time.
     * @param window_t *this A pointer to the window object.
     */
    void Window_Title_initial_render(window_t *this);

    /**
     * Handles a button press.
     * @param window_t **this A double pointer to the window object.
     * @param buttons_cmd button The button and its edge.
     */
    void Window_Title_button_handle(window_t **this, buttons_cmd button);

    /**
     * Renders updates to the window.
     * @param window_t *this A pointer to the window object.
     */
    void Window_Title_render_handle(window_t *this);

#ifdef	__cplusplus
}
#endif

#endif	/* WINDOW_TITLE_H */

