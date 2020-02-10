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
	void* private;
#if MH_ENABLE_USART1
	mh_device_node_t usart1;
#endif

#if MH_ENABLE_USART2
	mh_device_node_t usart2;
#endif

#if MH_ENABLE_USART3
	mh_device_private_t usart3;
#endif

} mh_usart_private_t, *pmh_usart_private_t;

#endif /* MH_USART_PRIVATE_H_ */
