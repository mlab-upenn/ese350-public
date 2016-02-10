/** generate a sequence of pulses */

#define DelayHi 18000 // high time of the pulses to be created
#define DelayLo 12000 // low time of the pulses to be created
#define NN 10 // number of pulses to be created

int pcnt; // pulse count
char HiorLo; // flag to choose


ISR (TIMER0_COMPA_vect){
  if(HiorLo){
    OCR0A += DelayHi;
    HiorLo = 0;
  } else {
    OCR0A += DelayLo;
    HiorLo = 1;
  }
  pcnt--;
  if(pcnt == 0){
    TIMSK0 &= ~0x02; // disable OC0A interrupt
    TCCR0A &= ~0x80; // disable OC0A
  }
}

void main(void)
{
  TCCR0A = 0x40; // enable output compare on OC0A
  TCCR0B = 0x02; // set prescalar to 8 for channel 0 (1.5MHz)
  OCR0A = TCNT + 16; // pull PT0 pin high quickly
  while(!(TFLG1 && C0F));
  pcnt = 2 * NN – 1; // prepare to create NN pulses (toggle 2*NN - 1 times)
  OCR0A += DelayHi; // start the second OC0 operation
  HiorLo = 0; // next time use DelayLo as delay count of OC0 operation
  TIMSK0 |= 0x02; // enable interrupt for OC0A
  sei(); // enable interrupts

  while (1); // do nothing or do something else
}