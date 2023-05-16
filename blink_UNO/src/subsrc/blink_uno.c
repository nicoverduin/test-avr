/**
 * @file    blink.c (UNO variant)
 * @author  nico verduin
 * @brief   example program to get started (i.e. blink)
 * @version 1.0
 * @date    16-4-2023
 * Je moet hiervoor wel de TARGET_CPU en COMPORT in CMakeLists.txt in de root aanpassen.
 */

#define  F_CPU 16000000UL   // processor CPU

// include files
#include <avr/io.h>
#include <util/delay.h>

#define MS_DELAY 500   // delay time is currentlu 50 milliseconds

/**
 * @brief main line
 * 
 * @return int never actually happens
 */
int main (void) {

  //set digitial pin 13 to output
  DDRD |= _BV(DDD7);

  while(1) {
    // toggle pin 7
    PORTD ^= _BV(PORTD7);

    // wait MS_DELAY time
    _delay_ms(MS_DELAY);

  }
}