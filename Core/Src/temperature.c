/*
 * temperature.c
 *
 *  Created on: 24 апр. 2022 г.
 *      Author: HardCore
 */
#include "temperature.h"
#include "dht11.h"
#include <string.h>

static float temperature_buffer[TEMPERATURE_BUFFER_SIZE];  // Collection of 100 records temperature.
static unsigned temperature_buffer_size = 0;  // Current size of collection.

float Get_Current_Temperature(void)
{
  return temperature_buffer[temperature_buffer_size];
}

void Measure_Temperature(void)
{
  if(temperature_buffer_size < TEMPERATURE_BUFFER_SIZE)
  {
    DHT11_Get_Data((temperature_buffer + temperature_buffer_size), NULL);
    temperature_buffer_size++;
  }
  else
  {
    memcpy(temperature_buffer, (temperature_buffer + 1), ((TEMPERATURE_BUFFER_SIZE - 1) * sizeof(float)));
    DHT11_Get_Data((temperature_buffer + TEMPERATURE_BUFFER_SIZE - 1), NULL);
  }
}

void Get_Max_Middle_Min_Temperature(float* p_max_temperature, float* p_middle_temperature, float* p_min_temperature)
{
  float max_temperature = temperature_buffer[0];
  float min_temperature = temperature_buffer[0];
  float middle_temperature_buffer = temperature_buffer[0];
  for (unsigned i = 1; i < TEMPERATURE_BUFFER_SIZE; i++)
  {
    if(max_temperature > temperature_buffer[i])
    {
      max_temperature = temperature_buffer[i];
    }
    if(min_temperature < temperature_buffer[i])
    {
      min_temperature = temperature_buffer[i];
    }
    middle_temperature_buffer += temperature_buffer[i];
  }
  *p_max_temperature = max_temperature;
  *p_middle_temperature = (middle_temperature_buffer / TEMPERATURE_BUFFER_SIZE);
  *p_min_temperature = min_temperature;
}
