/* 
 * File:   random.h
 * Author: Jacob Malin
 *
 * Created on December 3, 2024, 10:19 PM
 */

#ifndef RANDOM_H
#define	RANDOM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <avr/io.h>
    
#define RAND_MAX_ATTEMPTS 3
    
    /**
     * Initializes the random module.
     */
    void Random(void);

    /**
     * Perform xorshift. Taken from 
     * https://sureshjoshi.com/embedded/bgscript-random-number-generator
     * @return Returns a random integer.
     */
    uint32_t _Random_xorshift128(void);

    /**
     * Generates a random integer on the interval [0,upper).
     * @param uint8_t upper The upper value, non-inclusive.
     * @return Returns a random integer.
     */
    uint8_t Random_generate(uint8_t upper);

    /**
     * Generates a random integer on the interval [0,upper). Will attempt twice
     * to generate a number that is not avoid. On the third attempt, the value 
     * will be accepted even if it is the avoid value.
     * @param uint8_t upper The upper value, non-inclusive.
     * @param uint8_t avoid The value to avoid.
     * @return Returns a random integer.
     */
    uint8_t Random_generate_avoid(uint8_t upper, uint8_t avoid);

    /**
     * Adds randomness to the generator.
     */
    void Random_add_random(void);

#ifdef	__cplusplus
}
#endif

#endif	/* RANDOM_H */

