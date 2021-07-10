#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>

#include "generator.h"
#include "sleep.h"
#include "timer.h"

#define POWER_BLINK 0

// Output frequencies can be multiplied with this factor if necessary
#define SPEED_FACTOR 1.0

#define PWM_SIZE (256)
#define PWM_FREQ (F_OSC / PWM_SIZE)

SIN_U8_DATA(sine_normal, 0.8);
SIN_U8_DATA(sine_slow, 0.6);
SIN_U8_DATA(sine_fast, 1.0);

static const uint32_t __flash phase_inc[] = {
    /* slow     */ COMPUTE_PHASE_INCREMENT(SPEED_FACTOR * 37.5000, PWM_SIZE),
    /* sidereal */ COMPUTE_PHASE_INCREMENT(SPEED_FACTOR * 50.1369, PWM_SIZE),
    /* lunar    */ COMPUTE_PHASE_INCREMENT(SPEED_FACTOR * 48.3018, PWM_SIZE),
    /* solar    */ COMPUTE_PHASE_INCREMENT(SPEED_FACTOR * 50.0000, PWM_SIZE),
    /* fast     */ COMPUTE_PHASE_INCREMENT(SPEED_FACTOR * 62.5000, PWM_SIZE),
};

static const uint8_t __flash* const __flash sine_data[] = {
    /* slow     */ sine_slow,
    /* sidereal */ sine_normal,
    /* lunar    */ sine_normal,
    /* solar    */ sine_normal,
    /* fast     */ sine_fast,
};

static struct generator_state s_gen;
static uint8_t s_baseline;
static uint8_t s_output;
#if POWER_BLINK
static uint16_t s_power;
#endif
static uint16_t s_new_index_timer;
static uint16_t s_startup_timer;
static uint8_t s_startup_finished;

ISR(TIMER_OVERFLOW_VECTOR) {
  PWM_OUTPUT_REG = s_output ? generator_generate(&s_gen) : s_baseline;
  wdt_reset();

#if POWER_BLINK
  s_power++;
  if (s_power & 0xE000) {
    PORTA |= (1 << PA0); // Power
  } else {
    PORTA &= ~(1 << PA0); // Power
  }
#endif

  if (s_new_index_timer > 0) {
    s_new_index_timer--;
  }

  if (s_startup_timer > 0) {
    if (--s_startup_timer == 0) {
      s_startup_finished = 1;
    }
  }
}

static void idle_loop(void) {
  // Initialize so that we force a pin change. This ensures we set
  // an initial phase increment and enable interrupts.
  uint8_t last_pin = 255;

  // The active index chosen by the external switch
  uint8_t active_index = 0;

  // The new candidate index
  uint8_t new_index = active_index;

  for (;;) {
    /*
     *  ~PINA       Switch
     *   7654     Pos   Index   Speed
     *  -----------------------------------------
     *   0000     0     0       off
     *   0100     1     1       sidereal
     *   1100     2     3       solar
     *   1000     3     2       lunar
     *   xx10     -     -       fast  (xx != 00)
     *   xx01     -     -       slow  (xx != 00)
     */
    uint8_t pin = (~PINA) & 0xF0;

    if (pin != last_pin || (new_index != active_index && s_new_index_timer == 0)
        || s_startup_finished) {
      s_startup_finished = 0;

      uint8_t index = pin >> 6;

      if (index != new_index) {
        /*
         * External switch position has changed. When turning the knob,
         * it'll briefly open all switches before it locks into the next
         * position. In order to avoid major output signal glitches,
         * we'll wait for 100ms for the switch position to settle.
         */
        new_index = index;
        cli();
        s_new_index_timer = PWM_FREQ / 10;
        sei();
      }

      if (new_index != active_index && s_new_index_timer == 0) {
        if (active_index == 0) {
          STATIC_ASSERT(PWM_FREQ <= 0xFFFF);
          s_startup_timer = PWM_FREQ;
        }

        active_index = new_index;
      }

      // Handle ST4 inputs
      switch (pin & 0x30) {
        case 0x20: // fast
          PORTA |= (1 << PA3);
          index = 4;
          break;
        case 0x10: // slow
          PORTA |= (1 << PA1);
          index = 0;
          break;

        default:
          // clear ST4 indicator LEDs
          PORTA &= ~((1 << PA3) | (1 << PA1));
          index = active_index;
          break;
      }

      if (active_index > 0) {
        // Output is enabled
        PORTA |= (1 << PA2);

        // Disable interrupts here so we don't race with ISR
        cli();
        s_output = 1;
        generator_set_phase_increment(&s_gen, phase_inc[index]);
        generator_set_sine(
            &s_gen, s_startup_timer > 0 ? sine_fast : sine_data[index]);
        sei();
      } else {
        // Output is disabled
        PORTA &= ~(1 << PA2);

        // Disable interrupts here so we don't race with ISR
        cli();
        s_output = 0;
        generator_init(&s_gen);
        sei();
      }

      last_pin = pin;
    }
  }
}

int main(void) {
  // Set status LED outputs
  DDRA = (1 << DDA3) | (1 << DDA2) | (1 << DDA1) | (1 << DDA0);

  // Set PB2 as output for PWM
  DDRB = (1 << DDB2);

  // Toggle through LEDs once to make sure everything's working
  for (uint8_t i = 0; i < 4; ++i) {
    PORTA |= 1 << (i & 0x3);
    millisleep(250);
    PORTA &= 0xF0;
  }

  // Initialize generator
  generator_init(&s_gen);

  // Set up timer for fast PWM
  timer_pwm_init();

  // Enable interrupts
  sei();

  // Toggle through LEDs while we ramp up the baseline
  for (uint8_t i = 0; i < 16; ++i) {
    PORTA |= 1 << (i & 0x3);
    for (uint8_t j = 0; j < 8; ++j) {
      s_baseline = 8 * i + j;
      millisleep(31);
    }
    PORTA &= 0xF0;
  }

  // Enable pullups on PA4/PA5 (ST4) and PA6/PA7 (Mode Switch)
  PORTA |= (1 << PA7) | (1 << PA6) | (1 << PA5) | (1 << PA4);

  // Enable watchdog timer with 16ms timeout
  WDTCSR = (1 << WDE);

#if !POWER_BLINK
  PORTA |= (1 << PA0); // Power LED on
#endif

  // Run idle loop
  idle_loop();

  return 0;
}
