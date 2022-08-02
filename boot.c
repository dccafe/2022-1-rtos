#include <msp430.h>
#include <stdint.h>
#include <scheduler.h>
#include <tasks.h>

void main()
{
    // Config
    WDTCTL = WDTPW | WDTIS_4 | WDTSSEL__ACLK | WDTTMSEL;
    SFRIE1 |= WDTIE;

    registerTask(taskA);
    registerTask(taskB);

    startRTOS();

    while(1);

}
