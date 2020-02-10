/*
 * device_private.h
 *
 *  Created on: Feb 10, 2020
 *      Author: marcin
 */

#ifndef DEVICE_PRIVATE_H_
#define DEVICE_PRIVATE_H_

/**
 ******************************************************************************
 * @brief stores device node for device private data. Thanks that structure
 * 		  all devices can be stored in chain
 ******************************************************************************
 */
typedef struct device_private
{
	/**
	 * @brief stores specific device handle
	 */
	void* periph_specific;

	/**
	 * @brief id of device when there are more than one
	 */
	unsigned char id;
} mh_device_private_t, *pmh_device_private_t;

#endif /* DEVICE_PRIVATE_H_ */
