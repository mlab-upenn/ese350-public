/* pwm example 2: 
 * Use the Fast PWM mode of Timer0 to generate a
 * 100Hz PWM signal at 20% duty cycle
*/
int main() {
  DDRD |= 0x20; // set OC0B as output
  TCCR0A |= 0x20; // use a non-inverting signal
  TCCR0A |= 0x03; // use fast PWM mode
  TCCR0B |= 0x08;
  TCCR0B |= 0x05; // turn the timer on, use prescaler 1024
  OCR0A = 155; // set the period of resets to get 100Hz
  OCR0B = OCR0A / 5; // set the duty cycle to 20%
  for (;;);
}