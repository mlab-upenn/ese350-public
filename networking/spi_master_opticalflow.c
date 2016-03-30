/* spi master code for interface with 3d robotics optical flow sensor */

#include <avr/io.h>
#include <uart.h>
#include <util/delay.h>
void spi_init_master() {
  //enable output on pin10, 11,13 (SS, MOSI, SCK)
  DDRB = (1<<PB2)|(1<<PB3)|(1<<PB5);//pin 10 (PB2 is output
  //enable spi, set Master, MSB first, fspi = fclk/16
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void transmit(char byteWrite, char *byteRead) {
  PORTB &= ~(1<<PB2);
  SPDR = byteWrite;
  while(!(SPSR & (1<<SPIF))); //poll till transmission complete
  _delay_us(100);
  *byteRead = SPDR;//read value from slave
  PORTB |= (1<<PB2);

}

int main() {
  uart_init();
  spi_init_master();
  printf("hello\n");
  char byteWrite = 'm';
  char byteRead = 'r';
  char motion, deltaX, deltaY;
  char id, idin;
  transmit(0x00, &id);//send address for motion
  _delay_us(100);
  transmit(0x3f, &idin);//send address for motion
  _delay_us(100);
  printf("id: %u, in_id: %u\n", id, idin);
  while(1) {
/*
    transmit(0x02, &motion);//send address for motion
    _delay_us(100);
    transmit(0x03, &deltaX);//send address for motion
    _delay_us(100);
    transmit(0x04, &deltaY);//send address for motion
    _delay_us(100);
    printf("motion: %u, deltaX: %d, deltaY: %d\n", byteRead>>7, deltaX, deltaY); 
    _delay_ms(100);
*/
  } 

}
  
