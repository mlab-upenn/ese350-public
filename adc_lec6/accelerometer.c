#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int x, y;
volatile int max_x = 0;
volatile int max_y = 0;
volatile int min_x = 1024;
volatile int min_y = 1024;
volatile int calibrating = 1;

ISR(ADC_vect) {
    switch (ADMUX) {
        case 3:
            x = ADC;
            if (calibrating) {
                if (x > max_x) max_x = x;
                else if (x < min_x) min_x = x;
            }
            ADMUX = 4;
            break;
        case 4:
            y = ADC;
            if (calibrating) {
                if (y > max_y) max_y = y;
                else if (y < min_y) min_y = y;
            }
            ADMUX = 3;
            break;
    }
}

int main() {
    uart_init();
    sei();          // enable interrupts
    DDRC |= 0x20;   // use ADC5 as ground
    ADMUX = 3;      // start at pin 3
    ADCSRA |= 0x80; // enable ADC
    ADCSRA |= 0x07; // set prescaler to 1/128
    ADCSRA |= 0x20; // enable free-running conversions
    ADCSRA |= 0x08; // enable ADC interrupt
    ADCSRA |= 0x40; // start the first conversion
 
    // give us a chance to calibrate our sensor
    getchar();
    calibrating = 0;
    int mid_x = x;
    int mid_y = y;

    // print the cursor
    printf("\e[?25l\e[40;12f0");
    int last_x, last_y;
    int cursor_x, cursor_y;
    for (;;) {
        last_x = cursor_x;
        last_y = cursor_y;
        cursor_x = 40 - 80 * (x - mid_x) / (max_x - min_x);
        cursor_y = 12 + 24 * (y - mid_y) / (max_y - min_y);
        if (last_x != cursor_x || last_y != cursor_y) {
            printf("\e[1D.");
            printf("\e[%d;%dfX", cursor_y, cursor_x);
        }
    }
}
