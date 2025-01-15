/* 
 * File:   buttons.h
 * Author: Jacob Malin
 *
 * Created on October 31, 2024, 1:22 PM
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/io.h>
    
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
    
#include "button.h"
#include "extender.h"
#include "random.h"
    
#define EXT_ADDR 0b0100000 // Address of the GPIO extender
#define BUTTONS_POLL_RATE 50 // In ms

    typedef enum {
        BTN_UP,
        BTN_DOWN,
        BTN_LEFT,
        BTN_RIGHT,
        BTN_A,
        BTN_B,
        BTN_START,
        BTN_SELECT,
        BTN_SIZE, // Size of enum
    } buttons_e;
    
    typedef struct {
        buttons_e button : 4;
        button_edge_t edge : 2;
    } buttons_cmd;

    typedef struct {
        button_t *buttons[BTN_SIZE]; // In order of buttons_e
        QueueHandle_t queue;
        extender_t *extender;
    } buttons_t;

    /**
     * Initializes the buttons used in the GameBoy. This includes the d-pad (up,
     * down, left, right), A, B, start, and select.
     * @param spi_t *SPI An SPI object.
     * @param PORT_t *cs_port The CS port for SPI.
     * @param uint8_t cs_pin The CS pin for SPI.
     * @return Returns a buttons_t pointer.
     */
    buttons_t *Buttons(spi_t *SPI, PORT_t *cs_port, uint8_t cs_pin);

    /**
     * The main task loop for the buttons. Adds a button to the queue on key up.
     * @param void *pvParams A pointer to the buttons object.
     */
    void Buttons_tsk(void *pvParams);

    /**
     * Returns the queue that holds button inputs.
     * @param buttons_t *this A pointer to the buttons object.
     * @returns A pointer to the button queue.
     */
    QueueHandle_t Buttons_get_queue(buttons_t * this);

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

