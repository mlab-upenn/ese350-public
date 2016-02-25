/* estimate frequency of a signal */
#include <avr/io.h>
unsigned int frequency;
void main(void) {
  uart_init();
  char arr[7];
  char *msg = "Signal frequency is ";
  int i, oc_cnt;
  TCCR1A = 0x40; /* enable OC1A0 for Output Compare */
  TCCR1B = 0x02; /* set prescale factor to 8 */
  oc_cnt = 100; /* prepare perform 100 OC1 operations */
  frequency = 0;
  TCCR1B |= 0x40; /* input capture on rising edge */
  TIMSK1 |= 0x22; /* enable IC0 and OC1A interrupts */
  sei();

  OCR1A = TCNT + 60000; /* 60,000*1/6MHz = 10ms */
  while (oc_cnt) { /* 100 * 10ms = 1s */
    while(!(TIFR1 && C1F));
    OCR1A += 60000;
    oc_cnt--;
  }
  int2alpha(frequency, arr);
  puts(msg);
  puts(&arr[0]);
  while(1);
}