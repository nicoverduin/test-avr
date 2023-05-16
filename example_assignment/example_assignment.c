/**
 * @file    example_assignment.c
 * @author  nico verduin
 * @brief   example program to get started (i.e. blink)
 * @version 1.0
 * @date    2023-03-29
 *
 */
#define  F_CPU 2000000UL

#include <avr/io.h>
#include <util/delay.h>

/**
 * @brief main starting point of the program.
 * @return int (with embedded this will never happen
 */
int main() {

  PORTC.DIRSET = PIN0_bm;       // bit 0 port C is set, it is an output

  // endless loop
  while (1) {

    PORTC.OUTTGL = PIN0_bm;     // toggle bit 0 port C
    _delay_ms (1000);
  }
}