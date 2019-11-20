/*
 * device.c
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin
 */

#include "mh/mh_config_system.h"
#include "mh/devices/device.h"
#include "mh/devices/device_list.h"
#include "mh/error_handler/error_handler.h"
#include <stddef.h>
#include <string.h>

/* ****************************************************************************
 * @variable: mh_startup_device_list
 * @brief: list of devices which are used during startup
 * ***************************************************************************/
extern struct mh_device_node g_user_devices;

void mh_init_startup_devices(void)
{
	struct mh_device_node* node = &g_user_devices;

	while(node)
	{
		pmh_device_t dev = &node->device;
		MH_DEVICE_INIT(dev);
		if (dev->state != eDSInitialized)
		{
			Log_Init_Error(dev->name, dev->last_error);
		}

		node = node->next;
	}
}

void mh_start_startup_devices(void)
{
	struct mh_device_node* node = &g_user_devices;

	while(node)
	{
		pmh_device_t dev = &node->device;
		MH_DEVICE_START(dev);
		if (dev->state != eDSStarted)
		{
			Log_Startup_Error(dev->name, dev->last_error);
		}

		node = node->next;
	}
}

void mh_stop_startup_devices(void)
{
	struct mh_device_node* node = &g_user_devices;

	while(node)
	{
		pmh_device_t dev = &node->device;
		MH_DEVICE_STOP(dev);
		if (dev->state != eDSStopped)
		{
			Log_Stop_Error(dev->name, dev->last_error);
		}

		node = node->next;
	}
}

pmh_device_t mh_device_startup_get_by_name(char* name)
{
	pmh_device_t result = NULL;

	return result;
}
