#ifndef __XRAND_H_
#define __XRAND_H_

#include <stdint.h>
#include <stdlib.h>

// ===============================================================================
// Functions
// ===============================================================================

// Set xrand seed for random number generation
void xrand_seed(uint32_t seed);
// Get an integer random number
int xrand_int(int howsmall, int howbig);

#endif