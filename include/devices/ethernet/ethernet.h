/*
 * ethernet.h
 *
 *  Created on: Nov 11, 2019
 *      Author: marcin
 */

#ifndef MH_ETHERNET_H_
#define MH_ETHERNET_H_

#include "mh/mh_config_system.h"
#include "ethernet_conf.h"

#ifdef MH_STM_COREF4
#include "ethernet_stm32f4.h"
#endif

#ifdef MH_STM_COREF7
#include "ethernet_stm32f7.h"
#endif

#endif /* MH_ETHERNET_H_ */
