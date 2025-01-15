/* 
 * File:   tetris.c
 * Author: Jacob Malin
 *
 * Created on November 10, 2024, 10:05 PM
 */

#include "tetris.h"

tetris_t *Tetris(sd_t *SD, display_t *Display, buttons_t *Buttons) {
    static tetris_t Tetris;

    Tetris.SD = SD;
    Tetris.Display = Display;
    Tetris.buttons_queue = Buttons_get_queue(Buttons);

    return &Tetris;
}

void Tetris_tsk(void *pvParams) {
    tetris_t *this = (tetris_t *) pvParams;
    window_t *current = Window(this->SD, this->Display);
    
    Window_set(current, &Window_Logo); // First window is the N*ntendo logo
    
    while (1) {
        // Grab and handle button input
        buttons_cmd cmd;
        // Reads all button inputs received in the span of a frame
        while (xQueueReceive(this->buttons_queue, &cmd, 0)) {
            Window_handle_button(&current, cmd);
        }
        
        Window_render(current);
        
        // Wait
        vTaskDelay(pdMS_TO_TICKS(FRAME_PERIOD_MS));
    }
}