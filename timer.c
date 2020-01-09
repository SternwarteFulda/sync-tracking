#include "timer.h"

void timer_pwm_init(void) {
  // Set up Timer0 for non-inverting, fast PWM mode with prescaler=1
  TCCR0A = (1 << COM0A1) | (0 << COM0A0) | (1 << WGM01) | (1 << WGM00);
  TCCR0B = (0 << WGM02) | (0 << CS02 | (0 << CS01)) | (1 << CS00);

  // Enable TOV0 interrupt
  TIMSK0 = (1 << TOIE0);
}
