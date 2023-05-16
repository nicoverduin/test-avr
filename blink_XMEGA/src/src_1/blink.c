/**
 * @file    blink.c
 * @author  nico verduin
 * @brief   example program to get started (i.e. blink)
 * @version 1.0
 * @date    11-4-2023
 *
 */
#define  F_CPU 2000000UL

#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__   // to avoid compile time errors in delay.h
#include <util/delay.h>

/**
 * @brief  mainline of the program
 * @return nothing as we never get there
 */
int main(void) {
  PORTC.DIRSET = PIN0_bm;       // bit 0 port C is set, it is an output

  while (1) {
    PORTC.OUTSET = PIN0_bm;     // bit 0 port C is high, led is on
    _delay_ms (50);
    PORTC.OUTCLR = PIN0_bm;     // bit 0 port C is low, led is off
    _delay_ms (900);
  }
}