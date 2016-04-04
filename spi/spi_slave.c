#include <avr/io.h>
#include <uart.h>
#include <util/delay.h>


void spi_init_slave() {
  //enable output on MISO
  DDRB = 1<<PB4;
  //enable spi, 
  SPCR = (1<<SPE);

}

unsigned char transceive(unsigned char byteSend) {
  SPDR = byteSend;
//poll till data is ready
  while(!(SPSR & (1<<SPIF)));  
  return SPDR;
}


int main() {
  uart_init();
  spi_init_slave();
  uint8_t sync = 255;
//poll to sync
  while(transceive(0x00) != 0xFF) {
    printf("slave is waiting\n");
  }
  transceive(0xFF);
  uint8_t byteRead;
  uint8_t i = 1;
  while(1) {
    byteRead = transceive(i);
    printf("sent: %hu, read: %hu\n",i, byteRead); 
    i = byteRead+3;
  } 
}
  
