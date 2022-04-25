/*
 * temperature.c
 *
 *  Created on: 24 апр. 2022 г.
 *      Author: HardCore
 */
#include "temperature.h"
#include "dht11.h"
#include <stddef.h>

static float temperature_buffer[TEMPERATURE_BUFFER_SIZE];  // Collection of 100 records temperature.
static unsigned temperature_buffer_current_index = 0;  // Current index of collection.

float Get_Current_Temperature(void)
{
  return temperature_buffer[temperature_buffer_current_index];
}

void Measure_Temperature(void)
{
  temperature_buffer_current_index = (temperature_buffer_current_index < TEMPERATURE_BUFFER_SIZE) ? temperature_buffer_current_index + 1 : 0;
  DHT11_Get_Data((temperature_buffer + temperature_buffer_current_index), NULL);
}

void Get_Max_Middle_Min_Temperature(float* p_max_temperature, float* p_middle_temperature, float* p_min_temperature)
{
  *p_max_temperature = temperature_buffer[0];
  *p_middle_temperature = temperature_buffer[0];
  *p_min_temperature = temperature_buffer[0];
  for (unsigned i = 1; i < TEMPERATURE_BUFFER_SIZE; i++)
  {
    if(*p_max_temperature > temperature_buffer[i])
    {
      *p_max_temperature = temperature_buffer[i];
    }
    if(*p_min_temperature < temperature_buffer[i])
    {
      *p_min_temperature = temperature_buffer[i];
    }
    *p_middle_temperature += temperature_buffer[i];
  }
  *p_middle_temperature /= TEMPERATURE_BUFFER_SIZE;
}
