/*
 * usart_weaks.c
 *
 *  Created on: Dec 27, 2019
 *      Author: marcin
 */


#include "mh/devices/usart/usart.h"

__attribute__((weak)) void user_usart_tx_cplt_callback(UART_HandleTypeDef* uartHandle)
{
	(void)uartHandle;
};

__attribute__((weak)) void user_usart_rx_cplt_callback(UART_HandleTypeDef* uartHandle)
{
	(void)uartHandle;
};

__attribute__((weak)) void user_usart_error_callback(UART_HandleTypeDef* uartHandle)
{
	(void)uartHandle;
};
