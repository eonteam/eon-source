#include "xstr.h"

// ==================================================================
// Functions
// ==================================================================

int xstr_atoi(const xstr_t *xs) {
  int res = 0;
  int8_t sign = 1, start = 0;
  if (xs->ptr[0] == '+' || xs->ptr[0] == '-') { start = 1; }
  if (xs->ptr[0] == '-') { sign = -1; }
  for (XSTR_ITERFROM(xs, i, start)) {
    if (!isCharNumber(xstr_charAt(xs, i))) {
      break;
    }
    res = res * 10 + xstr_charAt(xs, i) - '0';
  }
  return sign * res;
}

float xstr_atof(const xstr_t *xs) {
  float res = 0.0f;
  uint8_t dp = 0;
  int8_t sign = 1, start = 0;
  if (xs->ptr[0] == '+' || xs->ptr[0] == '-') { start = 1; }
  if (xs->ptr[0] == '-') { sign = -1; }
  for (XSTR_ITERFROM(xs, i, start)) {
    if (!isCharNumber(xstr_charAt(xs, i))) {
      start = i;
      break;
    }
    res = res * 10.0f + (xstr_charAt(xs, i) - '0');
  }
  if (xstr_charAt(xs, start) == '.') {
    for (XSTR_ITERFROM(xs, i, start + 1)) {
      if (!isCharNumber(xstr_charAt(xs, i))) {
        break;
      }
      res = res * 10.0f + (xstr_charAt(xs, i) - '0');
      dp++;
    }
    while (dp > 0) {
      res *= 0.1f;
      dp--;
    }
  }
  return (float) (sign * res);
}

void xstr_utoa(xstr_t *xs, uint32_t num, uint8_t base) {
  xstr_clear(xs);
  // processing individual digits
  do {
    uint8_t rem = num % base;
    xstr_push(xs, (rem > 9) ? (rem - 10) + 'a' : rem + '0');
    num = num / base;
  } while (num != 0);
  // reverse xstring
  xstr_reverse(xs);
}

// TODO more tests??
void xstr_ftoa(xstr_t *xs, float num, uint8_t dp) {
  if (dp > 5) { dp = 5; } // max dp is 5
  xstr_clear(xs);

  if (num < 0.00000f) {
    num = -num;
    xstr_push(xs, '-');
  }
  int ipart = (int) num;
  float fpart = num - (float) ipart;

  xstr_pushInt(xs, ipart, 10); // put the integer part
  if (dp > 0) {
    xstr_push(xs, '.');
    while (dp > 0) {
      fpart *= 10.0f;
      if ((int) fpart == 0) { xstr_push(xs, '0'); }
      dp--;
    }
    if ((int) fpart > 0) {
      xstr_pushInt(xs, (int) fpart, 10);
    }
  }
}