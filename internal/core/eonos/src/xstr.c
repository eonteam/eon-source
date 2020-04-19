#include "xstr.h"

// ==================================================================
// General purpose function
// ==================================================================

char xstr_pop(xstr_t *xs) {
  if (xs->len == 0) return 0;
  char r = xs->ptr[xs->len - 1];
  xs->ptr[xs->len - 1] = 0;
  xs->len--;
  return r;
}

void xstr_reverse(xstr_t *xs) {
  if (xs->len == 0) return;
  xstrsize_t i = 0, j = xs->len - 1;
  while (i < j) {
    swap(&xs->ptr[i++], &xs->ptr[j--]);
  }
}

void xstr_clear(xstr_t *xs) {
  xs->len = 0;
  memset(xs->ptr, 0, xs->cap);
}

// ==================================================================
// Push functions
// ==================================================================

bool xstr_push(xstr_t *xs, char c) {
  if (xs->len >= xs->cap) { return false; }
  xs->ptr[xs->len] = c;
  xs->len++;
  return true;
}

bool xstr_pushString(xstr_t *xs, const char *s) {
  xstrsize_t len = strlen(s);
  for (xstrsize_t i = 0; i < len; i++) {
    if (!xstr_push(xs, s[i])) {
      return false;
    }
  }
  return true;
}

bool xstr_pushStringN(xstr_t *xs, const char *s, xstrsize_t maxbytes) {
  xstrsize_t len = strlen(s);
  if (len > maxbytes) { len = maxbytes; }
  for (xstrsize_t i = 0; i < len; i++) {
    if (!xstr_push(xs, s[i])) {
      return false;
    }
  }
  return true;
}

bool xstr_pushX(xstr_t *xs, const xstr_t *other) {
  for (XSTR_ITER(other, i)) {
    if (!xstr_push(xs, other->ptr[i])) {
      return false;
    }
  }
  return true;
}

bool xstr_pushUint(xstr_t *xs, uint32_t num, uint8_t base) {
  xstr_t tmp;
  xstr_slice(xs, &tmp, xs->len, xs->cap);
  xstr_utoa(&tmp, num, base);
  return xstr_pushX(xs, &tmp);
}

bool xstr_pushInt(xstr_t *xs, int64_t num, uint8_t base) {
  xstr_t tmp;
  if (num < 0) {
    num = -num;
    xstr_push(xs, '-');
  }
  xstr_slice(xs, &tmp, xs->len, xs->cap);
  xstr_utoa(&tmp, num, base);
  return xstr_pushX(xs, &tmp);
}

bool xstr_pushFloat(xstr_t *xs, float num, uint8_t dp) {
  xstr_t tmp;
  xstr_slice(xs, &tmp, xs->len, xs->cap);
  xstr_ftoa(&tmp, num, dp);
  return xstr_pushX(xs, &tmp);
}

// ==================================================================
// Substrings
// ==================================================================
bool xstr_substr(const xstr_t *xs, xstr_t *subxs, xstrsize_t start, xstrsize_t end) {
  if (start >= end) { return false; }  // `start` must not be greater or equal to `end`
  if (end > xs->len) { return false; } // `end` must not be greater than `xs->len`
  xstr_clear(subxs);
  for (xstrsize_t i = start; i < end; i++) {
    if (!xstr_push(subxs, xs->ptr[i])) {
      return false;
    }
  }
  return true;
}

int xstr_index(const xstr_t *xs, const char *s, xstrsize_t from) {
  if (from >= xs->len) { return -1; }
  char *p = strstr(xs->ptr + from, s);
  if (p == 0) { return -1; }
  return (p - xs->ptr);
}

bool xstr_slice(const xstr_t *xs, xstr_t *slice, xstrsize_t start, xstrsize_t stop) {
  if (start >= stop) { return false; }  // `start` can't be greater or equal to `stop`
  if (stop > xs->cap) { return false; } // `stop` can't be greater than `xs->cap`
  slice->ptr = xs->ptr + start;
  slice->len = stop - start;
  slice->cap = xs->cap - start;
  return true;
}

// ==================================================================
// Relational functions
// ==================================================================

bool xstr_isFull(const xstr_t *xs) {
  return xs->len >= xs->cap;
}

bool xstr_equalsTo(const xstr_t *xs, const char *s) {
  xstrsize_t len = strlen(s);
  if (len != xs->len) { return false; }
  for (xstrsize_t i = 0; i < len; i++) {
    if (xs->ptr[i] != s[i]) { return false; }
  }
  return true;
}

bool xstr_hasPrefix(const xstr_t *xs, const char *prefix) {
  xstrsize_t len = strlen(prefix);
  if (xs->len < len) { return false; }
  for (xstrsize_t i = 0; i < len; i++) {
    if (xs->ptr[i] != prefix[i]) { return false; }
  }
  return true;
}

bool xstr_hasSuffix(const xstr_t *xs, const char *suffix) {
  xstrsize_t len = strlen(suffix);
  if (xs->len < len) { return false; }
  for (xstrsize_t i = (xs->len - len); i < xs->len; i++) {
    if (xs->ptr[i] != suffix[i - xs->len + len]) { return false; }
  }
  return true;
}