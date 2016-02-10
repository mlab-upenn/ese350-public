#include <avr/interrupt.h> // common defines and macros
#include <avr/io.h> // derivative information
#include <stdio.h>
#include <stdlib.h>
#include “uart.h”

/* generate a 50% square wave using OC0A */

unsigned int half_period = 1000; // 1 kHz signal, half_period given in bus cycles
 //Assume your clock is 2MHz. 1 cycle is 0.5us
 //1000 cycles are 500us
ISR (TIMER0_COMPA_vect){
  OCR0A += half_period;
}
main(){
  TCCR0A |= 0x80;
  TIMSK0 = 0x02;
  OCR0A += TCNT0 + half_period; //Starts the OC process at arbitrary value
  TCCR0A |= 0x40; //Toggle OC0A pin
  sei();
  while(1);
} 