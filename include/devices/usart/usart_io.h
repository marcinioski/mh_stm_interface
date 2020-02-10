/*
 * usart_io.h
 *
 *  Created on: Feb 10, 2020
 *      Author: marcin
 */

#ifndef USART_USART_IO_H_
#define USART_USART_IO_H_

#include "usart_private.h"
#include "mh/devices/device.h"

#define MH_USART_WRITE(X, ID, BUFFER, BUFFER_LEN, LEN) do {\
	pmh_usart_private_t priv = ((pmh_device_t)X)->private_data; \
	void* handler = priv->ID.periph_specific; \
	MH_DEVICE_IO_WRITE(X, handler, BUFFER, BUFFER_LEN, LEN); \
} while(0)

#define MH_USART_READ(X, ID, BUFFER, BUFFER_LEN, LEN) do{\
	pmh_usart_private_t priv = ((pmh_device_t)X)->private_data; \
	void* handler = priv->ID.periph_specific; \
	MH_DEVICE_IO_READ(X, handler, BUFFER, BUFFER_LEN, LEN); \
} while(0)

#ifdef MH_ENABLE_USART3
#define MH_USART3_WRITE(X, BUFFER, BUFFER_LEN, LEN) MH_USART_WRITE(X, usart3, BUFFER, BUFFER_LEN, LEN)
#define MH_USART3_READ(X, BUFFER, BUFFER_LEN, LEN) MH_USART_READ(X, usart3, BUFFER, BUFFER_LEN, LEN)
#endif

#endif /* USART_USART_IO_H_ */
