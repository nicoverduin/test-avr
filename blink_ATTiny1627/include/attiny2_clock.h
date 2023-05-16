#ifndef ATTINY2_CLOCK_H
#define ATTINY2_CLOCK_H

#include <stdbool.h>
#include <stdint.h>

void enable_prescaler(void);
void disable_prescaler(void);
void set_prescaler(bool enable, uint8_t prescaling);
void lock_clkctrl(void);

#endif /* ATTINY2_CLOCK_H */
