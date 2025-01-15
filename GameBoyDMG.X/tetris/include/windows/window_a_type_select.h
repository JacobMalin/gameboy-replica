/* 
 * File:   window_a_type_select.h
 * Author: Jacob Malin
 *
 * Created on November 24, 2024, 6:19 AM
 */

#ifndef WINDOW_A_TYPE_SELECT_H
#define	WINDOW_A_TYPE_SELECT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "window.h"
#include "window_a_type_game.h"
    
#define DOT_LEN 6 // Length of name or score
#define SCORES_PER_LEVEL 3
#define NUM_LEVELS 10
#define NUM_LEVELS_HALF NUM_LEVELS/2
#define NO_SCORE 0

#define SELECT_LEVEL_ROW_1 6
#define SELECT_LEVEL_ROW_2 8
#define HIGH_SCORE_ROW_1   13
#define SELECT_LEVEL_COL_1 5
#define HIGH_SCORE_COL_1   4
#define HIGH_SCORE_COL_2   12
    
    // Forward declaration
    window_change_t Window_Select;
    
    typedef struct {
        char name[DOT_LEN];
        uint32_t score;
    } score_t;
    typedef score_t level_score[SCORES_PER_LEVEL];

    typedef struct {
        uint8_t level : 5;
        uint8_t score_entry : 2; // Which score is being edited
        level_score scores[NUM_LEVELS];
        
        uint8_t char_index : 3; // Which char is being edited
        char sel_char : 7; // The character that is blinking (being edited)
    } window_a_type_select_t;
    
    /**
     * Initializes a window for the GameBoy.
     */
    void Window_A_Type_Select_init(void);

    /**
     * Swaps to the given window.
     * @param window_t *this The window to change.
     */
    void Window_A_Type_Select(window_t *this);

    /**
     * Renders the window for the first time.
     * @param window_t *this A pointer to the window object.
     */
    void Window_A_Type_Select_initial_render(window_t * this);

    /**
     * Handles a button press.
     * @param window_t **this A double pointer to the window object.
     * @param buttons_cmd button The button and its edge.
     */
    void Window_A_Type_Select_button_handle(window_t **this, 
            buttons_cmd button);

    /**
     * Renders updates to the window.
     * @param window_t *this A pointer to the window object.
     */
    void Window_A_Type_Select_render_handle(window_t * this);

    /**
     * Fills a buffer with the score and dots.
     * @param cell_e buf[] The output buffer.
     * @param uint32_t score The score.
     */
    void Window_A_Type_Select_score_to_buffer(cell_e buf[], uint32_t score);

    /**
     * Fills a buffer with a name and dots.
     * @param cell_e buf[] The output buffer.
     * @param char name[DOT_LEN] The name.
     */
    void Window_A_Type_Select_name_to_buffer(cell_e buf[], char name[DOT_LEN]);

    /**
     * Converts a char to a cell_e.
     * @param char c The char to convert.
     * @return The equivalent cell.
     */
    cell_e _WATS_char_to_cell(char c);

    /**
     * Enters a new score. If it is better than the leader board, it keeps the
     * score.
     * @param uint32_t new_score The new score that was achieved.
     */
    void Window_A_Type_Select_new_score(uint32_t new_score);



#ifdef	__cplusplus
}
#endif

#endif	/* WINDOW_A_TYPE_SELECT_H */

