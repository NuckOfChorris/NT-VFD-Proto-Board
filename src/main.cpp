#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SPIDevice.h>
#include "config.h"
#include "HV5812.h"
#include "cie1931.h"


void charge_pump_init(void);
void error_spi(void);

HV5812 SR(SR_DIN, SR_CLK, SR_LAT, SR_BLK);
uint8_t digits[] = {MSK_0, MSK_1, MSK_2, MSK_3, MSK_4,
                    MSK_5, MSK_6, MSK_7, MSK_8, MSK_9};

float R = (10 * log10(2))/(log10(255));

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(VFD_FIL_ENA, OUTPUT);
  pinMode(VFD_GRID_ENA, OUTPUT);
  pinMode(VFD_DP_ENA, OUTPUT);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  //digitalWrite(VFD_FIL_ENA, HIGH);
  
  charge_pump_init();
  Adafruit_SPIDevice SPI_ADC = Adafruit_SPIDevice(ADC_NCS);
  Adafruit_SPIDevice SPI_POT = Adafruit_SPIDevice(POT_NCS);

  if (!SPI_ADC.begin()) {
    error_spi();
  }
  if (!SPI_POT.begin()) {
    error_spi();
  }

  SR.write7Seg(MSK_CLEAR);
  analogWrite(VFD_GRID_ENA, 5);
  //digitalWrite(VFD_DP_ENA, HIGH);
}


void loop() {
  for (uint8_t i = 0; i < 10; i++) {
    //uint8_t duty = map(i, 0, 9, 5, 255);
    uint8_t duty = pow (2, (i / R)) - 1;
    analogWrite(VFD_GRID_ENA, duty);
    analogWrite(LED_RED, 255 - duty);
    SR.write7Seg(digits[i]);
    delay(500);
  }

  // for (uint16_t i = 0; i < 255; i++) {
  //   analogWrite(VFD_GRID_ENA, i);
  //   delay(8);
  // }
  // for (uint16_t j = 0; j < 255; j++) {
  //   analogWrite(VFD_GRID_ENA, 255 - j);
  //   delay(8);
  // }

  // digitalWrite(LED_RED, HIGH);
  // delay(800);
  // digitalWrite(LED_RED, LOW);
  // delay(80);
}


void charge_pump_init(void) {
  pinMode(CP_A, OUTPUT);
  pinMode(CP_B, OUTPUT);
  OCR1A = 255;                // 50% duty cycle in 9-bit mode
  OCR1B = 255;                // 50% duty cycle in 9-bit mode          
  TCCR1A = ((1 << COM1A1) |   // Enable output compare on channel A. Non-inverting mode
    (1 << COM1B1) |           // Enable output compare on channel B. Inverting mode
    (1 << COM1B0) |           // Enable output compare on channel B. Inverting mode
    (1 << WGM11));            // Set the waveform generation mode to 9-bit fast PWM
  TCCR1B = ((1 << WGM12) |    // Set the waveform generation mode to 9-bit fast PWM
     (1 << CS10));            // Set the clock prescaler to 1 (no prescaling)
}

void error_spi(void) {
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, HIGH);
  while (1) {
    digitalWrite(LED_RED, LOW);
    delay(80);
    digitalWrite(LED_RED, HIGH);
    delay(200);
    digitalWrite(LED_RED, LOW);
    delay(80);
    digitalWrite(LED_RED, HIGH);
    delay(1000);
  }
}