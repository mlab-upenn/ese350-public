#include "uart.h"
#include <avr/io.h>
#include <stdio.h>

int main() {
  unsigned int edge1, edge2;
  uart_init();
  TCCR1B |= 0x01; // enable timer 1, no prescaling
  TCCR1B |= 0x40; // input capture on rising edge
  TFIR1 |= 0x20; // clear the input capture flag
  while (!(TFIR1 & 0x20)); // wait until we get the first edge
  edge1 = ICR1; // store the time of the first edge
  TFIR1 |= 0x20; // clear the input capture flag
  while(!(TFIR1 & 0x20)); // wait until we get the next edge
  edge2 = ICR1; // store the time of the second edge
  printf("Frequency: %u\n", F_CPU / (edge2 - edge1));
} 