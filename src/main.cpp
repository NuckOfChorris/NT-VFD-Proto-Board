#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SPIDevice.h>
#include "config.h"

void charge_pump_init(void);


void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(VFD_FIL_ENA, OUTPUT);
  digitalWrite(VFD_FIL_ENA, HIGH);
  charge_pump_init();
  Adafruit_SPIDevice SPI_ADC = Adafruit_SPIDevice(ADC_NCS);
  Adafruit_SPIDevice SPI_POT = Adafruit_SPIDevice(POT_NCS);

  if (!SPI_ADC.begin()) {
    error_spi();
  }
  if (!SPI_POT.begin()) {
    error_spi();
  }
  
}

void loop() {
  digitalWrite(LED_RED, HIGH);
  delay(800);
  digitalWrite(LED_RED, LOW);
  delay(80);
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