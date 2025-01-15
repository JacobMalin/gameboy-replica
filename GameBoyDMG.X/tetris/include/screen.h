/* 
 * File:   screen.h
 * Author: Jacob Malin
 *
 * Created on November 14, 2024, 5:37 AM
 */

#ifndef SCREEN_H
#define	SCREEN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "cell.h"
#include "display.h"
#include "sd.h"

    typedef display_row screen_t[DISPLAY_ROWS];

    typedef enum {
        SCREEN_COPYRIGHT,
        SCREEN_TITLE,
        SCREEN_SELECT,
        SCREEN_A_TYPE_SELECT,
        SCREEN_A_TYPE_GAME,
        SCREEN_GAME_OVER,
        SCREEN_PAUSED,
        SCREEN_LOGO,
                
        SCREEN_E_LEN, // Length of enum
    } screen_e;
    
    extern const screen_t Screen_copyright, Screen_title, Screen_select, 
            Screen_a_type_select, Screen_a_type_game, Screen_game_over,
            Screen_paused, Screen_logo, Screen_b_type_game;
    
    /**
     * Loads screens into SD memory.
     * @param sd_t *SD A pointer to the SD object.
     */
    void Screen(sd_t *SD);

    /**
     * Gets a screen from the SD card. If it is the most recent screen, then
     * returns that screen without grabbing it.
     * @param sd_t *SD A pointer to the SD object.
     * @param screen_e index The index of the screen.
     * @return A pointer to the first cell of the screen.
     */
    const cell_e *Screen_get(sd_t *SD, screen_e index);

    /**
     * Writes a screen to the SD card.
     * @param sd_t *SD A pointer to the SD object.
     * @param screen_e index The index of the screen.
     * @param const screen_t screen The screen to write.
     */
    void Screen_set(sd_t *SD, screen_e index, const screen_t screen);

#ifdef	__cplusplus
}
#endif

#endif	/* SCREEN_H */

