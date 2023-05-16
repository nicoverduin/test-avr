#include "attiny2_clock.h"

#include <avr/io.h>


void enable_prescaler(void)
{
    // Prep new register value
    register8_t mclkctrlb = CLKCTRL_MCLKCTRLB | CLKCTRL_PEN_bm;

    // CLKCTRL register is protected under the CCP
    CPU_CCP = CCP_IOREG_gc;
    // Enable prescaling the main clk
    CLKCTRL_MCLKCTRLB = mclkctrlb;
}

void disable_prescaler(void)
{
    // Prep new register value
    register8_t mclkctrlb = CLKCTRL_MCLKCTRLB & (~CLKCTRL_PEN_bm);

    // Write key to CPU.CCP register to be able to modify MCLKCTRLB
    CPU_CCP = CCP_IOREG_gc;
    // Write new value to register
    CLKCTRL_MCLKCTRLB = mclkctrlb;
}

void set_prescaler(bool enable, uint8_t prescaling_gc)
{
    // Prep new register value
    register8_t mclkctrlb = prescaling_gc;

    if (enable) {
        // Set prescaling bit
        mclkctrlb |= CLKCTRL_PEN_bm;
    }

    // Write key to CPU.CCP register to be able to modify MCLKCTRLB
    CPU_CCP = CCP_IOREG_gc;
    // Write new value to register
    CLKCTRL_MCLKCTRLB = mclkctrlb;
}

void lock_clkctrl(void)
{
    // Prep new register value
    register8_t mclklock = CLKCTRL_MCLKLOCK | CLKCTRL_LOCKEN_bm;

    // Write key to CPU.CCP register to be able to modify MCLKCTRLB
    CPU_CCP = CCP_IOREG_gc;
    // Write the lock to MCLKLOCK
    CLKCTRL_MCLKLOCK = mclklock;
}
