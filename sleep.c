#include "sleep.h"

void sleep(uint16_t seconds) {
  while (seconds--) {
    millisleep(1000);
  }
}

void millisleep(uint16_t milliseconds) {
  while (milliseconds--) {
    microsleep(1000);
  }
}
