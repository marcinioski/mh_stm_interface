/*
 * device_list.h
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin
 */

#ifndef MH_DEVICE_LIST_H_
#define MH_DEVICE_LIST_H_

#include "device.h"

#define ETHERNET_DEVICE {0}
#define USB_DEVICE {0}
#define I2C_DEVICE {0}
#define SPI_DEVICE {0}
#define GPIO_DEVICE {0}
#define UNKNOWN_DEVICE {0}

#include "mh/mh_config_system.h"

#include "mh/devices/ethernet/ethernet.h"

/*
 * TODO: list of device_fX files surrounded with #ifdef
 */

#ifdef MH_STM_COREF2
#endif

#ifdef MH_STM_COREF4
#endif

#ifdef MH_STM_COREF7
#endif

/* ****************************************************************************
 * @method: mh_device_startup_get_by_name
 * @brief:  method returns specific device from: mh_startup_device_list
 * @param:  name of device
 * @return: pmh_device_t on success, NULL on otherwise
 * ***************************************************************************/
pmh_device_t mh_device_startup_get_by_name(char* name);

/*****************************************************************************
* @brief: entry of devices list
* ***************************************************************************/
typedef struct mh_device_node
{
	mh_device_t device;
	struct mh_device_node* next;
};

#endif /* MH_DEVICES_DEVICE_LIST_H_ */
