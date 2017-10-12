#include <msp430.h> 
/*
 * LAB3_BUTTONDELAY_6989 w/ P1.2 as RESET
 *
 *  Created on: Oct 6, 2017
 *  Last Edited: Oct 11, 2017
 *  Author: Tyler Brady
 */
void main(void)
{
    double x = 10;
    const double freq = 32768/x; //Set to desired frequency in Hz

    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    P1DIR |= BIT0; // configure P1.0 as an output.
    P9DIR |= BIT7; // configure P9.7 as an output.

    //COUNT BUTTON
    P1OUT |= BIT1; // Set pull up resistor on P1.1
    P1REN |= BIT1; // Enable pull up resistor on P1.1

    //RESET BUTTON
    P1OUT |= BIT2; // Set pull up on P1.2
    P1REN |= BIT2; // Enable pull up resistor on P1.2

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;


    //TIMER 0 CONFIG
    TA0CCTL0 = CCIE; // CCR0 interrupt enabled
    TA0CTL = TASSEL__ACLK | MC__UP; // SMCLK/8, upmode
    TA0CCR0 = freq;

    //TIMER 1 CONFIG
    TA1CCTL0 = CCIE; // CCR0 interrupt enabled
    TA1CTL = TASSEL__ACLK | MC__UP; // ALCK, upmode
    TA1CCR0 = 32.768;

    __bis_SR_register(CPUOFF + GIE); // Enter LPM0 w/ interrupt

    while(1)//INFINITE LOOP (Ensures the processor does nothing else.)
    {
    }
}

#pragma vector = TIMER0_A0_VECTOR //Creating timer A0 as an interrupt vector
__interrupt void Timer_A0 (void) //Controls LED blinks
{
    if(BIT1 & P1IN)
    {
        P1OUT ^= BIT0;// toggle P1.0
        P9OUT ^= BIT7;// toggle P9.7
    }
}

double x = 0.01; //Counter Variable
#pragma vector = TIMER1_A0_VECTOR //Creating timer A1 as an interrupt vector
__interrupt void Timer_A1 (void) //Does nothing but reset x when button is not pressed, and counts/disables LEDs/Sets new CCR0 for timer 0 when pressed
{
    if((P1IN & BIT2) == 0) //Reset condition (Only resets if BIT2 is off)
    {
        TA0CCR0 = 3276.8; //Sets the frequency back to 10Hz
    }
    else if(P1IN & BIT1) //Default state
    {
        x = 0.01; //Resets counter variable for next hold
    }
    else //Button hold
    {
        x += 0.01; //Counts up for every 1/100th of a second
        TA0CCR0 = (32768)/(1/x); //Sets frequency of the time held, this is done every cycle until the button is released
        P1OUT &= ~BIT0;// toggle P1.0 OFF
        P9OUT &= ~BIT7;// toggle P9.7 OFF
    }
}

