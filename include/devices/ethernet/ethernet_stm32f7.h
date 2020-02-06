/*
 * ethernet_stm32f7.h
 *
 *  Created on: Nov 11, 2019
 *      Author: marcin
 */

#ifndef MH_ETHERNET_STM32F7_H_
#define MH_ETHERNET_STM32F7_H_

#include "mh/devices/device.h"
#include "mh/devices/device_list.h"
#include "mh/devices/device_state.h"
#include "mh/devices/ethernet/ethernet_private.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_eth.h"

#ifdef ETHERNET_DEVICE
#undef ETHERNET_DEVICE

/* ****************************************************************************
 * @method mh_f7_ethernet_init
 * @brief: method used for initializing ethernet device for stm32f7, in case of
 *         error it sets up last_error mh_device_t member to nonzero value
 * @param: arg pointer to mh_device_t
 * @return device state
 * ***************************************************************************/
enum MHDeviceState mh_f7_ethernet_init(void* arg);

/* ****************************************************************************
 * @method mh_f7_ethernet_start
 * @brief: method used for starting ethernet device for stm32f7, in case of
 *         error it sets up last_error mh_device_t member to nonzero value
 * @param: arg pointer to mh_device_t
 * @return device state
 * ***************************************************************************/
enum MHDeviceState mh_f7_ethernet_start(void* arg);

/* ****************************************************************************
 * @method mh_f7_ethernet_stop
 * @brief: method used for stopping ethernet device for stm32f7, in case of
 *         error it sets up last_error mh_device_t member to nonzero value
 * @param: arg pointer to mh_device_t
 * @return device state
 * ***************************************************************************/
enum MHDeviceState mh_f7_ethernet_stop(void* arg);



#define ETHERNET_DEVICE { \
	&mh_f7_ethernet_init, \
	&mh_f7_ethernet_start, \
	&mh_f7_ethernet_stop, \
	{ \
		NULL, \
		NULL, \
		NULL \
	}, \
	0, \
	NULL, \
	"ETHERNET", \
	eDSUnknown }
#endif

#endif /* MH_ETHERNET_STM32F7_H_ */
