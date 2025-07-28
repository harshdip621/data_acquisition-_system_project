/*
 * uart.h
 *
 *  Created on: JULY 28, 2025
 *      Author: Harshdip Sonekar[89707]
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"

/*
USART2
PA2 -- TX
PA3 -- RX
*/

void UartInit(uint32_t baud);
void UartPutch(int ch);
int UartGetch(void);
void UartPuts(char *str);
void UartGets(char *str);

#endif /* UART_H_ */

