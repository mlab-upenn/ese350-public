#include <avr/io.h>
#include <uart.h>

void spi_init_slave() {
  //enable output on MISO
  DDRB = 1<<PB4;
  //enable spi, 
  SPCR = (1<<SPE);

}
void read(char *byteRead) {
  while(!(SPSR & (1<<SPIF)));//poll till data is ready
  *byteRead = SPDR;
}

void write(char byteWrite) {
  SPDR = byteWrite;
}
  


int main() {
  uart_init();
  spi_init_slave();
  char byteWrite = 's';
  char byteRead;
  while(1) {
    while(PORTB & (1<<PB2));//poll till is ^SS is low
    read(&byteRead);
    while(!(PORTB & (1<<PB2)))//poll till ^SS is hi
    write(byteWrite);
    printf("%c\n", byteRead); 
  } 

}
  
