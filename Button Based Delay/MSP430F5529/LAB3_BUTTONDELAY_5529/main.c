#include <msp430.h>
/*
 * LAB3_BUTTONDELAY_5529
 *
 *  Created on: Oct 6, 2017
 *  Last Edited: Oct 11, 2017
 *  Author: Tyler Brady
 */
void main(void)
 {
    double x = 10;
    const double freq = 32768/x; //Set to desired frequency in Hz

    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= BIT0;   // configure P1.0 as an output.
    P4DIR |= BIT7;   // configure P4.7 as an output.

    P1OUT |= BIT1; // Set P1.1 as a high
    P1REN |= BIT1; // Enable pull up resistor on P1.1

    //TIMER 0
    TA0CCTL0 = CCIE; // CCR0 interrupt enabled
    TA0CTL = TASSEL_1 | MC_1; // SMCLK/8, upmode
    TA0CCR0 = freq; //Set at 12.5Hz

    //TIMER 1
    TA1CCTL0 = CCIE; // CCR0 interrupt enabled
    TA1CTL = TASSEL_1 | MC_1; // SMCLK/8, upmode
    TA1CCR0 = 32.678; //Set at 12.5Hz

    _BIS_SR(CPUOFF + GIE); // Enter LPM0 w/ interrupt

    while(1) //INFINITE LOOP
    {
    }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
    if(P1IN & BIT1)
    {
        P1OUT ^= BIT0;// toggle P1.0
        P4OUT ^= BIT7;// toggle P4.7
    }
}

double x = 0.01;
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer_A1 (void)
{
    if(P1IN & BIT1) //Default state
    {
        x = 0.01; //Resets counter variable for next hold
    }
    else //Button hold
    {
        x += 0.01; //Counts up for every 1/100th of a second
        TA0CCR0 = (32768)/(1/x); //Sets frequency of the time held, this is done every cycle until the button is released
        P1OUT &= ~BIT0;// toggle P1.0
        P4OUT &= ~BIT7;// toggle P4.7
    }

}
