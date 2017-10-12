# Button based delay

## Tyler Brady

## Background
* The main purpose of this project was to create a program capable of changing the frequency of a timer based on
the duration that the button was pressed. This was done using polling on a secoundary timer with a interrupt of
about 0.01 seconds. The secoundary timer would check and see if the button was being pressed and change the timing of
the led timer by changing the interrupt trigger period, adding about 0.01 seconds every cycle.

## Usage
* Once the board specific code has been loaded into the program, the user can hold down the designated button, causing the LEDs to remain off until the button is released. The
longer the button is held the longer the time between blinks after the button is released. On the 6989 a second designated button can also be pressed to reset the frequency back
to its default 10Hz.

## Devices
* MSP430G2553
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430F5529

## Differences
* Similarly to other projects, the main difference between processors had to do with the way timers were set up,
and which pins were used for input and output. However, one major difference of code can be found in the MSP430FR2311
as when the code from the four other processors was adapted to the 2311, it was found that the amount of FRAM in
the processor could not handle the total code. Therefore in order to do the function the code needed to be adapted and changed
so that the code would fit within the FRAM of the processor.

## Extra work
* The extra work done for this project was the implementaion of a secoundary reset button. This was done within the 
MSP430FR6989 by adding a new section of polling before the check for the button delay to see if the reset is being pressed.
 