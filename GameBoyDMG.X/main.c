/*
 * File:   main.c
 * Author: Jacob Malin
 *
 * Created on October 27, 2024, 7:12 AM
 */

#ifndef F_CPU
#define F_CPU 20000000 // Speed is increased to allow for fast SPI (20MHz)
#endif

#include <avr/io.h>

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"

/* Project includes */
#include "error.h"
#include "spi.h"
#include "sd.h"
#include "display.h"
#include "buttons.h"
#include "tetris.h"

spi_t *spi;
sd_t *sd;
display_t *display;
buttons_t *buttons;

tetris_t *tetris;


void init(void) {
    Error();

    // Set clock speed to undivided (20MHz)
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, 0);

    spi = SPI(
        &PORTA, 4, // SDI
        &PORTA, 5, // SDO
        &PORTA, 6 // SCK
    );
    
    Random();
    
    sd = SD(
        spi,
        &PORTD, 6 // CS
    );
    display = Display(
        sd, 
        spi, 
        &PORTD, 5, // CS
        &PORTD, 7  // Data/command select
    );
    buttons = Buttons(
        spi, 
        &PORTA, 7 // CS
    );

    tetris = Tetris(sd, display, buttons);
}

int main(void) {
    // Initialize
    init();

    // Create tasks
    xTaskCreate(Buttons_tsk, "buttons", 0x130, (void *) buttons, 0, NULL);
    xTaskCreate(Tetris_tsk,  "tetris",  0x160, (void *) tetris,  0, NULL);

    // Run tasks
    vTaskStartScheduler();

    return 0;
}
