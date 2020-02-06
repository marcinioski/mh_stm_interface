/*
 * usart_stm32f7.h
 *
 *  Created on: Dec 26, 2019
 *      Author: marcin
 */

#ifndef MH_USART_STM32F7_H_
#define MH_USART_STM32F7_H_

#include "mh/devices/device.h"
#include "mh/devices/device_list.h"
#include "mh/devices/device_state.h"
#include "mh/devices/usart/usart_private.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_uart.h"
#include "stm32f7xx_hal_usart.h"

#ifdef USART_DEVICE
#undef USART_DEVICE
/******************************************************************************
 * @method mh_f7_usart_init
 * @brief method used for initializing usart device for stm32f7, in case of
 *        error it sets up last_error mh_device_t member to nonzero value
 * @param arg pointer to mh_device_t
 * @return device state
 *****************************************************************************/
enum MHDeviceState mh_f7_usart_init(void* arg);
/* ****************************************************************************
 * @method mh_f7_usart_start
 * @brief: method used for starting usart device for stm32f7, in case of
 *         error it sets up last_error mh_device_t member to nonzero value
 * @param: arg pointer to mh_device_t
 * @return device state
 * ***************************************************************************/
enum MHDeviceState mh_f7_usart_start(void* arg);

/* ****************************************************************************
 * @method mh_f7_usart_stop
 * @brief: method used for stopping usart device for stm32f7, in case of
 *         error it sets up last_error mh_device_t member to nonzero value
 * @param: arg pointer to mh_device_t
 * @return device state
 * ***************************************************************************/
enum MHDeviceState mh_f7_usart_stop(void* arg);

/**
 ******************************************************************************
 * @method mh_f7_usart_write
 * @brief method is used to writing data to usart device
 * @param buffer - pointer to data
 * @param buffer_len - length of data to write
 * @param len - len of write data
 * @return device state
 ******************************************************************************
 */
enum MHDeviceState mh_f7_usart_write(const char* buffer, const size_t buffer_len, size_t* len);

/**
 ******************************************************************************
 * @method mh_f7_usart_read
 * @brief method is used to reading data from usart device
 * @param buffer - pointer to data
 * @param buffer_len - length of buffer
 * @param len - len of read data
 * @return device state
 ******************************************************************************
 */
enum MHDeviceState mh_f7_usart_read(char* buffer, const size_t buffer_len, size_t* len);

/**
 ******************************************************************************
 * @method mh_f7_usart_signal
 * @brief method is used to send signals to usart device
 * @param signal - signal id
 * @return device state
 ******************************************************************************
 */
enum MHDeviceState mh_f7_usart_signal(unsigned int signal);

#define USART_DEVICE { \
	&mh_f7_usart_init, \
	&mh_f7_usart_start, \
	&mh_f7_usart_stop, \
	{ \
		&mh_f7_usart_read, \
		&mh_f7_usart_write, \
		&mh_f7_usart_signal \
	}, \
	0, \
	NULL, \
	"USART", \
	eDSUnknown }
#endif

#ifdef UART_DEVICE
#undef UART_DEVICE
#endif

#endif /* MH_USART_STM32F7_H_ */
