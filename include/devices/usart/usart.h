/*
 * usart.h
 *
 *  Created on: Dec 26, 2019
 *  	Author: ,arcom
 */

#ifndef MH_USART_H_
#define MH_USART_H_

#include "mh/mh_config_system.h"

#ifdef MH_STM_COREF4
#include "usart_stm32f4.h"
#endif

#ifdef MH_STM_COREF7
#include "usart_stm32f7.h"
#endif

#include "usart_conf.h"

#endif /* MH_USART_H_ */
