#include <avr/io.h>
#include <uart.h>
#include <util/delay.h>

uint8_t i = 65;

void spi_init_slave() {
  //enable output on MISO
  DDRB = 1<<PB4;
  //enable spi, 
  SPCR = (1<<SPE);

}

unsigned char transceive(unsigned char byteSend) {
  SPDR = byteSend;
  while(!(SPSR & (1<<SPIF)));//poll till data is ready
  return SPDR;
}


int main() {
  uart_init();
  spi_init_slave();
  char byteRead;
  SPDR = i;
  uint8_t i = 0;
  while(1) {
    byteRead = transceive(i);
    printf("%hu\n", byteRead); 
    i = (i+1)%10;
  } 

}
  
