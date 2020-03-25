/**
  ******************************************************************************
  * @file    utils.h 
  * @author  EonTeam
	* @version V1.0.0
  * @date    2020
  ******************************************************************************
*/

#ifndef __EON_UTILS_H
#define __EON_UTILS_H

#include "system.h"
#include <stdint.h>
#include <stdlib.h>

// ===============================================================================
// Macros
// ===============================================================================

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
#define radians(deg) ((deg) *DEG_TO_RAD)
#define degrees(rad) ((rad) *RAD_TO_DEG)
#define sq(x) ((x) * (x))

#define lowByte(w) ((uint8_t)((w) &0xff))
#define highByte(w) ((uint8_t)((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

// ===============================================================================
// Static inline Functions
// ===============================================================================

// -- General functions

// Map function execute the slope-intercept equation.
__STATIC_INLINE long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// -- Words related functions

// Make a half word from two bytes (high and low).
__STATIC_INLINE uint16_t makeHalfWord(uint8_t h, uint8_t l) {
  return (h << 8) | l;
}

// Get the low half word of a word
__STATIC_INLINE uint16_t lowHalfWord(uint32_t w) {
  return (uint16_t)((w) &0xFFFF);
}

// Get the high half word of a word
__STATIC_INLINE uint16_t highHalfWord(uint32_t w) {
  return (uint16_t)((w) >> 16);
}

#endif