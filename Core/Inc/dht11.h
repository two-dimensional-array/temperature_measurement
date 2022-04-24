/*
 * dht11.h
 *
 *  Created on: 24 апр. 2022 г.
 *      Author: HardCore
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#define DHT11_PORT GPIOA
#define DHT11_PIN  GPIO_PIN_8

void DHT11_Get_Data(float* temperature, float* humidity);

#endif /* INC_DHT11_H_ */
