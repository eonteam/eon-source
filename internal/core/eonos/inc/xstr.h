#ifndef __XSTR_H_
#define __XSTR_H_

#include "system.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// ===============================================================================
// Initializers
// ===============================================================================

// Initiliaze empty xstring with a predefined capacity.
#define XSTR_INITIALIZER(__CAP__) \
  {                               \
    .ptr = (char[__CAP__]){},     \
    .len = 0,                     \
    .cap = __CAP__                \
  }

// Initiliaze a constant xstring with a string passed.
#define XSTR_CONST(__S__)           \
  (const xstr_t) {                  \
    .ptr = (char[]){__S__},         \
    .len = strlen((char[]){__S__}), \
    .cap = strlen((char[]){__S__})  \
  }

// ===============================================================================
// Iterators
// ===============================================================================

// Iterate a xstring over its elements.
#define XSTR_ITER(__XS__, __IDX__) \
  xstrsize_t(__IDX__) = 0;         \
  (__IDX__) < ((__XS__)->len);     \
  (__IDX__)++

// Iterate a xstring over its elements starting from a position.
#define XSTR_ITERFROM(__XS__, __IDX__, __FROM__) \
  xstrsize_t(__IDX__) = (__FROM__);              \
  (__IDX__) < ((__XS__)->len);                   \
  (__IDX__)++

// ===============================================================================
// Types
// ===============================================================================

// type of xstr size
typedef uint8_t xstrsize_t;

// xstr main type
typedef struct {
  char *ptr;                // private DO NOT EDIT THIS MANUALLY
  xstrsize_t len;           // private DO NOT EDIT THIS MANUALLY
  /*const*/ xstrsize_t cap; // private DO NOT EDIT THIS MANUALLY (must be constant)
} xstr_t;

// ===============================================================================
// Static inline functions
// ===============================================================================

// -- For general purpose

// Check if the char variable passed is a numeric digit or not.
__STATIC_INLINE bool isCharNumber(char c) {
  return (c >= '0' && c <= '9');
}

__STATIC_INLINE void swap(char *x, char *y) {
  char t = *x;
  *x = *y;
  *y = t;
}

// -- For accessing elements

// Returns the char at the index specified.
__STATIC_INLINE char xstr_charAt(const xstr_t *xs, xstrsize_t index) {
  return xs->ptr[index];
}
// Returns the length of the xstring.
__STATIC_INLINE xstrsize_t xstr_len(const xstr_t *xs) {
  return xs->len;
}
// Returns the capacity of the xstring.
__STATIC_INLINE xstrsize_t xstr_cap(const xstr_t *xs) {
  return xs->cap;
}

// ===============================================================================
// Public functions
// ===============================================================================

// -- General purpose

// Remove the last char inside the xstring, and return it.
char xstr_pop(xstr_t *xs);
// Reverse xstring.
void xstr_reverse(xstr_t *xs);
// Clear the xstring with zeros and reset its length.
void xstr_clear(xstr_t *xs);

// -- Push functions

// Pushes a char into the xstring.
bool xstr_push(xstr_t *xs, char c);
// Pushes a string (const char*) into the xstring.
bool xstr_pushString(xstr_t *xs, const char *s);
// Pushes "other" into the "xs".
bool xstr_pushX(xstr_t *xs, const xstr_t *other);
// Pushes an unsigned integer into the xstring.
bool xstr_pushUint(xstr_t *xs, uint32_t num, uint8_t base);
// Pushes an integer into the xstring.
bool xstr_pushInt(xstr_t *xs, int64_t num, uint8_t base);
// Pushes a float into the xstring.
bool xstr_pushFloat(xstr_t *xs, float num, uint8_t dp);
// Create a slice from `xs`, note that they will share the same buffer pointer.
bool xstr_slice(const xstr_t *xs, xstr_t *slice, xstrsize_t start, xstrsize_t stop);

// -- Substrings and slices

// Get a substring (subxs) from a xstring (xs), starting from index
// position "s" until "e".
bool xstr_substr(const xstr_t *xs, xstr_t *subxs, xstrsize_t start, xstrsize_t end);
// Get the index position of the first occurrency inside "xs"
// of the string "s", starting from an index position "from".
int xstr_index(const xstr_t *xs, const char *s, xstrsize_t from);

// -- Relational functions

// Check if xstring is full (no more chars nor strings can be added).
bool xstr_isFull(const xstr_t *xs);
// Check if xstring data is equal to the string "s".
bool xstr_equalsTo(const xstr_t *xs, const char *s);
// Check if xstring has a prefix "prefix" inside itself.
bool xstr_hasPrefix(const xstr_t *xs, const char *prefix);
// Check if xstring has a suffix "suffix" inside itself.
bool xstr_hasSuffix(const xstr_t *xs, const char *suffix);

// -- Conversion functions

// Convert xstring ascii to integer.
int xstr_atoi(const xstr_t *xs);
// Convert xstring ascii to float.
float xstr_atof(const xstr_t *xs);
// Convert unsigned integer to xstring ascii.
void xstr_utoa(xstr_t *xs, uint32_t num, uint8_t base);
// Convert float to xstring ascii.
void xstr_ftoa(xstr_t *xs, float num, uint8_t dp);

#endif