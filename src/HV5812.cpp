/**
 * HV5812.cpp
 * 
 * J Webb
 * April 2022
 * 
 * This module implements the HV5812 class methods.
 * 
 **/

#include "HV5812.h"
#include <Arduino.h>


HV5812::HV5812(uint8_t dataPin, uint8_t clkPin, uint8_t latPin) {
    dat = dataPin;
    clk = clkPin;
    lat = latPin;
    init();
}

HV5812::HV5812(uint8_t dataPin, uint8_t clkPin, uint8_t latPin, uint8_t blkPin) {
    dat = dataPin;
    clk = clkPin;
    lat = latPin;
    blk = blkPin;
    hasBlanking = 1;
    init();
}

void HV5812::shiftByte(uint8_t data) {
    for (uint8_t i = 7; i > 0; i--) {
        digitalWrite(dat, data & (1 << i));
        digitalWrite(clk, HIGH);
        digitalWrite(clk, LOW);
    }
    digitalWrite(dat, LOW);
    digitalWrite(lat, HIGH);
    digitalWrite(lat, LOW);
}

void HV5812::write7Seg(uint8_t data) {
    for (uint8_t i = 0; i < 7; i++) {
        digitalWrite(dat, data & (1 << (6 - i)));
        digitalWrite(clk, HIGH);
        digitalWrite(clk, LOW);
    }
    digitalWrite(dat, LOW);
    digitalWrite(lat, HIGH);
    digitalWrite(lat, LOW);
}

// void HV5812::writeDigit(uint8_t d) {
//     switch d {
//         case 0:
//             write7Seg(MSK_0);
//     }
// }

void HV5812::init(void) {
    pinMode(dat, OUTPUT);
    pinMode(clk, OUTPUT);
    pinMode(lat, OUTPUT);
    digitalWrite(dat, LOW);
    digitalWrite(clk, LOW);
    digitalWrite(lat, LOW);
    if (hasBlanking) {
        pinMode(blk, OUTPUT);
        digitalWrite(blk, LOW);
    }
}