#include <msp430.h> 
/*
 * LAB3_Timer_5529
 *
 *  Created on: Oct 5, 2017
 *  Last Edited: Oct 11, 2017
 *      Author: Tyler Brady
 */

void main(void)
{
    double x = 12.5;
    const double freq = 32768/x; //Set to desired frequency in Hz
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= BIT0;   // configure P1.0 as an output.
    P4DIR |= BIT7;   // configure P4.7 as an output.

    TA0CCTL0 = CCIE; // CCR0 interrupt enabled
    TA0CTL = TASSEL_1 | MC_1; // ACLK, upmode
    TA0CCR0 = freq; //Set freq
    _BIS_SR(CPUOFF + GIE); // Enter LPM0 w/ interrupt

    while(1) //INFINITE LOOP
    {
    }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
    P1OUT ^= BIT0;// toggle P1.0
    P4OUT ^= BIT7;// toggle P4.7
}

