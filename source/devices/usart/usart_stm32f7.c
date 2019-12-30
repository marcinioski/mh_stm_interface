/*
 * usart_stm32f7.c
 *
 *  Created on: Dec 27, 2019
 *      Author: marcin
 */

#include "mh/devices/usart/usart.h"
#include "mh/error_handler/error_handler.h"
#include "stm32f7xx_hal.h"


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
 * @variable g_mh_usart_private
 * @brief global usart private data
 *****************************************************************************/
mh_usart_private_t g_mh_usart_private = {
	NULL

#if MH_ENABLE_USART1
	, &g_mh_uart1_handle
#endif
#if MH_ENABLE_USART2
	, &g_mh_uart2_handle
#endif
#if MH_ENABLE_USART3
	, &g_mh_uart3_handle
#endif
};

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

		if (HAL_UART_DeInit(handle) != HAL_OK)
		{
			Log_Stop_Error("USART3", 1);
		}
	}
#endif

	return result;
}
