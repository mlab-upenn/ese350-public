/* estimate frequency of a signal */
#include <avr/io.h>
#define HiFreq 1250
#define LoFreq 5000
int delay; // delay count for OC5 operation
ISR(TIMER1_OVF_VECT) {
  OCR1A += delay;
}
void main(void) {
  TCCR1A = 0x40; // enable TCNT and toggle on compare match
  TCCR1B = 0x02; // set prescaler to TCNT to 1:8
  delay = HiFreq; // use high frequency delay count first
  OCR1A = TCNT1 + delay; // start an OC1A operation
  TIMSK1 |= 0x02; // enable TC5 interrupt
  sei();

  while(1) {
    delayby100ms(5); // wait for half a second
    delay = LoFreq; // switch to low-frequency tone
    delayby100ms(5); // wait for half a second
  delay = HiFreq; // switch to high-frequency tone
  }
} 