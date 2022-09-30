#ifndef __XTIME_H_
#define __XTIME_H_

#include <stdint.h>

// ===============================================================================
// Macros
// ===============================================================================

#define MIN_TO_SEC(__x__) ((__x__) *60)
#define HOUR_TO_SEC(__x__) ((__x__) *60 * 60)

// ===============================================================================
// Types
// ===============================================================================

typedef struct {
  uint8_t weekday;
  uint8_t day;
  uint8_t month;
  uint8_t year;
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} xtime_t;

// ===============================================================================
// Functions
// ===============================================================================

// Get xtime object from unix time seconds
void xtime_fromUnix(xtime_t *xt, uint32_t u);
// Get the unix time seconds from a xtime object
uint32_t xtime_toUnix(const xtime_t *xt);

#endif