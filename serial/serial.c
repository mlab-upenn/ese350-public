#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <stdio.h>


void uart_init(unsigned int baud) {
  UBRR0 = 103; 
  UCSR0B = 0x18;
  UCSR0C = 0x06;//8 bits of data
}

void sendByte(char c) {
  if (c == '\n') {
    c = '\r';
  }
 // while(!(UCSR0A & (1<<UDRE0)));//poll until ready to transmit 
  UDR0 = (uint8_t)c;
  while(!(UCSR0A & (1<<TXC0)));
}

char receiveByte() {
  while(!(UCSR0A & 0x80)); //poll until ready to receive
  return UDR0;
}
  
void main() {
  uart_init(9600);
  DDRB = 0x20;

  char c = 'b';

  while(1) {
    c = receiveByte();
    
    sendByte(c);
  }
    
}

