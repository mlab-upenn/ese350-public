#include "uart.h"
#include <avr/io.h>

int main() {
    uart_init();
    ADCSRA |= 0x07; // set ADC prescaler to 1/128
    ADMUX  |= 0xc0; // use 1.1 voltage reference
    ADCSRA |= 0x81; // enable the ADC
    
    for (;;) {
        ADCSRA |= 0x40;                       // start an ADC measurement
        while(ADCSRA & 0x40);                 // wait for ADC to complete
        int temp = (double)ADC * 0.107421875; // convert ADC to degrees F
        printf(
            "\e[3%dm%u Degrees F\n",             // print color-coded output
            temp <= 74 ? 2 : temp <= 76 ? 3 : 1, // chose color based on temp
            temp
        );
    }
}
