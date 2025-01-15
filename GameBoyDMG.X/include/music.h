/* 
 * File:   music.h
 * Author: Jacob Malin
 *
 * Created on November 10, 2024, 12:54 AM
 */

#ifndef MUSIC_H
#define	MUSIC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <avr/io.h>
    
#include "FreeRTOS.h"
#include "task.h"
    
#include "output.h"
    
#define MUSIC_RATE_MS 16 // In milliseconds. 16ms is 62.5fps

    typedef struct {
        output_t *speaker;
    } music_t;

    /**
     * Initializes the music for the GameBoy.
     * @param PORT_t *port The port of the speaker.
     * @param uint8_t pin The pin of the speaker.
     * @return Returns a music_t pointer.
     */
    music_t *Music(PORT_t *port, uint8_t pin);

    /**
     * The main task loop for the music.
     */
    void Music_tsk(void *pvParams);

#ifdef	__cplusplus
}
#endif

#endif	/* MUSIC_H */

