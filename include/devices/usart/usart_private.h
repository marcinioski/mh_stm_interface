/*
 * usart_private.h
 *
 *  Created on: Dec 26, 2019
 *      Author: marcin
 */

#ifndef MH_USART_PRIVATE_H_
#define MH_USART_PRIVATE_H_

#include "usart_conf.h"

/******************************************************************************
 * @type mh_usart_write_clb_t
 * @brief callback interface used for writing to usart device. In irq mode it
 *        returns immediately and will not block system.
 * @param uartHandle - pointer to uart handle to which will be data written
 * @param buffer - pointer to data to write
 * @param buffer_size - stores amount of data to write
 * @return amount of send bytes
 *****************************************************************************/
typedef uint16_t (*mh_usart_write_clb_t)(void* uartHandle,
										 uint8_t* buffer,
										 uint16_t buffer_size);

/******************************************************************************
 * @type mh_usart_read_clb_t
 * @brief callback interface used for reading from usart device. In irq mode it
 *        returns immediately and will not block system.
 * @param uartHandle - pointer to uart handle from which data will be read
 * @param buffer - pointer to store read data
 * @param buffer_size - size of buffer
 * @return amount of read bytes
 *****************************************************************************/
typedef uint16_t (*mh_usart_read_clb_t)(void* uartHandle,
										uint8_t* buffer,
										uint16_t buffer_size);

/******************************************************************************
 * @type mh_usart_interface_t
 * @brief stores pointer to usart callbacks which can be used later in system
 *****************************************************************************/
typedef struct
{
	mh_usart_write_clb_t write;
	mh_usart_read_clb_t read;
}mh_usart_interface_t, *pmh_usart_interface_t;


typedef struct
{
	pmh_usart_interface_t private_data;

#if MH_ENABLE_USART1
	void* usart1_handle;
#endif

#if MH_ENABLE_USART2
	void* usart2_handle;
#endif

#if MH_ENABLE_USART3
	void* usart3_handle;
#endif
} mh_usart_private_t, *pmh_usart_private_t;

#endif /* MH_USART_PRIVATE_H_ */
