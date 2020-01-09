#pragma once

#include <stdint.h>

void sleep(uint16_t seconds);

void millisleep(uint16_t milliseconds);

static inline void
sleep_four_cycles(uint16_t loops) __attribute__((always_inline));

static inline void sleep_four_cycles(uint16_t loops) {
  asm volatile("1: sbiw %0, 1 \n\t"
               "   brne 1b    \n\t"
               : "=w"(loops)
               : "0"(loops));
}

#define STATIC_ASSERT(cond) _Static_assert(cond, #cond)

#define microsleep(microseconds)                                               \
  do {                                                                         \
    STATIC_ASSERT(microseconds <= ((uint64_t)UINT16_MAX * 4000000UL) / F_OSC); \
    sleep_four_cycles(((uint64_t)F_OSC * microseconds) / 4000000UL);           \
  } while (0)

#define nanosleep(nanoseconds)                                                 \
  do {                                                                         \
    STATIC_ASSERT(                                                             \
        nanoseconds <= ((uint64_t)UINT16_MAX * 4000000000UL) / F_OSC);         \
    sleep_four_cycles(((uint64_t)F_OSC * nanoseconds) / 4000000000UL);         \
  } while (0)
