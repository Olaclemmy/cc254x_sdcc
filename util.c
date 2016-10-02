#include "cc254x_types.h"
#include "cc254x_map.h"
#include "util.h"

void init_clock()
{
    // run both external oscillators and system at full speed
    CLKCON = 0x00;
    SLEEP = 0x84;

    // Enable pre-fetching of instructions from flash,
    // which makes the code execute much faster.
    MEMCTR = 0;
}

void delay_ms(uint16 milliseconds)
{
    // TODO: make this more accurate.
    // A great way would be to use the compare feature of Timer 4 and then
    // wait for the right number of compare events to happen, but then we
    // can't use that channel for PWM in the future.
    while(milliseconds--)
    {
        delay_us(250);
        delay_us(250);
        delay_us(250);
        delay_us(249); // there's some overhead, so only delay by 249 here
    }
}

void disableUsbPullup()
{
    P2DIR &= ~(1<<0);  // Make P2_0 be a floating input.
}

void enableUsbPullup()
{
    P2_0 = 1;
    P2DIR |= (1<<0);   // Drive P2_0 high.
}

uint8 vinPowerPresent()
{
    return 1;
}

/* empty interrupt 17 to make sure the interrupt table generated
 * by SDCC is long enough */
void isr_wdt() __interrupt(17) {}
