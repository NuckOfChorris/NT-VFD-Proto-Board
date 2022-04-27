#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SPIDevice.h>
#include "config.h"
#include "HV5812.h"


void charge_pump_init(void);
void error_spi(void);

HV5812 foo(SR_DIN, SR_CLK, SR_LAT, SR_BLK);

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(VFD_FIL_ENA, OUTPUT);
  pinMode(VFD_GRID_ENA, OUTPUT);
  pinMode(VFD_DP_ENA, OUTPUT);
  digitalWrite(VFD_FIL_ENA, HIGH);
  digitalWrite(LED_RED, HIGH);
  charge_pump_init();
  Adafruit_SPIDevice SPI_ADC = Adafruit_SPIDevice(ADC_NCS);
  Adafruit_SPIDevice SPI_POT = Adafruit_SPIDevice(POT_NCS);

  if (!SPI_ADC.begin()) {
    error_spi();
  }
  if (!SPI_POT.begin()) {
    error_spi();
  }

  delay(1000);
  foo.shiftByte(MSK_CLEAR);
  digitalWrite(VFD_GRID_ENA, HIGH);
}

void loop() {
  foo.shiftByte(MSK_0);
  delay(500);
  foo.shiftByte(MSK_1);
  delay(500);
  foo.shiftByte(MSK_2);
  delay(500);
  foo.shiftByte(MSK_3);
  delay(500);
  foo.shiftByte(MSK_4);
  delay(500);
  foo.shiftByte(MSK_5);
  delay(500);
  foo.shiftByte(MSK_6);
  delay(500);
  foo.shiftByte(MSK_7);
  delay(500);
  foo.shiftByte(MSK_8);
  delay(500);
  foo.shiftByte(MSK_9);
  delay(500);

  // digitalWrite(VFD_GRID_ENA, HIGH);
  // digitalWrite(VFD_DP_ENA, HIGH);
  // delay(250);
  // digitalWrite(VFD_DP_ENA, LOW);
  // delay(250);
  // digitalWrite(VFD_GRID_ENA, LOW);
  // digitalWrite(VFD_DP_ENA, HIGH);
  // delay(250);
  // digitalWrite(VFD_DP_ENA, LOW);
  // delay(250);

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