/*
 * temperature.h
 *
 *  Created on: 24 апр. 2022 г.
 *      Author: HardCore
 */

#ifndef INC_TEMPERATURE_H_
#define INC_TEMPERATURE_H_

#define TEMPERATURE_BUFFER_SIZE 100

float Get_Current_Temperature(void);
void Measure_Temperature(void);
void Get_Max_Middle_Min_Temperature(float* p_max_temperature, float* p_middle_temperature, float* p_min_temperature);

#endif /* INC_TEMPERATURE_H_ */
