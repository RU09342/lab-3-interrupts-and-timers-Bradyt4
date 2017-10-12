#include <msp430.h> 
/*
 * LAB3_BUTTONDELAY_2553
 *
 *  Created on: Oct 9, 2017
 *  Last Edited: Oct 11, 2017
 *      Author: Tyler Brady
 */

void main(void)
{
    double x = 10;
    const double freq = 32768/x; //Set to desired frequency in Hz
     WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    P1DIR |= BIT0 + BIT6;   // configure P1.0 and P1.6 as an output.

    P1OUT |= BIT3; // Set pull up resistor on P1.3
    P1REN |= BIT3; // Enable pull up resistor on P1.3

    //TIMER CONFIG
    CCTL0 = CCIE; // CCR0 interrupt enabled
    TACTL = TASSEL_1 | MC_1; // ACLK, upmode
    CCR0 = freq; //Divides SMCLK speed of 1MHz by desired frequency to get the correct CCR0 value

    //TIMER 1 CONFIG
    TA1CCTL0 = CCIE; // CCR0 interrupt enabled
    TA1CTL = TASSEL_1 | MC_1; // ALCK, upmode
    TA1CCR0 = 32.768;

    _BIS_SR(CPUOFF + GIE); // Enter LPM0 w/ interrupt

    while(1)//INFINITE LOOP (Ensures the processor does nothing else.)
    {
    }
}

#pragma vector = TIMER0_A0_VECTOR //Creating timer A0 as an interupt vector
__interrupt void Timer_A (void)
{
    if(P1IN & BIT3)
    {
        P1OUT ^= BIT0 + BIT6; // toggle P1.0 and P1.6
    }
}

double x = 0.01; //Counter Variable
#pragma vector = TIMER1_A0_VECTOR //Creating timer A1 as an interrupt vector
__interrupt void Timer_A1 (void) //Does nothing but reset x when button is not pressed, and counts/disables LEDs/Sets new CCR0 for timer 0 when pressed
{
    if(P1IN & BIT3) //Default state
    {
        x = 0.01; //Resets counter variable for next hold
    }
    else //Button hold
    {
        x += 0.01; //Counts up for every 1/100th of a second
        TA0CCR0 = (32768)/(1/x); //Sets frequency of the time held, this is done every cycle until the button is released
        P1OUT &= ~BIT0 + ~BIT6;// toggle P1.0 and P1.6 OFF
    }
}
