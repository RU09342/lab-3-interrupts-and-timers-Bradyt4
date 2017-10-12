#include <msp430.h> 
/*
 * LAB3_Timer_2553
 *
 *  Created on: Oct 5, 2017
 *  Last Edited: Oct 11, 2017
 *      Author: Tyler Brady
 */

void main(void)
{
    double x = 10; //Enter desired freq
    const double freq = 32768/x; //Frequency Divider
     WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    P1DIR |= BIT0 + BIT6;   // configure P1.0 and P1.6 as an output.

    //TIMER CONFIG
    CCTL0 = CCIE; // CCR0 interrupt enabled
    TACTL = TASSEL_1 | MC_1; // ACLK, upmode
    CCR0 = freq; //Divides SMCLK speed of 1MHz by desired frequency to get the correct CCR0 value
    _BIS_SR(CPUOFF + GIE); // Enter LPM0 w/ interrupt

    while(1)//INFINITE LOOP (Ensures the processor does nothing else.)
    {
    }
}

#pragma vector = TIMER0_A0_VECTOR //Creating timer A0 as an interupt vector
__interrupt void Timer_A (void)
{
    P1OUT ^= BIT0 + BIT6; // toggle P1.0 and P1.6
}

