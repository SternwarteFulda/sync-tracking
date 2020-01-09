#pragma once

#include <avr/interrupt.h>
#include <avr/io.h>

#define TIMER_OVERFLOW_VECTOR TIM0_OVF_vect
#define PWM_OUTPUT_REG OCR0A

void timer_pwm_init(void);
