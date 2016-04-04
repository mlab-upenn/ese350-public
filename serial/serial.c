#include <avr/io.h>
#include <stdio.h>

void uart_init(unsigned int baud) {
  UBRR0 = 103;//fclk=16MHz, baud=9600 
  UCSR0B = 0x18;//enable TX, RX
  UCSR0C = 0x06;//async, 8 bit frame, no parity
}

void sendByte(char c) {
  if (c == '\n') {
    c = '\r';
  }
  while(!(UCSR0A & (1<<UDRE0)));//poll until ready to transmit 
  UDR0 = (uint8_t)c;
}

char receiveByte() {
  while(!(UCSR0A & 0x80)); //poll until ready to receive
  return UDR0;
}
  
void main() {
  uart_init(9600);
  char c;
  while(1) {
    c = receiveByte();
    sendByte(c);
  }
    
}

