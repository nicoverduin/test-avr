#define F_CPU 20000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "attiny2_clock.h"

int main(void) {
    // Disable the prescaler for getting maximum clock freq
    disable_prescaler();
    // lock the clkctrl registers
    lock_clkctrl();

    // Set pin B7 (LED0) to output
    PORTB.DIRSET = PIN7_bm;
    // Set pin B3 (external LED) to output
    PORTB.DIRSET = PIN3_bm;

    // Turn off LED0 (active low)
    PORTB.OUTSET = PIN7_bm;
    // Turn off external LED
    PORTB.OUTCLR = PIN3_bm;

    while (1) {
        // Turn on LED0
        PORTB.OUTCLR = PIN7_bm;
        // Turn on external LED
        PORTB.OUTSET = PIN3_bm;
        _delay_ms(50);

        // Turn off LED0
        PORTB.OUTSET = PIN7_bm;
        // Turn off external LED
        PORTB.OUTCLR = PIN3_bm;
        _delay_ms(900);
    }
}
