/* 
 * File:   music.c
 * Author: Jacob Malin
 *
 * Created on November 10, 2024, 12:54 AM
 */

#include "music.h"

music_t *Music(PORT_t *port, uint8_t pin) {
    static music_t Music;

    Music.speaker = Output(port, pin);

    return &Music;
}

void Music_tsk(void *pvParams) {
//    music_t *this = (music_t *) pvParams;
    
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(MUSIC_RATE_MS));
    }
}