#include <avr/io.h>
#include <uart.h>

void spi_init_master() {
  //enable output on pin10, 11,13 (SS, MOSI, SCK)
  DDRB = (1<<PB2)|(1<<PB3)|(1<<PB5);//pin 10 (PB2 is output
  //enable spi, set Master, MSB first, fspi = fclk/16
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void transmit(char *byteWrite, char *byteRead) {
  SPDR = *byteWrite;
  while(!(SPSR & (1<<SPIF))); //poll till transmission complete
  *byteRead = SPDR;//read value from slave

}

int main() {
  uart_init();
  spi_init_master();
  printf("hello\n");
  char byteWrite = 'm';
  char byteRead = 'r';
  while(1) {
    
    PORTB &= ~(1<<PB2);
    transmit(&byteWrite, &byteRead);
    PORTB |= (1<<PB2);
    printf("%c\n", byteRead); 
  } 

}
  
