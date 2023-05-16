/**
 * @file    blink_as_state_machine.c
 * @author  nico verduin
 * @brief   example program with blink but now as a state machine
 * @version 1.0
 * @date    11-4-2023
 *
 */
#define  F_CPU 2000000UL

#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__   // leave this in the code to avoid compile errors in delay.h
#include <util/delay.h>

// Create an enum of different delay values
// without actually specifying them in code

// enum with values set
enum {
  DELAY_1 = 10,    // 10  ms
  DELAY_2 = 25,    // 250  ms
  DELAY_3 = 50     // 500 ms
};

const uint8_t LOOP_CNT = 10;     // flash the delays for 5 times per type (ON and OFF makes 10)

/**
 * @brief   mainline of the program
 * @return  nothing as we never get there
 */
int main(void) {
  PORTC.DIRSET = PIN0_bm;         // bit 0 port C is set, it is an output

  uint16_t state = DELAY_1;       // start with first delay

  // start with an endless loop
  while (1) {

    // calculate the delay time
    uint16_t delayTime = state * 10;

    // show the flashing led 5 times update (ON and OFF)
    for (uint8_t i = 0; i < LOOP_CNT; i++) {

      PORTC.OUTTGL = PIN0_bm;     // Toggle the LED
      _delay_ms (delayTime);  // and wait
    }

    // move from state to state
    switch (state){

      case DELAY_1:
        state = DELAY_2;    // move to the next state
        break;

      case DELAY_2:
        state = DELAY_3;    // move to the next state
        break;

      case DELAY_3:
        state = DELAY_1;    // move to the first state
        break;

      default:
        break;
    }
  }
}