//example configuraton for fast pwm mode
#include <avr/io.h>
#include <util/delay.h>
int main() {
  DDRD |= 0x40; // set OC0A as output
  TCCR0A |= 0x80; // use non-inverting output
  TCCR0A |= 0x03; // use fast PWM mode
  TCCR0B |= 0x01; // turn the timer on
  OCR0A = 0xff; // 100% duty cycle
  _delay_ms(1000);
  OCR0A = 0xe6; // 90% duty cycle
  _delay_ms(2000);
  OCR0A = 0xb4; // 70% duty cycle

 // continue until we get to 0% duty cycle
}