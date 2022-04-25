# Temperature Measurement
Firmware for stm32f103c8t6, which is do following tasks:
---
-	Collect temperature measurements with 1 min interval and keep up to 100 records in the RAM.
-	When temperature value is below 10°C, change measurement interval to 20 seconds and return it to 1 min back when temperature is above 15°C.
-	Using collected measurements - save minimum, maximum and average values to the persistence storage (Internal Flash) each 30 min.
-	Print current temperature via UART output.
---
## Hardware
- Microcontroller - stm32f103c8t6
- Temperature sensor - DHT11 
---
## About Project
This project is created in STM32CubeIDE. <br/>
Library for temperature sensor DHT11 is contained in [dht11.h][dht11.h] and [dht11.c][dht11.c] files. <br/>
Library for temperature measurements is contained in [temperature.h][temperature.h] and [temperature.c][temperature.c] files. <br/>
Example of printed message via uart output.
```
Current temperature: 22.1\r\n
```
---

[dht11.h]: [https://github.com/two-dimensional-array/temperature_measurement/blob/master/Core/Inc/dht11.h]
[dht11.c]: [https://github.com/two-dimensional-array/temperature_measurement/blob/master/Core/Inc/dht11.c]
[temperature.h]: [https://github.com/two-dimensional-array/temperature_measurement/blob/master/Core/Inc/temperature.h]
[temperature.c]: [https://github.com/two-dimensional-array/temperature_measurement/blob/master/Core/Inc/temperature.c]
