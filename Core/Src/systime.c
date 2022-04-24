/*
 * systime.c
 *
 *  Created on: 25 апр. 2022 г.
 *      Author: HardCore
 */
#include "systime.h"
#include "stm32f1xx_hal.h"

uint32_t Sys_Time_Get_Time(void)
{
  return HAL_GetTick();
}

bool Sys_Time_Its_Time(uint32_t start_time, uint32_t delay)
{
  uint32_t current_time = Sys_Time_Get_Time();
  uint32_t delta = (current_time < start_time) ? ((UINT32_MAX - start_time) + current_time) : (current_time - start_time);
  return (delta >= delay);
}
