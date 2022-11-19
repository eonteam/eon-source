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

#include <stdint.h>
#include <stdlib.h>

// ===============================================================================
// Macros
// ===============================================================================

// Macros for GNU compiler
#if defined(__GNUC__)
#ifndef __weak
#define __weak __attribute__((weak))
#endif
#ifndef __packed
#define __packed __attribute__((__packed__))
#endif
#endif

// IRQ Macro for IRQ handlers
#define IRQ(__IRQ__) __IRQ__()

// For unused variables
#if !defined(USE_HAL_DEF_UNUSED_MACRO) && !defined(UNUSED)
#define UNUSED(__X__) ((void) (__X__))
#endif

/// @brief No pin macro
/// @deprecated This will be deleted in the next update in favor of PIN_NONE defined in platform code.
#define NOPIN ((uint8_t) 255)

#ifndef IGNORE
/// @brief Ignore Macro
/// @deprecated This will be deleted in the next update in favor of PIN_NONE defined in platform code.
#define IGNORE ((uint8_t) 255)
#endif

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

#define lowByte(w) ((uint8_t) ((w) &0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

// ===============================================================================
// Types
// ===============================================================================

// write function type definition
typedef void (*writeFn_t)(unsigned char c);
// available function type definition
typedef uint16_t (*availableFn_t)(void);
// read function type definition
typedef int (*readFn_t)(void);

// ===============================================================================
// Static inline Functions
// ===============================================================================

// -- General functions

// Map function execute the slope-intercept equation.
static inline long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// -- Words related functions

// Make a half word from two bytes (high and low).
static inline uint16_t makeHalfWord(uint8_t h, uint8_t l) {
  return (h << 8) | l;
}

// Get the low half word of a word
static inline uint16_t lowHalfWord(uint32_t w) {
  return (uint16_t) ((w) &0xFFFF);
}

// Get the high half word of a word
static inline uint16_t highHalfWord(uint32_t w) {
  return (uint16_t) ((w) >> 16);
}

// ===============================================================================
// Functions
// ===============================================================================

// Converts BCD format to binary
uint8_t bcd2bin(uint8_t val);

// Converts binary to BCD format
uint8_t bin2bcd(uint8_t val);

#endif
