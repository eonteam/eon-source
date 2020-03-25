#include "xrand.h"

// ===============================================================================
// Functions
// ===============================================================================

// Set xrand seed for random number generation
//
void xrand_seed(uint32_t seed) {
  if (seed != 0) { srand(seed); }
}

// Get an integer random number
//
int xrand_int(int howsmall, int howbig) {
  if (howsmall >= howbig) { return howsmall; }
  howbig = howbig - howsmall;
  return (rand() % howbig) + howsmall;
}