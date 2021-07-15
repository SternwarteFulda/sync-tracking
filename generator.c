#include "generator.h"

static uint8_t sinval(uint8_t const __flash* sine, uint16_t x) {
  // As our sine wave has a period of 1024, we don't have to deal with values
  // larger than 1023 explicitly. The uint16_t argument will simply cover
  // between 1 and 64 sine periods, depending on GENERATOR_EXTRA_ACCURACY_BITS.
  uint8_t ix = x & 0xff;
  if (x & 0x0100) {
    // 2nd and 4th quarters index backwards into the array
    ix = 255 - ix;
  }
  uint8_t val = sine[ix];
  // 3rd and 4th quarters are negative
  return x & 0x0200 ? 127 - val : 128 + val;
}

void generator_init(struct generator_state* st) {
  st->p.phase = 0;
}

void generator_set_sine(
    struct generator_state* st, uint8_t const __flash* sine) {
  st->new_sine = sine;
  if (st->p.phase == 0) {
    st->sine = sine;
  }
  // Otherwise delay switch to `new_sine` until we have a zero crossing.
}

void generator_set_phase_increment(
    struct generator_state* st, uint32_t phase_increment) {
  st->phase_increment = phase_increment;
}

uint8_t generator_generate(struct generator_state* st) {
  uint8_t sine_half = st->p.bytes.b3 & (0x02 << GENERATOR_EXTRA_ACCURACY_BITS);
  uint8_t rv
      = sinval(st->sine, st->p.words.upper >> GENERATOR_EXTRA_ACCURACY_BITS);
  st->p.phase += st->phase_increment;
  if ((st->p.bytes.b3 & (0x02 << GENERATOR_EXTRA_ACCURACY_BITS)) != sine_half) {
    st->sine = st->new_sine;
  }
  return rv;
}
