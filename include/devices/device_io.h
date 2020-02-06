/*
 * device_io.h
 *
 *  Created on: Feb 3, 2020
 *      Author: marcin
 */

#ifndef DEVICE_IO_H_
#define DEVICE_IO_H_

#include <sys/types.h>
#include "mh/devices/device_state.h"

/**
 ******************************************************************************
 * @type mh_device_io_read_clb_t
 * @brief callback responsible for reading from device
 * @param buffer - pointer to data buffer
 * @param buffer_len - length of buffer
 * @param len - length of read data
 * @return device state
 ******************************************************************************
 */
typedef enum MHDeviceState (*mh_device_read_clb_t)(char* buffer, const size_t buffer_len, size_t* len);

/**
 ******************************************************************************
 * @type mh_device_io_write_clb_t
 * @brief callback responsible for writing to device
 * @param buffer - pointer to data buffer
 * @param buffer_len - length of buffer
 * @param len - length of read data
 * @return device state
 ******************************************************************************
 */
typedef enum MHDeviceState (*mh_device_write_clb_t)(const char* buffer, const size_t buffer_len, size_t* len);

/**
 ******************************************************************************
 * @type mh_device_io_signal_clb_t
 * @brief callback responsible for signaling events to device
 * @param signal - signal id
 * @return device state
 ******************************************************************************
 */
typedef enum MHDeviceState (*mh_device_signal_clb_t)(unsigned int signal);


/**
 ******************************************************************************
 * @type mh_device_io_t
 * @brief definition of IO methods used to communicate with device
 ******************************************************************************
 */
typedef struct
{
	mh_device_read_clb_t read;
	mh_device_write_clb_t write;
	mh_device_signal_clb_t signal;
} mh_device_io_t, *pmh_device_io_t;

#endif /* DEVICE_IO_H_ */
