/*
 * usart_private.h
 *
 *  Created on: Dec 26, 2019
 *      Author: marcin
 */

#ifndef MH_USART_PRIVATE_H_
#define MH_USART_PRIVATE_H_

#include "usart_conf.h"

typedef struct
{
	void* private_data;

#if MH_ENABLE_USART1
	void* usart1_handle;
#endif

#if MH_ENABLE_USART2
	void* usart2_handle;
#endif

#if MH_ENABLE_USART3
	void* usart3_handle;
#endif
} mh_usart_private_t, *pmh_usart_private_t;

#endif /* MH_USART_PRIVATE_H_ */
