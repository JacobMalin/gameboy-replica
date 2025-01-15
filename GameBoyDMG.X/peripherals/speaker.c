
/*
 * File:   speaker.c
 * Author: Jacob Malin
 *
 * Created on October 12, 2024, 7:43 PM
 */

#include "speaker.h"

speaker_t *Speaker(PORT_t *port, uint8_t pin) {
    static speaker_t Speaker;

    Speaker.PORT = Output(port, pin);

    return &Speaker;
}

void Speaker_SET(speaker_t *this) {
    Output_SET(this->PORT);
}

void Speaker_CLR(speaker_t *this) {
    Output_CLR(this->PORT);
}

void Speaker_TGL(speaker_t *this) {
    Output_TGL(this->PORT);
}