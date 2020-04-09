/**
  ******************************************************************************
  * @file    utils.h 
  * @author  EonTeam
	* @version V1.0.0
  * @date    2020
  ******************************************************************************
*/

#include "utils.h"

// ===============================================================================
// Functions
// ===============================================================================

uint8_t bin2bcd(uint8_t val) {
  uint32_t bcdhigh = 0U;
  uint8_t Param = val;
  while (Param >= 10U) {
    bcdhigh++;
    Param -= 10U;
  }
  return ((uint8_t)(bcdhigh << 4U) | Param);
}

uint8_t bcd2bin(uint8_t val) {
  uint32_t tmp;
  tmp = (((uint32_t) val & 0xF0U) >> 4U) * 10U;
  return (uint8_t)(tmp + ((uint32_t) val & 0x0FU));
}