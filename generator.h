#pragma once

#include <stdint.h>

/*
 * This data represents the first quarter of one sine wave period with an
 * amplitude of 127.5. The number of samples is chosen to be a power of 2
 * and to be large enough so that the whole range of values is covered.
 *
 * The first sample does *not* correspond to an argument of 0, but rather
 * pi/1024. This allows us to compute all 4 quarters from the same data
 * while covering the full value range [0, 255].
 *
 *    1   2   3   4
 *   --- --- --- ---
 *   0 1 1 0 0 1 1 0
 *     * *
 *   *_____*________
 *           *     *
 *             * *
 *   0 1 2 3 4 5 6 7
 *
 * The data was generated using the following Perl code:
 *
 *   for(0..255){printf"(uint8_t)((g)*%.3f),",127.5*sin(($_+.5)*atan2(1,1)/128)}
 */
#define SIN_U8_DATA(name, g)                                                   \
  static uint8_t const __flash name[256] = {                                   \
      (uint8_t)((g)*0.391),   (uint8_t)((g)*1.173),   (uint8_t)((g)*1.956),    \
      (uint8_t)((g)*2.738),   (uint8_t)((g)*3.520),   (uint8_t)((g)*4.302),    \
      (uint8_t)((g)*5.084),   (uint8_t)((g)*5.865),   (uint8_t)((g)*6.647),    \
      (uint8_t)((g)*7.428),   (uint8_t)((g)*8.209),   (uint8_t)((g)*8.989),    \
      (uint8_t)((g)*9.770),   (uint8_t)((g)*10.549),  (uint8_t)((g)*11.329),   \
      (uint8_t)((g)*12.108),  (uint8_t)((g)*12.886),  (uint8_t)((g)*13.664),   \
      (uint8_t)((g)*14.442),  (uint8_t)((g)*15.219),  (uint8_t)((g)*15.996),   \
      (uint8_t)((g)*16.771),  (uint8_t)((g)*17.547),  (uint8_t)((g)*18.321),   \
      (uint8_t)((g)*19.095),  (uint8_t)((g)*19.868),  (uint8_t)((g)*20.641),   \
      (uint8_t)((g)*21.412),  (uint8_t)((g)*22.183),  (uint8_t)((g)*22.953),   \
      (uint8_t)((g)*23.722),  (uint8_t)((g)*24.490),  (uint8_t)((g)*25.258),   \
      (uint8_t)((g)*26.024),  (uint8_t)((g)*26.789),  (uint8_t)((g)*27.554),   \
      (uint8_t)((g)*28.317),  (uint8_t)((g)*29.079),  (uint8_t)((g)*29.840),   \
      (uint8_t)((g)*30.600),  (uint8_t)((g)*31.359),  (uint8_t)((g)*32.117),   \
      (uint8_t)((g)*32.873),  (uint8_t)((g)*33.629),  (uint8_t)((g)*34.383),   \
      (uint8_t)((g)*35.135),  (uint8_t)((g)*35.887),  (uint8_t)((g)*36.637),   \
      (uint8_t)((g)*37.385),  (uint8_t)((g)*38.133),  (uint8_t)((g)*38.878),   \
      (uint8_t)((g)*39.623),  (uint8_t)((g)*40.366),  (uint8_t)((g)*41.107),   \
      (uint8_t)((g)*41.847),  (uint8_t)((g)*42.585),  (uint8_t)((g)*43.322),   \
      (uint8_t)((g)*44.057),  (uint8_t)((g)*44.790),  (uint8_t)((g)*45.521),   \
      (uint8_t)((g)*46.251),  (uint8_t)((g)*46.980),  (uint8_t)((g)*47.706),   \
      (uint8_t)((g)*48.431),  (uint8_t)((g)*49.153),  (uint8_t)((g)*49.874),   \
      (uint8_t)((g)*50.593),  (uint8_t)((g)*51.310),  (uint8_t)((g)*52.026),   \
      (uint8_t)((g)*52.739),  (uint8_t)((g)*53.450),  (uint8_t)((g)*54.159),   \
      (uint8_t)((g)*54.867),  (uint8_t)((g)*55.572),  (uint8_t)((g)*56.275),   \
      (uint8_t)((g)*56.976),  (uint8_t)((g)*57.675),  (uint8_t)((g)*58.371),   \
      (uint8_t)((g)*59.066),  (uint8_t)((g)*59.758),  (uint8_t)((g)*60.448),   \
      (uint8_t)((g)*61.135),  (uint8_t)((g)*61.821),  (uint8_t)((g)*62.504),   \
      (uint8_t)((g)*63.185),  (uint8_t)((g)*63.863),  (uint8_t)((g)*64.539),   \
      (uint8_t)((g)*65.212),  (uint8_t)((g)*65.883),  (uint8_t)((g)*66.552),   \
      (uint8_t)((g)*67.218),  (uint8_t)((g)*67.881),  (uint8_t)((g)*68.542),   \
      (uint8_t)((g)*69.201),  (uint8_t)((g)*69.856),  (uint8_t)((g)*70.510),   \
      (uint8_t)((g)*71.160),  (uint8_t)((g)*71.808),  (uint8_t)((g)*72.453),   \
      (uint8_t)((g)*73.095),  (uint8_t)((g)*73.735),  (uint8_t)((g)*74.372),   \
      (uint8_t)((g)*75.006),  (uint8_t)((g)*75.637),  (uint8_t)((g)*76.265),   \
      (uint8_t)((g)*76.891),  (uint8_t)((g)*77.514),  (uint8_t)((g)*78.133),   \
      (uint8_t)((g)*78.750),  (uint8_t)((g)*79.364),  (uint8_t)((g)*79.975),   \
      (uint8_t)((g)*80.582),  (uint8_t)((g)*81.187),  (uint8_t)((g)*81.789),   \
      (uint8_t)((g)*82.387),  (uint8_t)((g)*82.983),  (uint8_t)((g)*83.575),   \
      (uint8_t)((g)*84.165),  (uint8_t)((g)*84.751),  (uint8_t)((g)*85.334),   \
      (uint8_t)((g)*85.913),  (uint8_t)((g)*86.490),  (uint8_t)((g)*87.063),   \
      (uint8_t)((g)*87.633),  (uint8_t)((g)*88.199),  (uint8_t)((g)*88.763),   \
      (uint8_t)((g)*89.323),  (uint8_t)((g)*89.879),  (uint8_t)((g)*90.432),   \
      (uint8_t)((g)*90.982),  (uint8_t)((g)*91.528),  (uint8_t)((g)*92.071),   \
      (uint8_t)((g)*92.611),  (uint8_t)((g)*93.147),  (uint8_t)((g)*93.679),   \
      (uint8_t)((g)*94.208),  (uint8_t)((g)*94.734),  (uint8_t)((g)*95.255),   \
      (uint8_t)((g)*95.774),  (uint8_t)((g)*96.288),  (uint8_t)((g)*96.799),   \
      (uint8_t)((g)*97.307),  (uint8_t)((g)*97.810),  (uint8_t)((g)*98.310),   \
      (uint8_t)((g)*98.807),  (uint8_t)((g)*99.299),  (uint8_t)((g)*99.788),   \
      (uint8_t)((g)*100.273), (uint8_t)((g)*100.754), (uint8_t)((g)*101.232),  \
      (uint8_t)((g)*101.706), (uint8_t)((g)*102.175), (uint8_t)((g)*102.641),  \
      (uint8_t)((g)*103.104), (uint8_t)((g)*103.562), (uint8_t)((g)*104.016),  \
      (uint8_t)((g)*104.467), (uint8_t)((g)*104.913), (uint8_t)((g)*105.356),  \
      (uint8_t)((g)*105.795), (uint8_t)((g)*106.229), (uint8_t)((g)*106.660),  \
      (uint8_t)((g)*107.086), (uint8_t)((g)*107.509), (uint8_t)((g)*107.928),  \
      (uint8_t)((g)*108.342), (uint8_t)((g)*108.752), (uint8_t)((g)*109.159),  \
      (uint8_t)((g)*109.561), (uint8_t)((g)*109.959), (uint8_t)((g)*110.353),  \
      (uint8_t)((g)*110.743), (uint8_t)((g)*111.128), (uint8_t)((g)*111.510),  \
      (uint8_t)((g)*111.887), (uint8_t)((g)*112.260), (uint8_t)((g)*112.629),  \
      (uint8_t)((g)*112.993), (uint8_t)((g)*113.354), (uint8_t)((g)*113.710),  \
      (uint8_t)((g)*114.061), (uint8_t)((g)*114.409), (uint8_t)((g)*114.752),  \
      (uint8_t)((g)*115.091), (uint8_t)((g)*115.425), (uint8_t)((g)*115.755),  \
      (uint8_t)((g)*116.081), (uint8_t)((g)*116.403), (uint8_t)((g)*116.720),  \
      (uint8_t)((g)*117.032), (uint8_t)((g)*117.341), (uint8_t)((g)*117.644),  \
      (uint8_t)((g)*117.944), (uint8_t)((g)*118.239), (uint8_t)((g)*118.529),  \
      (uint8_t)((g)*118.815), (uint8_t)((g)*119.097), (uint8_t)((g)*119.374),  \
      (uint8_t)((g)*119.646), (uint8_t)((g)*119.915), (uint8_t)((g)*120.178),  \
      (uint8_t)((g)*120.437), (uint8_t)((g)*120.692), (uint8_t)((g)*120.942),  \
      (uint8_t)((g)*121.187), (uint8_t)((g)*121.428), (uint8_t)((g)*121.664),  \
      (uint8_t)((g)*121.896), (uint8_t)((g)*122.123), (uint8_t)((g)*122.345),  \
      (uint8_t)((g)*122.563), (uint8_t)((g)*122.777), (uint8_t)((g)*122.985),  \
      (uint8_t)((g)*123.189), (uint8_t)((g)*123.389), (uint8_t)((g)*123.583),  \
      (uint8_t)((g)*123.773), (uint8_t)((g)*123.959), (uint8_t)((g)*124.140),  \
      (uint8_t)((g)*124.316), (uint8_t)((g)*124.487), (uint8_t)((g)*124.654),  \
      (uint8_t)((g)*124.816), (uint8_t)((g)*124.973), (uint8_t)((g)*125.126),  \
      (uint8_t)((g)*125.274), (uint8_t)((g)*125.417), (uint8_t)((g)*125.555),  \
      (uint8_t)((g)*125.689), (uint8_t)((g)*125.818), (uint8_t)((g)*125.942),  \
      (uint8_t)((g)*126.062), (uint8_t)((g)*126.177), (uint8_t)((g)*126.287),  \
      (uint8_t)((g)*126.392), (uint8_t)((g)*126.493), (uint8_t)((g)*126.588),  \
      (uint8_t)((g)*126.679), (uint8_t)((g)*126.766), (uint8_t)((g)*126.847),  \
      (uint8_t)((g)*126.924), (uint8_t)((g)*126.996), (uint8_t)((g)*127.063),  \
      (uint8_t)((g)*127.125), (uint8_t)((g)*127.183), (uint8_t)((g)*127.235),  \
      (uint8_t)((g)*127.283), (uint8_t)((g)*127.327), (uint8_t)((g)*127.365),  \
      (uint8_t)((g)*127.399), (uint8_t)((g)*127.427), (uint8_t)((g)*127.451),  \
      (uint8_t)((g)*127.471), (uint8_t)((g)*127.485), (uint8_t)((g)*127.495),  \
      (uint8_t)((g)*127.499)}

struct generator_state {
  uint8_t const __flash* sine;
  uint8_t const __flash* new_sine;
  // Phase Accumulator. This will use (26 + GENERATOR_EXTRA_ACCURACY_BITS)
  // effective bits. The only advantage of setting GENERATOR_EXTRA_ACCURACY_BITS
  // to a value less than 6 is that is saves some code space.
  union {
    uint32_t phase;
    struct {
      uint16_t lower; // LSW
      uint16_t upper; // MSW
    } words;
    struct {
      uint8_t b0; // LSB
      uint8_t b1;
      uint8_t b2;
      uint8_t b3; // MSB
    } bytes;
  } p;
  uint32_t phase_increment;
};

#ifndef GENERATOR_EXTRA_ACCURACY_BITS
#define GENERATOR_EXTRA_ACCURACY_BITS 6
#endif

#if GENERATOR_EXTRA_ACCURACY_BITS > 6
#error "Cannot support more than 6 extra bits of accuracy"
#endif

#define COMPUTE_PHASE_INCREMENT(frequency, pwm_size)                           \
  ((uint32_t)(((double)(frequency) * (pwm_size) * (UINT64_C(1) << (26 + GENERATOR_EXTRA_ACCURACY_BITS)) + (F_OSC) / 2) / (F_OSC)))

void generator_init(struct generator_state* st);
void generator_set_sine(
    struct generator_state* st, uint8_t const __flash* sine);
void generator_set_phase_increment(
    struct generator_state* st, uint32_t phase_increment);
uint8_t generator_generate(struct generator_state* st);
