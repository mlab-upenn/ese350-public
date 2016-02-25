/* This code is supposed to flash an LED every 6 s */
#include <avr/io.h>

void timer0_init()
{
 // set up timer with no prescaling
  TCCR0B |= (1 << CS00);

 // initialize counter
  TCNT0 = 0;
}

int main(void)
{
 // connect led to pin PC0
  DDRC |= (1 << 0);

 // initialize timer
  timer0_init();

 // loop forever
  while(1)
  {
 // check if the timer count reaches 191
    if (TCNT0 >= 191)
    {
      PORTC ^= (1 << 0); // toggles the led
      TCNT0 = 0; // reset counter
    }
  }
}
