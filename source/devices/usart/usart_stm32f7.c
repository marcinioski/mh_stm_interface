/*
 * usart_stm32f7.c
 *
 *  Created on: Dec 27, 2019
 *      Author: marcin
 */

#include "mh/devices/usart/usart.h"
#include "mh/error_handler/error_handler.h"
#include "stm32f7xx_hal.h"

extern void user_usart_rx_cplt_callback(UART_HandleTypeDef*);

extern void user_usart_tx_cplt_callback(UART_HandleTypeDef*);

extern void user_usart_error_callback(UART_HandleTypeDef*);

/******************************************************************************
 * @variable g_mh_uart3_handle
 * @brief global uart handle
 *****************************************************************************/
UART_HandleTypeDef g_mh_uart3_handle;

#if MH_ENABLE_USART
/******************************************************************************
 * @variable g_mh_usart_handle
 * @brief global usart handle
 *****************************************************************************/
USART_HandleTypeDef g_mh_usart_handle;
#endif

/******************************************************************************
 * @method _mh_usart_write
 * @brief callback method used for writing data to usart device
 * @param uartHandle - pointer to uart handler to which data will be written
 * @param buffer - pointer to data buffer
 * @param buffer_size - amount of data to write
 * @return amount of send bytes
 *****************************************************************************/
uint16_t _mh_usart_write(void* uartHandle, uint8_t* buffer, uint16_t buffer_size)
{
	uint16_t result = 0x0;

#if MH_ENABLE_USART_IRQ
	if (HAL_UART_Transmit_IT
			((UART_HandleTypeDef*)uartHandle, buffer, buffer_size) == HAL_OK)
	{
		result = buffer_size;
	}
#else
	if (HAL_UART_Transmit
			((UART_HandleTypeDef*)uartHandle,
					buffer,
					buffer_size,
					MH_USART_TIMEOUT_TRANSMIT) == HAL_OK)
	{
		result = buffer_size;
	}
#endif

	return result;
}

/******************************************************************************
 * @method _mh_usart_read
 * @brief callback method used for reading data from usart device
 * @param uartHandle - pointer to uart handler from which data will be read
 * @param buffer - pointer to data buffer
 * @param buffer_size - maximum size of data to read
 * @return amount of read bytes
 *****************************************************************************/
uint16_t _mh_usart_read(void* uartHandle, uint8_t* buffer, uint16_t buffer_size)
{
	uint16_t result = 0x0;

#if MH_ENABLE_USART_IRQ
	if (HAL_UART_Receive_IT
			((UART_HandleTypeDef*)uartHandle, buffer, buffer_size) == HAL_OK)
	{
		result = buffer_size;
	}
#else
	if (HAL_UART_Receive
				((UART_HandleTypeDef*)uartHandle,
						buffer,
						buffer_size,
						MH_USART_TIMEOUT_RECEIVE) == HAL_OK)
		{
			result = buffer_size;
		}
#endif

	return result;
}

/******************************************************************************
 * @variable g_mh_usart_interface
 * @brief global usart interface structure
 *****************************************************************************/
mh_usart_interface_t g_mh_usart_interface = {
		&_mh_usart_write,
		&_mh_usart_read
};

/******************************************************************************
 * @variable g_mh_usart_private
 * @brief global usart private data
 *****************************************************************************/
mh_usart_private_t g_mh_usart_private = {
	&g_mh_usart_interface
#if MH_ENABLE_USART3
	, &g_mh_uart3_handle
#endif

#if MH_ENABLE_USART4
	, &g_mh_uart4_handle
#endif
};

#if MH_ENABLE_USART_IRQ
void UART_IRQHandler(UART_HandleTypeDef* handle)
{
	HAL_UART_IRQHandler(handle);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	user_usart_rx_cplt_callback(huart);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	user_usart_tx_cplt_callback(huart);
}

#endif

void HAL_UART_MspInit(UART_HandleTypeDef* handle)
{
	GPIO_InitTypeDef gpioInit;

	(void)gpioInit;

#if MH_ENABLE_USART3
	gpioInit.Mode = MH_USART_TX_GPIO_MODE_3;
	gpioInit.Alternate = MH_USART_TX_GPIO_AF_3;
	gpioInit.Pin = MH_USART_TX_GPIO_PIN3;
	gpioInit.Pull = MH_USART_TX_GPIO_PDPU_3;
	gpioInit.Speed = MH_USART_TX_GPIO_SPEED_3;

	HAL_GPIO_Init(MH_USART_TX_GPIO_PORT_3, &gpioInit);

	gpioInit.Mode = MH_USART_RX_GPIO_MODE_3;
	gpioInit.Alternate = MH_USART_RX_GPIO_AF_3;
	gpioInit.Pin = MH_USART_RX_GPIO_PIN3;
	gpioInit.Pull = MH_USART_RX_GPIO_PDPU_3;
	gpioInit.Speed = MH_USART_RX_GPIO_SPEED_3;

	HAL_GPIO_Init(MH_USART_RX_GPIO_PORT_3, &gpioInit);

#if MH_ENABLE_USART_IRQ
	HAL_NVIC_SetPriority(MH_USART_IRQ3, MH_USART_IRQ_PRIORITY3, MH_USART_IRQ_SUBPRIORITY3);
#endif

#endif
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* handle)
{
#if MH_ENABLE_USART3
	MH_USART_FORCE_RESET3;
	MH_USART_RELEASE_RESET3;

	HAL_GPIO_DeInit(MH_USART_TX_GPIO_PORT_3, MH_USART_TX_GPIO_PIN3);
	HAL_GPIO_DeInit(MH_USART_RX_GPIO_PORT_3, MH_USART_RX_GPIO_PIN3);

#if MH_ENABLE_USART_IRQ
#endif

#endif
}

enum MHDeviceState mh_f7_usart_init(void* arg)
{
	pmh_device_t device = (pmh_device_t)arg;
	device->private_data = (void*)&g_mh_usart_private;
	enum MHDeviceState result = eDSError;

#if MH_ENABLE_USART3
	{
		UART_HandleTypeDef* handle = g_mh_usart_private.usart3_handle;
		handle->Init.BaudRate = MH_USART_BAUD_RATE3;
		handle->Init.WordLength = MH_USART_WORD_LENGTH3;
		handle->Init.StopBits = MH_USART_STOP_BITS3;
		handle->Init.OverSampling = MH_USART_OVERSAMPLING3;
		handle->Init.HwFlowCtl = MH_USART_HWCTRL3;
		handle->Init.Mode = MH_USART_MODE3;
		handle->Init.Parity = MH_USART_PARITY3;

#if MH_ENABLE_USART_IRQ
#endif
		if (HAL_UART_Init(handle) != HAL_OK)
		{
			Log_Init_Error("USART3", 0);
		}
	}
#endif

	return result;
}

enum MHDeviceState mh_f7_usart_start(void* arg)
{
	pmh_device_t device = (pmh_device_t)arg;
	enum MHDeviceState result = eDSError;

	(void)device;

#if MH_ENABLE_USART3
	{
		MH_USART_PERIPH_RCC_ENABLE3;
		MH_USART_TX_GPIO_RCC_ENABLE3;
		MH_USART_RX_GPIO_RCC_ENABLE3;

#if MH_ENABLE_USART_IRQ
		HAL_NVIC_EnableIRQ(MH_USART_IRQ3);
#endif

	}
#endif

	return result;
}

enum MHDeviceState mh_f7_usart_stop(void* arg)
{
	pmh_device_t device = (pmh_device_t)arg;
	enum MHDeviceState result = eDSError;

	(void)device;

#if MH_ENABLE_USART3
	{
		UART_HandleTypeDef* handle = g_mh_usart_private.usart3_handle;
		MH_USART_PERIPH_RCC_DISABLE3;
		MH_USART_TX_GPIO_RCC_DISABLE3;
		MH_USART_RX_GPIO_RCC_DISABLE3;

#if MH_ENABLE_USART_IRQ
		HAL_NVIC_DisableIRQ(MH_USART_IRQ3);
#endif

		if (HAL_UART_DeInit(handle) != HAL_OK)
		{
			Log_Stop_Error("USART3", 1);
		}
	}
#endif

	return result;
}
