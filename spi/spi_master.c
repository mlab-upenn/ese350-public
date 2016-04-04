#include <avr/io.h>
#include <util/delay.h>
#include <uart.h>

void spi_init_master() {
  //enable output on pin9,11,13 (SS, MOSI, SCK)
  DDRB = (1<<PB2)|(1<<PB3)|(1<<PB5);
  //enable spi, set Master, MSB first, fspi = fclk/16
  SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(1<<SPR0);
}

unsigned char master_transceive(unsigned char byteSend) {
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
  //poll to sync
  while(master_transceive(0xFF) != 0xFF) {
    printf("master is waiting");
  }
  uint8_t i = 0;
  uint8_t byteRead;
  while(1) {
    byteRead = master_transceive(i);
    printf("sent: %hu, read:%hu\n", i, byteRead); 
    i = byteRead+1;
    _delay_ms(500);
  } 

}
  


