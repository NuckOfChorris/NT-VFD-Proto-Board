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