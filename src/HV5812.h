#ifndef HV5812_H
#define HV5812_H

/**
 * HV5812.h
 * 
 * J Webb
 * April 2022
 * 
 * This module implements shift register control functions for
 * the HV5812 chip.
 * 
 **/

#include <stdint.h>

/**
 * Shift n bits into the shift
 **/
//void shift_n_bits(uint8_t* pData, uint8_t n);

class HV5812 {
    public:
    HV5812(uint8_t dataPin, uint8_t clkPin, uint8_t latPin);
    HV5812(uint8_t dataPin, uint8_t clkPin, uint8_t latPin, uint8_t blkPin);
    void shiftByte(uint8_t* pData);

    private:
    uint8_t dat;
    uint8_t clk;
    uint8_t lat;
    uint8_t blk;
    uint8_t hasBlanking = 0;

    void init(void);
};



#endif