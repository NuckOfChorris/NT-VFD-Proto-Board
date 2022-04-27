#include <Arduino.h>
#include "config.h"

void charge_pump_init(void);


void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(VFD_FIL_ENA, OUTPUT);
  digitalWrite(VFD_FIL_ENA, HIGH);
  charge_pump_init();
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
  // TCCR1A |= (1 << COM1A1);           // Enable output compare on channel A. Non-inverting mode
  // TCCR1A |= (1 << COM1B1) | (1 << COM1B0);  // Enable output compare on channel B. Inverting mode
  // TCCR1A |= (1 << WGM11);            // Set the waveform generation mode to 9-bit fast PWM
  // TCCR1B |= (1 << WGM12);
  // TCCR1B |= (1 << CS10);             // Set the clock prescaler to 1 (no prescaling)
  TCCR1A = ((1 << COM1A1) | 
    (1 << COM1B1) | 
    (1 << COM1B0) | 
    (1 << WGM11));
  TCCR1B = ((1 << WGM12) | (1 << CS10));
}