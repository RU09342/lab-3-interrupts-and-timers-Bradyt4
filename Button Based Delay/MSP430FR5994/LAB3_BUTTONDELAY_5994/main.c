#include <msp430.h>
/*
 * LAB3_BUTTONDELAY_5994
 *
 *  Created on: Oct 10, 2017
 *  Last Edited: Oct 11, 2017
 *      Author: Tyler Brady
 */

void main(void)
{
    //FREQEUNCY
    double Red = 12;
    double Timer0 = 32768/Red;


    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= BIT0 + BIT1;   // configure P1.0 and P1.1 as an output.

    P5OUT |= BIT6; // Set pull up resistor on P5.6
    P5REN |= BIT6; // Enable pull up resistor on P5.6

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    //TIMER A0 CONFIG
    TA0CCTL0 = CCIE; // CCR0 interrupt enabled
    TA0CTL = TASSEL__ACLK  | MC__UP; // SMCLK/8, upmode
    TA0CCR0 = Timer0-1;

    //TIMER A1 CONFIG
    TA1CCTL0 = CCIE; // CCR0 interrupt enabled
    TA1CTL = TASSEL__ACLK  | MC__UP; // SMCLK/8, upmode
    TA1CCR0 = 32.768;

    _BIS_SR(CPUOFF + GIE); // Enter LPM0 w/ interrupt



    while(1)//INFINITE LOOP (Ensures the processor does nothing else.)
    {
    }
}

#pragma vector = TIMER0_A0_VECTOR //Creating timer A0 as an interrupt vector
__interrupt void Timer0_A (void)
{
    if(P5IN & BIT6) //Default state
    {
        P1OUT ^= BIT0;// toggle P1.0
        P1OUT ^=  BIT1;// toggle P1.1
    }
}
double x = 0.01;
#pragma vector = TIMER1_A0_VECTOR //Creating timer A1 as an interrupt vector
__interrupt void Timer1_A (void)
{
    if(P5IN & BIT6) //Default state
    {
        x = 0.01; //Resets counter variable for next hold
    }
    else //Button hold
    {
        x += 0.01; //Counts up for every 1/100th of a second
        TA0CCR0 = (32768)/(1/x); //Sets frequency of the time held, this is done every cycle until the button is released
        P1OUT &= ~BIT0;// toggle P1.0 OFF
        P1OUT &= ~BIT1;// toggle P1.1 OFF
    }
}
