#include <msp430.h>
/*
 * LAB3_BUTTONDELAY_2311
 *
 *  Created on: Oct 5, 2017
 *  Last Edited: Oct 11, 2017
 *      Author: Tyler Brady
 *      Notes: Had to change the code from all other versions due to a memory error in the other logic
 */
void main(void)
{

    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    P1DIR |= BIT0;   // configure P1.0 as an output.

    P1OUT |= BIT1; // Set pull up resistor on P1.1
    P1REN |= BIT1; // Enable pull up resistor on P1.1

    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode

    //TIMER 0 CONFIG
    TB0CCTL0 = CCIE; // CCR0 interrupt enabled
    TB0CTL = TBSSEL__ACLK | MC_1; // ACLK, upmode
    TB0CCR0 = 3276.8; //Set freq

    //TIMER 1 CONFIG
    TB1CCTL0 = CCIE; // CCR0 interrupt enabled
    TB1CTL = TBSSEL__ACLK | MC_1; // ACLK, upmode
    TB1CCR0 = 32.768; //Set freq
    _BIS_SR(CPUOFF + GIE); // Enter LPM0 w/ interrupt

    while(1)//INFINITE LOOP (Ensures the processor does nothing else.)
    {
    }
}
#pragma vector = TIMER0_B0_VECTOR //Creating timer B0 as an interupt vector
__interrupt void Timer_B (void)
{
    P1OUT ^= BIT0;// toggle P1.0
}
 int x = 0; //Reset variable
#pragma vector = TIMER1_B0_VECTOR //Creating timer B1 as an interrupt vector
__interrupt void Timer_B1 (void) //Does nothing but reset x when button is not pressed, and counts/disables LEDs/Sets new CCR0 for timer 0 when pressed
{
    if(P1IN & BIT1) //Default state
    {
      x=0;
    }
    else //Button hold
    {
        if(x == 0) //Resets TB0CCR0 to count from base again
        {
            TB0CCR0 = 3267.8;
            x = 1;
        }
        else
        {
            TB0CCR0 += 327.68; //Sets frequency of the time held, this is done every cycle until the button is released
        }
    }
}


