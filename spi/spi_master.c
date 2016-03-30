#include <avr/io.h>
#include <util/delay.h>
#include <uart.h>

void spi_init_master() {
  //enable output on pin9,11,13 (SS, MOSI, SCK)
  DDRB = (1<<PB2)|(1<<PB3)|(1<<PB5);
  //enable spi, set Master, MSB first, fspi = fclk/16
  SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(1<<SPR0);
}

unsigned char transceive(unsigned char byteSend) {
  PORTB &= ~(1<<PB2);
  SPDR = byteSend;
  while(!(SPSR & (1<<SPIF)));//poll till data is ready
  unsigned char retVal  = SPDR;
  PORTB |= (1<<PB2);
  return retVal;
}

int main() {
  uart_init();
  spi_init_master();
  uint8_t byteRead;
  printf("hello\n");
  uint8_t i = 11;
  while(1) {
    byteRead = transceive(i);
    printf("%hu\n", byteRead); 
    i++;
    if (i > 20) {
      i = 11;
    }
    _delay_ms(500);
  } 

}
  


