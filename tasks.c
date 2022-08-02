#include <msp430f5529.h>
#include <stdint.h>

void taskA()
{
    P1DIR |= BIT0;

    while(1)
    {
        P1OUT ^= BIT0;
        __delay_cycles(500000);
    }
}

void taskB()
{
    P4DIR |= BIT7;

    while(1)
    {
        P4OUT ^= BIT7;
        __delay_cycles(400000);
    }
}
