#include "xprint.h"

// ============================================================================
// Macros
// ============================================================================

#define VERB_FLOAT_2DP 'w'

// ============================================================================
// Public Printing functions
// ============================================================================

void xfprint(writeFn_t wr, const char *s) {
  for (uint8_t i = 0; s[i] != '\0'; i++) {
    wr(s[i]);
  }
}

void xfprintUint(writeFn_t wr, uint32_t num, uint8_t base) {
  char buf[12] = {0};
  int8_t last_pos = sizeof(buf) - 1;
  char *str = &buf[last_pos];
  // prepare buffer
  *str = '\0';
  last_pos--;
  // prevent crash if called with base == 1
  if (base < 2) base = 10;
  // processing individual digits
  do {
    if (last_pos < 0) {
      wr('o');
      wr('v');
      wr('r');
      return;
    }
    char c = num % base;
    num /= base;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
    last_pos--;
  } while (num);
  // print number
  for (uint8_t i = 0; str[i] != '\0'; i++) {
    wr(str[i]);
  }
}

void xfprintInt(writeFn_t wr, int64_t num, uint8_t base) {
  // handle negative numbers
  if (num < 0) {
    num = -num;
    wr('-');
  }
  xfprintUint(wr, num, base);
}

void xfprintf(writeFn_t wr, const char *format, ...) {
  va_list va;
  va_start(va, format);
  uint8_t end = (uint8_t) strlen(format);
  for (uint8_t i = 0; i < end;) {
    uint8_t lasti = i;
    while (i < end && format[i] != '%') {
      i++;
    }
    while (i > lasti) {
      wr(format[lasti++]);
    }
    if (i >= end) { break; } // done processing format string
    i++;                     // Process one verb
    char c = format[i];
    switch (c) {
      case '%':
        wr('%');
        i++;
        break;
      case 'c':
      case 't':
      case 'd':
      case 'u':
      case 'x':
      case 'o':
      case VERB_FLOAT_2DP:
      case 'b': {
        uint8_t base = 10;
        if (c == 'x') { base = 16; }
        if (c == 'b') { base = 2; }
        if (c == 'o') { base = 8; }
        int w = va_arg(va, int);
        if (c == 't' && w < base) { wr('0'); }
        // only int and float2dp have sign
        if ((c == 'd' || c == VERB_FLOAT_2DP) && w < 0) {
          w = -w;
          wr('-');
        }
        if (c == VERB_FLOAT_2DP) {
          int ipart = (int) w / 100;
          xfprintUint(wr, ipart, base);
          wr('.');
          ipart = w % 100;
          if (ipart < base) { wr('0'); }
          xfprintUint(wr, ipart, base);
        } else if (c == 'c') {
          wr((char) w);
        } else {
          xfprintUint(wr, w, base);
        }
        i++;
        break;
      }
      case 's': {
        const char *w = va_arg(va, char *);
        for (lasti = 0; w[lasti] != '\0'; lasti++) {
          wr(w[lasti]);
        }
        i++;
        break;
      }
    }
  }
  va_end(va);
}

// ============================================================================
// Public String format functions
// ============================================================================

void xsprintf(xstr_t *xs, const char *format, ...) {
  uint8_t end = (uint8_t) strlen(format);
  va_list va;
  va_start(va, format);
  for (uint8_t i = 0; i < end;) {
    uint8_t lasti = i;
    while (i < end && format[i] != '%') {
      i++;
    }
    while (i > lasti) {
      if (!xstr_push(xs, format[lasti++])) {
        break;
      }
    }
    if (i >= end) { break; } // done processing format string
    i++;                     // Process one verb
    char c = format[i];
    switch (c) {
      case '%':
        xstr_push(xs, '%');
        i++;
        break;
      case 'c':
      case 't':
      case 'd':
      case 'u':
      case 'x':
      case 'o':
      case VERB_FLOAT_2DP:
      case 'b': {
        uint8_t base = 10;
        if (c == 'x') { base = 16; }
        if (c == 'b') { base = 2; }
        if (c == 'o') { base = 8; }
        int w = va_arg(va, int);
        if (c == 't' && w < base) { xstr_push(xs, '0'); }
        // only int and float2dp have sign
        if ((c == 'd' || c == VERB_FLOAT_2DP) && w < 0) {
          w = -w;
          xstr_push(xs, '-');
        }
        if (c == VERB_FLOAT_2DP) {
          int ipart = (int) w / 100;
          xstr_pushUint(xs, ipart, base);
          xstr_push(xs, '.');
          ipart = w % 100;
          if (ipart < base) { xstr_push(xs, '0'); }
          xstr_pushUint(xs, ipart, base);
        } else if (c == 'c') {
          xstr_push(xs, (char) w);
        } else {
          xstr_pushUint(xs, w, base);
        }
        i++;
        break;
      }
#ifdef USE_FLOAT_XSPRINTF
      case 'f': {
        const float w = va_arg(va, double);
        xstr_pushFloat(xs, w, 2);
        i++;
        break;
      }
#endif
      case 's': {
        const char *w = va_arg(va, char *);
        for (lasti = 0; w[lasti] != '\0'; lasti++) {
          xstr_push(xs, w[lasti]);
        }
        i++;
        break;
      }
    }
  }
  va_end(va);
}