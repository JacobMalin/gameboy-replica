/* 
 * File:   buttons.c
 * Author: Jacob Malin
 *
 * Created on October 31, 2024, 1:22 PM
 */

#include "buttons.h"

const uint8_t button_pins[BTN_SIZE] = {
    1, 3, 0, 2, // d-pad (up, down, left, right)
    7, 6, 5, 4, // a, b, start, select
};

buttons_t *Buttons(spi_t *SPI, PORT_t *cs_port, uint8_t cs_pin) {
    static buttons_t Buttons;

    // GPIO
    Buttons.extender = Extender(SPI, cs_port, cs_pin, EXT_ADDR);
    for (buttons_e i = 0; i < BTN_SIZE; i++) {
        Buttons.buttons[i] = Button(Buttons.extender, button_pins[i], true);
    }

    // Queue
    Buttons.queue = xQueueCreate(10, sizeof(buttons_cmd));

    return &Buttons;
}

void Buttons_tsk(void *pvParams) {
    buttons_t *this = (buttons_t *)pvParams;

    while (1) {
        Extender_poll(this->extender); // Reads button state
        
        for (buttons_e i = 0; i < BTN_SIZE; i++) {
            button_edge_t edge = Button_get_edge(this->buttons[i]);
            if (edge != KEY_UNCHANGED) { // If button state changed
                buttons_cmd cmd = {
                    .button = i,
                    .edge = edge,
                };
                
                xQueueSendToBack(this->queue, &cmd, 0);
                
                // Add randomness on each button push
                Random_add_random();
            }
        }
        
        vTaskDelay(pdMS_TO_TICKS(BUTTONS_POLL_RATE));
    }
}

QueueHandle_t Buttons_get_queue(buttons_t * this) {
    return this->queue;
}