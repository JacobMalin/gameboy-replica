/* 
 * File:   tetris.h
 * Author: Jacob Malin
 *
 * Created on November 10, 2024, 10:05 PM
 */

#ifndef TETRIS_H
#define	TETRIS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/io.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "buttons.h"
#include "sd.h"
#include "display.h"
#include "window.h"
#include "window_logo.h"

#define FRAME_PERIOD_MS 16 // In milliseconds. 16ms is 62.5fps

    typedef struct {
        sd_t *SD;
        display_t *Display;
        QueueHandle_t buttons_queue;
    } tetris_t;

    /**
     * Initializes Tetris.
     * @param st_t *SD The SD object.
     * @param display_t *Display The display object.
     * @param buttons_t *Buttons The buttons object.
     * @return Returns a tetris_t pointer.
     */
    tetris_t *Tetris(sd_t *SD, display_t *Display, buttons_t *Buttons);

    /**
     * The main game loop for tetris.
     * @param void *pvParams A pointer to the tetris object.
     */
    void Tetris_tsk(void *pvParams);

#ifdef	__cplusplus
}
#endif

#endif	/* TETRIS_H */

