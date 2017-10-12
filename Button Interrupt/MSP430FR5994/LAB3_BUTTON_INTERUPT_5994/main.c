#include <msp430.h> 

/*
 * Button Interrupt 5994
 *
 *  Created on: Oct 1, 2017
 *  Last Edited: Oct 11, 2017
 *      Cleaned up and fixed some comments
 *  Author: Tyler Brady
 */

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= BIT0 + BIT1; // Set P1.0 and 1.1 to output direction
    P5OUT |= BIT6; // Set P5.6 as a high
    P5REN |= BIT6; // Enable pull up resistor on P5.6

    P5IE |= BIT6; // P5.6 interrupt enabled
    P5IES |= BIT6; // P5.6 Hi/lo edge
    P5IFG &= ~BIT6; // P5.6 IFG cleared

    TA0CCTL0 = CCIE; // CCR0 interrupt enabled
    TA0CCR0 = 25000; //resets timer at 25000 cycles

    _BIS_SR(CPUOFF + GIE); // Enter LPM0 w/ interrupt
    while(1)
    {
    }
}

#pragma vector = TIMER0_A0_VECTOR //Creating timer A0 as an interrupt vector
__interrupt void Timer0_A (void) //Deals with slight button bounce issue while also turning off the light after a set time.
{
    P5IE |= BIT6; //Enables P5.6 interrupt
    TA0CTL = 0x0000; //Disables and resets Timer A0
    P5IFG &= ~BIT6; //Disables interrupt flag
}

#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
    TA0CTL = TASSEL__ACLK  | MC__UP; // AClock, Up mode
    P5IE &= ~BIT6; //Disables interrupt on P5.6
    P5IFG &= ~BIT6; //Disables interrupt flag

    P1OUT ^= BIT0; //Toggles P1.0
    P1OUT ^= BIT1; //Toggles P1.1
}
