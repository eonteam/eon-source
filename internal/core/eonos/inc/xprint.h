#ifndef __XPRINT_H_
#define __XPRINT_H_

#include "utils.h"
#include "xstr.h"

// ===============================================================================
// Macros
// ===============================================================================

#define FL(__x__) ((int) ((__x__) *100))
// #define USE_FLOAT_XSPRINTF

// ===============================================================================
// Functions
// ===============================================================================

// Print a string
void xfprint(writeFn_t wr, const char *s);
// Print an unsigned integer with a specified base
void xfprintUint(writeFn_t wr, uint32_t num, uint8_t base);
// Print an integer with a specified base
void xfprintInt(writeFn_t wr, int64_t num, uint8_t base);
// Print with format
void xfprintf(writeFn_t wr, const char *format, ...);
// Print with format into a xstring
void xsprintf(xstr_t *xs, const char *format, ...);

// ===============================================================================
// Static inline Functions
// ===============================================================================

// Print a string ending with a new line
__STATIC_INLINE void xfprintln(writeFn_t wr, const char *s) {
  xfprint(wr, s);
  wr('\r');
  wr('\n');
}
// Print an unsigned integer ending with a new line
__STATIC_INLINE void xfprintlnUint(writeFn_t wr, uint32_t num, uint8_t base) {
  xfprintUint(wr, num, base);
  wr('\r');
  wr('\n');
}
// Print an integer ending with a new line
__STATIC_INLINE void xfprintlnInt(writeFn_t wr, int64_t num, uint8_t base) {
  xfprintInt(wr, num, base);
  wr('\r');
  wr('\n');
}

#endif