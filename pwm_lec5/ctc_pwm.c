/** example configuration for CTC mode */
#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t count = 0; // global counter

// initialize timer, interrupt and variable
void timerX_init()
{
 // set up timerX with prescaler and CTC mode
 // initialize counter
 // initialize compare value
 // enable compare interrupt
 // enable global interrupts
}

// process the ISR that is fired
ISR (TIMERx_COMPA_vect)
{
 // do whatever you want to do here
 // say, increment the global counter
 count++;

 // check for the global counter
 // if count == odd, delay required = 11 ms
 // if count == even, delay required = 9 ms
 // thus, OCRx should be constantly updated
 if (count % 2 == 0)
 OCRx = 9999; // calc and sub approp. value
 else
 OCRx = 10999; // calc and sub approp. value
}

int main(void)
{
 // initialize the output pin, say PC0
 DDRC |= (1 << 0);

 // initialize timerX
 timerX_init();

 // loop forever
 while(1)
 {
 // do nothing

 }
}