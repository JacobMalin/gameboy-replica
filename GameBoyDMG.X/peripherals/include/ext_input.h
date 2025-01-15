/* 
 * File:   ext_input.h
 * Author: Jacob Malin
 *
 * Created on November 16, 2024, 9:52 PM
 */

#ifndef EXT_INPUT_H
#define	EXT_INPUT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "input.h"
#include "extender.h"

    /**
     * Initializes an GPIO extender input pin.
     * @param extender_t *extender The GPIO extender.
     * @param uint8_t pin The pin number.
     * @param bool do_pull_up If the pull up resistor should be enabled.
     * @return Returns an input_t pointer.
     */
    input_t *Ext_Input(extender_t *extender, const uint8_t pin,
            const bool do_pull_up);

#ifdef	__cplusplus
}
#endif

#endif	/* EXT_INPUT_H */

