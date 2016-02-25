#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
unsigned int diff, edge1, edge2, overflows;
unsigned long pulse_width;
ISR(TIMER1_OVF_vect) {
  overflows++;
}

int main() {
  uart_init();
  TCCR1B |= 0x03; // start timer, prescaler = 64
  TCCR1B |= 0x40; // capture rising edges
  overflows = 0;
  TIMSK1 |= 0x01; // enable overflow interrupt
  TIFR1 |= 0x20; // clear input capture flag

  while (!(TIFR1 & 0x20)); // wait until an edge
  sei(); // enable interrupts
  edge1 = ICR1; // save time of first edge
  TCCR1B &= 0xBF; // capture falling edges
  TIFR1 |= 0x20; // clear input capture flag

  while(TIFR1 & 0x20); //wait until falling edge
  cli(); // disable interrupts
  edge2 = ICR1; // save time of the second edge
  if (edge2 < edge1) {
    overflows--;
  }
  diff = edge2 - edge1;
  pulse_width = (long)overflows * 65536u +
  (long)diff;
  printf("pulse width = 4us x %l\n", pulse_width);
  for(;;);
}