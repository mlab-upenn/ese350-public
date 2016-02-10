#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
int overflows;
ISR(TIMER1_OVF_vect) {
 overflows++; // increment overflow counter
}
int main() {
  uart_init();
  sei(); // enable interrupts
  TCCR1B |= 0x01; // enable timer
  TIMSK1 |= 0x01; // enable overflow interrupt
  for (;;) { // loop forever
    while (!(PINB & 0x01)); // while the pin is low, do nothing
    overflows = 0; // start counting from 0

    while (PINB & 0x01); // while the pin is high, do nothing
    printf("Key released: %u\n", overflows);
  }
}