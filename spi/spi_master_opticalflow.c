/* spi master code for interface with 3d robotics optical flow sensor */

#include <avr/io.h>
#include <uart.h>
#include <util/delay.h>
void spi_init_master() {
  //enable output on pin10, 11,13 (SS, MOSI, SCK)
  DDRB = (1<<PB2)|(1<<PB3)|(1<<PB5);//pin 10 (PB2 is output
  //enable spi, set Master, MSB first, fspi = fclk/64
  //sample trailing (rising) edge
  //MSB first (default)
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<CPOL)|(1<<CPHA);
}
unsigned char transceive(unsigned char byteWrite){
  PORTB &= ~(1<<PB2);
  SPDR = byteWrite;
  while(!(SPSR & (1<<SPIF))); //poll till transmission complete
  _delay_us(100);
  SPDR = 0xFF;//send arbitrary value just to read
  while(!(SPSR & (1<<SPIF))); //poll till transmission complete
  _delay_us(100);
  PORTB |= (1<<PB2);
  return SPDR;

}

int main() {
  uart_init();
  spi_init_master();
  printf("hello\n");
  uint8_t motion;
  int8_t deltaX, deltaY;
  uint8_t id, id_inv;
  id = transceive(0x00);//send address for inverse_id
  //id = transceive(0xFF);
  id_inv = transceive(0x3F); //address for inverse_id
  //id_inv = transceive(0xFF);
  printf("id: %hu, in_id: %hu\n", id, id_inv);
  while(1) {

    motion = transceive(0x02);//send address for motion
    deltaX = transceive(0x03);//send address for motion
    deltaY = transceive(0x04);//send address for motion
    printf("motion: %u, deltaX: %d, deltaY: %d\n", motion>>7, deltaX, deltaY); 
    _delay_ms(200);


  } 

}
  
