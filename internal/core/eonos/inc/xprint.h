#ifndef __XPRINT_H_
#define __XPRINT_H_

#include "xstr.h"

// ===============================================================================
// Macros
// ===============================================================================

#define FL(__x__) ((int) ((__x__) *100))
// #define USE_FLOAT_XSPRINTF

// ===============================================================================
// Types
// ===============================================================================

// writeFn type definition
typedef void (*writeFn)(unsigned char c);

// ===============================================================================
// Functions
// ===============================================================================

// Print a string
void xfprint(writeFn wr, const char *s);
// Print an unsigned integer with a specified base
void xfprintUint(writeFn wr, uint32_t num, uint8_t base);
// Print an integer with a specified base
void xfprintInt(writeFn wr, int64_t num, uint8_t base);
// Print with format
void xfprintf(writeFn wr, const char *format, ...);
// Print with format into a xstring
void xsprintf(xstr_t *xs, const char *format, ...);

// ===============================================================================
// Static inline Functions
// ===============================================================================

// Print a string ending with a new line
__STATIC_INLINE void xfprintln(writeFn wr, const char *s) {
  xfprint(wr, s);
  wr('\r');
  wr('\n');
}
// Print an unsigned integer ending with a new line
__STATIC_INLINE void xfprintlnUint(writeFn wr, uint32_t num, uint8_t base) {
  xfprintUint(wr, num, base);
  wr('\r');
  wr('\n');
}
// Print an integer ending with a new line
__STATIC_INLINE void xfprintlnInt(writeFn wr, uint32_t num, uint8_t base) {
  xfprintInt(wr, num, base);
  wr('\r');
  wr('\n');
}

#endif