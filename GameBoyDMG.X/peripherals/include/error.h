/* 
 * File:   error.h
 * Author: Jacob Malin
 *
 * Created on November 13, 2024, 8:17 PM
 */

#ifndef ERROR_H
#define	ERROR_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifndef F_CPU
#define F_CPU 20000000
#endif

#include <avr/io.h>
    
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
    
#include "printf.h"

#define SAMPLES_PER_BIT 16
#define USART2_BAUD_VALUE(BAUD_RATE) (uint16_t) ((F_CPU << 6) / (((float) SAMPLES_PER_BIT) * (BAUD_RATE)) + 0.5)

    /**
     * Initializes the error and data LEDs.
     */
    void Error(void);

    /**
     * Turns on the error LED.
     */
    void Error_SET(void);

    /**
     * Turns off the error LED.
     */
    void Error_CLR(void);

    /**
     * Toggles the error LED.
     */
    void Error_TGL(void);

    /**
     * Turns on the data LED.
     */
    void Error_data_SET(void);

    /**
     * Turns off the data LED.
     */
    void Error_data_CLR(void);

    /**
     * Toggles the data LED.
     */
    void Error_data_TGL(void);
    
    /**
     * Initializes USART.
     */
    void USART(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ERROR_H */

