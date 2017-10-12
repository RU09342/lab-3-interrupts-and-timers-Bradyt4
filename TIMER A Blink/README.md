# TIMER A BLINK

## Tyler Brady

## Background
* The main purpose of this lab was to design code capable of using timers that could simply blink the onboard
LEDs. By using a variety of different methods at making the timer, mixing either SMCLK or ACLK and pre-dividers.
The reason why one might use a pre-divder is when a much smaller frequency is needed as the CCR0 registers can only
hold up to approximatly 60kHz. Therefore when a lower frequency is needed on a much higher frequency, the predividers
make that possible.

## Devices
* MSP430G2553
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430F5529

## Differences
* The main differences between each of the devices is similar to all the other projects where it is the use of different
pins, macros, and timer setup.

## Extra work
* NONE