/*
 * systime.h
 *
 *  Created on: 25 апр. 2022 г.
 *      Author: HardCore
 */

#ifndef INC_SYSTIME_H_
#define INC_SYSTIME_H_

#include <stdint.h>
#include <stdbool.h>

uint32_t Sys_Time_Get_Time(void);
bool Sys_Time_Its_Time(uint32_t start_time, uint32_t delay);

#endif /* INC_SYSTIME_H_ */
