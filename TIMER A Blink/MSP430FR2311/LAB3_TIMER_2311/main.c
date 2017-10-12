#include <msp430.h>
/*
 * LAB3_Timer_2311
 *
 *  Created on: Oct 5, 2017
 *  Last Edited: Oct 11, 2017
 *      Author: Tyler Brady
 */
void main(void)
{
    //FREQ SET
    double x = 100;//Set to desired frequency in Hz
    const double freq = 32768/x;

    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    P1DIR |= BIT0;   // configure P1.0 as an output.
    P2DIR |= BIT0;   // configure P2.0 as an output.

    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode

    //TIMER CONFIG
    TB0CCTL0 = CCIE; // CCR0 interrupt enabled
    TB0CTL = TBSSEL__ACLK | MC_1 | ID_3; // ACLK/8, upmode
    TB0CCR0 = freq; //Set freq
    _BIS_SR(CPUOFF + GIE); // Enter LPM0 w/ interrupt

    while(1)//INFINITE LOOP (Ensures the processor does nothing else.)
    {
    }
}

#pragma vector = TIMER0_B0_VECTOR //Creating timer B0 as an interupt vector
__interrupt void Timer_B (void)
{
    P1OUT ^= BIT0;// toggle P1.0
    P2OUT ^= BIT0;// toggle P2.0
}
