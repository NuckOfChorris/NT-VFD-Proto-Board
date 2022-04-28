#ifndef CONFIG_H
#define CONFIG_H

/**
 * config.h
 * 
 * Configuration header file. All global constants
 * and parameters are defined here. Pin configuration
 * is based on hardware version 1.0.
 * 
 * J Webb
 * April 2022
 */


//#define DEBUG

/** GLOBAL CONSTANTS **/
#define FLASH_DURATION_500MS 500
#define FLASH_DURATION_10S 10000

/** BITMASKS **/
#define MSK_0 0b1111011
#define MSK_1 0b1000001
#define MSK_2 0b0110111
#define MSK_3 0b1100111
#define MSK_4 0b1001101
#define MSK_5 0b1101110
#define MSK_6 0b1111110
#define MSK_7 0b1000011
#define MSK_8 0b1111111
#define MSK_9 0b1101111
#define MSK_CLEAR 0b0000000

/** PIN CONFIGURATION **/
#define LED_RED         5   //PD5 OCB0B
#define LED_GREEN       6   //PD6 OCC0A
#define SR_DIN          14  //PC0
#define SR_CLK          15  //PC1
#define SR_LAT          16  //PC2
#define SR_BLK          17  //PC3
#define VFD_FIL_ENA     2   //PD2
#define VFD_GRID_ENA    3   //PD3 OC2B
#define VFD_DP_ENA      4   //PD4
#define ADC_NCS         7   //PD7
#define POT_NCS         8   //PB0
#define CP_A            9   //PB1 OC1A
#define CP_B            10  //PB2 OC1B

#endif