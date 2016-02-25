/**
Write a sequence to generate a 100KHz waveform with 50% duty cycle from
the OC0A pin. Assume clock = 16MHz.
Solution:
-Configure timer 0 in CTC Mode
- Set the prescaler to 1, so we don't divide the clock
- Figure out how many clock periods need to pass before our signal
toggles to get the correct frequency
- Set the OCR0A register so our counter waits the correct time between
square wave edges
*/

int main() {
 DDRD |= 0x40; // set OC0A as output
 TCCR0A |= 0x40; // toggle the pin on reset
 TCCR0A |= 0x02; // use CTC mode
 TCCR0B |= 0x01; // turn the timer on
 OCR0A = 79; // set the period of resets to get 100kHz
 for (;;);
}