/*
 * uart.h
 *
 *  Created on: 2019. 11. 18.
 *      Author: kazam
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void GPIO_Init();
void UART_Init(uint32_t BaudRate);

uint8_t ReadByte();
void WriteByte(uint8_t buf);

#endif /* UART_H_ */
