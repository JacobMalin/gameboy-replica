/* 
 * File:   speaker.h
 * Author: Jacob Malin
 *
 * Created on October 12, 2024, 7:42 PM
 */

#ifndef SPEAKER_H
#define	SPEAKER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/io.h>

#include "output.h"

    typedef struct {
        output_t *PORT;
    } speaker_t;

    /**
     * Initializes a speaker.
     * @param PORT_t *port The port register.
     * @param uint8_t pin The pin number.
     * @return Returns an speaker_t pointer.
     */
    speaker_t *Speaker(PORT_t *port, uint8_t pin);

    /**
     * Sets the output bit to 1.
     * @param output_t *this A pointer to the speaker object.
     */
    void Speaker_SET(speaker_t * this);

    /**
     * Sets the output bit to 0.
     * @param output_t *this A pointer to the speaker object.
     */
    void Speaker_CLR(speaker_t * this);

    /**
     * Toggles the output bit.
     * @param output_t *this A pointer to the speaker object.
     */
    void Speaker_TGL(speaker_t * this);

#ifdef	__cplusplus
}
#endif

#endif	/* SPEAKER_H */