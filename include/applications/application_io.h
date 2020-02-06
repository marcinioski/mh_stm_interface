/*
 * application_io.h
 *
 *  Created on: Feb 3, 2020
 *      Author: marcin
 */

#ifndef APPLICATION_IO_H_
#define APPLICATION_IO_H_

#include <sys/types.h>

/**
 ******************************************************************************
 * @type mh_application_io_read_clb_t
 * @brief callback responsible for reading from application
 * @param buffer - pointer to data buffer
 * @param len - length of buffer
 * @return length of read data
 ******************************************************************************
 */
typedef size_t (*mh_application_read_clb_t)(char* buffer, size_t len);

/**
 ******************************************************************************
 * @type mh_application_io_write_clb_t
 * @brief callback responsible for writing to application
 * @param buffer - pointer to data buffer
 * @param len - length of buffer
 * @return length of write data
 ******************************************************************************
 */
typedef size_t (*mh_application_write_clb_t)(char* buffer, size_t len);

/**
 ******************************************************************************
 * @type mh_application_io_signal_clb_t
 * @brief callback responsible for signaling events to application
 * @param signal - signal id
 * @return None
 ******************************************************************************
 */
typedef void (*mh_application_signal_clb_t)(unsigned int signal);


/**
 ******************************************************************************
 * @type mh_application_io_t
 * @brief definition of IO methods used to communicate with application
 ******************************************************************************
 */
typedef struct
{
	mh_application_read_clb_t read;
	mh_application_write_clb_t write;
	mh_application_signal_clb_t signal;
} mh_application_io_t, *pmh_application_io_t;

#endif /* APPLICATION_IO_H_ */
