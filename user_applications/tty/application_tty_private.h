/*
 * application_tty_private.h
 *
 *  Created on: Jan 20, 2020
 *      Author: marcin
 */

#ifndef APPLICATION_TTY_PRIVATE_H_
#define APPLICATION_TTY_PRIVATE_H_

#include "mh/devices/device.h"

/**
 ******************************************************************************
 * @brief stores private data for tty device, like pointer to device
 ******************************************************************************
 */
typedef struct
{
	pmh_device_t tty_device;
} tty_private_t, *ptty_private_t;

#endif /* APPLICATION_TTY_PRIVATE_H_ */
