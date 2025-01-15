/* 
 * File:   error.c
 * Author: Jacob Malin
 *
 * Created on November 13, 2024, 8:17 PM
 */

#include "error.h"

static SemaphoreHandle_t blockUSART;

void Error(void) {
    USART();
    blockUSART = xSemaphoreCreateMutex();

    PORTF.DIRSET = PIN5_bm; // Error LED
    PORTF.DIRSET = PIN4_bm; // Data LED

    Error_CLR();
    Error_data_CLR();
}

void Error_SET(void) {
    PORTF.OUTCLR = PIN5_bm;
}

void Error_CLR(void) {
    PORTF.OUTSET = PIN5_bm;
}

void Error_TGL(void) {
    PORTF.OUTTGL = PIN5_bm;
}

void Error_data_SET(void) {
    PORTF.OUTCLR = PIN4_bm;
}

void Error_data_CLR(void) {
    PORTF.OUTSET = PIN4_bm;
}

void Error_data_TGL(void) {
    PORTF.OUTTGL = PIN4_bm;
}

void USART(void) {
    /* Set TX pin as output and RX pin as input */
    PORTF.DIRSET = PIN0_bm;
    PORTF.DIRCLR = PIN1_bm;

    /* Set Baud rate */
    USART2.BAUD = (uint16_t) USART2_BAUD_VALUE(9600);

    /* Enable transmission for USART2 */
    USART2.CTRLB |= USART_TXEN_bm;
}

void _putchar(char c) {
    while (!(USART2.STATUS & USART_DREIF_bm));
    USART2.TXDATAL = c;
}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName ) {
    Error_SET();
}