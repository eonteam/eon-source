#include "xtime.h"

// ===============================================================================
// Contants
// ===============================================================================

static const uint8_t DaysInMonths[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, /* Not leap year */
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}  /* Leap year */
};

// ===============================================================================
// Macros
// ===============================================================================

#define LEAP_YEAR(year) ((((year) % 4 == 0) && ((year) % 100 != 0)) || ((year) % 400 == 0))
#define DAYS_IN_YEAR(x) LEAP_YEAR(x) ? 366 : 365
#define OFFSET_YEAR 1970 // Start Year for Unix
#define SECONDS_PER_DAY 86400
#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_MINUTE 60

// ===============================================================================
// Functions
// ===============================================================================

// Get xtime object from unix time seconds
//
void xtime_fromUnix(xtime_t *xt, uint32_t u) {
  // Get seconds from unix
  xt->seconds = u % 60;
  // Go to minutes
  u /= 60;
  // Get minutes
  xt->minutes = u % 60;
  // Go to hours
  u /= 60;
  // Get hours
  xt->hours = u % 24;
  // Go to days
  u /= 24;
  // Get week day (Monday is day one)
  xt->weekday = (u + 3) % 7 + 1;

  // Get year
  uint16_t year = 1970;
  while (1) {
    if (LEAP_YEAR(year)) {
      if (u >= 366) {
        u -= 366;
      } else {
        break;
      }
    } else if (u >= 365) {
      u -= 365;
    } else {
      break;
    }
    year++;
  }
  // Get year in xx format
  xt->year = (uint8_t) (year - 2000);

  // Get month
  for (xt->month = 0; xt->month < 12; xt->month++) {
    if (LEAP_YEAR(year)) {
      if (u >= (uint32_t) DaysInMonths[1][xt->month]) {
        u -= DaysInMonths[1][xt->month];
      } else {
        break;
      }
    } else if (u >= (uint32_t) DaysInMonths[0][xt->month]) {
      u -= DaysInMonths[0][xt->month];
    } else {
      break;
    }
  }
  // Get month (Month starts with 1)
  xt->month++;
  // Get date (Day starts with 1)
  xt->day = u + 1;
}

// Get the unix time seconds from a xtime object
//
uint32_t xtime_toUnix(const xtime_t *xt) {
  uint32_t unix_seconds = 0;
  uint16_t t_year = (uint16_t) (xt->year + 2000);

  if (t_year < OFFSET_YEAR) { return 0; }

  // Days from 1970 until the specified year
  for (uint16_t i = OFFSET_YEAR; i < t_year; i++) {
    unix_seconds += DAYS_IN_YEAR(i);
  }

  // Days that has been passed from the specified year, according to the input month
  for (uint8_t i = 1; i < xt->month; i++) {
    unix_seconds += DaysInMonths[LEAP_YEAR(t_year)][i - 1];
  }

  // Day starts with 1
  unix_seconds += xt->day - 1;
  unix_seconds = unix_seconds * SECONDS_PER_DAY;
  unix_seconds += xt->hours * SECONDS_PER_HOUR;
  unix_seconds += xt->minutes * SECONDS_PER_MINUTE;
  unix_seconds += xt->seconds;

  return (uint32_t) unix_seconds;
}