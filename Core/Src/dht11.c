/*
 * dht11.c
 *
 *  Created on: 24 апр. 2022 г.
 *      Author: HardCore
 */

#include "dht11.h"
#include "stm32f1xx_hal.h"

__STATIC_FORCEINLINE void Delay_MS(__IO uint32_t micros);

void DHT11_Get_Data(float* p_temperature, float* p_humidity)
{
  uint8_t buffer_data[5];

  // Set DHT11 pin on output mode.
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = DHT11_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);

  // Startup DHT11.
  HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
  HAL_Delay(18);
  HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);

  // Set DHT11 pin on input mode.
  GPIO_InitStruct.Pin = DHT11_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);

  // Check answer from DHT11.
  Delay_MS(39);
  if(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
  {
    return;
  }
  Delay_MS(80);
  if(!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
  {
    return;
  }
  Delay_MS(80);

  // Read bytes from DHT11. Disable interrupts.
  __disable_irq();
  for (uint8_t j = 4; j > 0; j--)
  {
    buffer_data[j] = 0;
    for(uint8_t i = 7; i > 0; i--)
    {
      while(!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));
      Delay_MS(30);
      if(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
        buffer_data[j] |= (1 << i);
      while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));
    }
  }
  __enable_irq();

  // Enable interrupts. Check checksum.
  if(buffer_data[0] == (buffer_data[1] + buffer_data[2] + buffer_data[3] + buffer_data[4]))
  {
    if(p_temperature != NULL)
    {
      *p_temperature = (float)((*(uint16_t*)(buffer_data + 1)) & 0x7FFF) / 10;
      if((*(uint16_t*)(buffer_data + 1)) & 0x8000)
      {
        *p_temperature *= -1;
      }
    }
    if(p_humidity != NULL)
    {
      *p_humidity = (float)(*(int16_t*)(buffer_data + 3)) / 10;
    }
  }
}

__STATIC_FORCEINLINE void Delay_MS(__IO uint32_t micros)
{
  micros *= (SystemCoreClock / 1000000) / 9;
  while (micros--);
}
