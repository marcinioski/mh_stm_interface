/*
 * user_devices.c
 *
 *  Created on: Nov 20, 2019
 *      Author: marcin
 */

#include "mh/devices/device_list.h"
#include <stddef.h>

struct mh_device_node usart = {USART_DEVICE, NULL};
struct mh_device_node ethernet = {ETHERNET_DEVICE, &usart};
struct mh_device_node g_user_devices = {UNKNOWN_DEVICE, &ethernet};
