/*
 * usart_conf.h
 *
 *  Created on: Dec 26, 2019
 *      Author: marcin
 */

#ifndef MH_USART_CONF_H_
#define MH_USART_CONF_H_

#include "mh/mh_config_system.h"
#include "usart.h"

#define MH_USART_1_VAR(X) X##1
#define MH_USART_2_VAR(X) X##2
#define MH_USART_3_VAR(X) X##3

/******************************************************************************
 * @param MH_USART_PERIPH_X
 * @brief variable specify which usart will be used
 *****************************************************************************/
#define MH_USART_PERIPH3 USART3

/******************************************************************************
 * @param MH_USART_PERIPH_RCC_ENABLEX
 * @brief variable runs specified usart clock
 *****************************************************************************/
#define MH_USART_PERIPH_RCC_ENABLE3 __HAL_RCC_USART3_CLK_ENABLE()
#define MH_USART_PERIPH_RCC_ENABLE4 __HAL_RCC_UART4_CLK_ENABLE()

/******************************************************************************
 * @param MH_USART_PERIPH_RCC_DISABLEX
 * @brief variable stops specified usart clock
 *****************************************************************************/
#define MH_USART_PERIPH_RCC_DISABLE3 __HAL_RCC_USART3_CLK_DISABLE()
#define MH_USART_PERIPH_RCC_DISABLE4 __HAL_RCC_UART4_CLK_DISABLE()

/******************************************************************************
 * @param MH_USART_TX_GPIO_RCC_ENABLEX
 * @brief variable runs specified usart tx gpio clock
 *****************************************************************************/
#define MH_USART_TX_GPIO_RCC_ENABLE3 __HAL_RCC_GPIOD_CLK_ENABLE()
#define MH_USART_TX_GPIO_RCC_ENABLE4 __HAL_RCC_GPIOD_CLK_ENABLE()

/******************************************************************************
 * @param MH_USART_RX_GPIO_RCC_ENABLEX
 * @brief variable runs specified usart rx gpio clock
 *****************************************************************************/
#define MH_USART_RX_GPIO_RCC_ENABLE3 __HAL_RCC_GPIOD_CLK_ENABLE()
#define MH_USART_RX_GPIO_RCC_ENABLE4 __HAL_RCC_GPIOD_CLK_ENABLE()

/******************************************************************************
 * @param MH_USART_FORCE_RESET_X
 * @brief variable specify usart reset mechanism
 *****************************************************************************/
#define MH_USART_FORCE_RESET3 __HAL_RCC_USART3_FORCE_RESET()

/******************************************************************************
 * @param MH_USART_RELEASE_RESET_X
 * @brief variable release reset from usart device
 *****************************************************************************/
#define MH_USART_RELEASE_RESET3 __HAL_RCC_USART3_RELEASE_RESET()

/******************************************************************************
 * @param MH_USART_TIMEOUT_TRANSMIT
 * @brief variable specify timeout for transmitting data
 *****************************************************************************/
#define MH_USART_TIMEOUT_TRANSMIT 0

/******************************************************************************
 * @parma MH_USART_TIMEOUT_RECEIVE
 * @brief variable specify timeout for receiving data
 *****************************************************************************/
#define MH_USART_TIMEOUT_RECEIVE 0

/******************************************************************************
 * @param MH_USART_TX_GPIO_RCC_DISABLEX
 * @brief variable stops specified usart tx gpio clock
 *****************************************************************************/
#define MH_USART_TX_GPIO_RCC_DISABLE3 __HAL_RCC_GPIOD_CLK_DISABLE()

/******************************************************************************
 * @param MH_USART_RX_GPIO_RCC_DISABLEX
 * @brief variable stops specified usart rx gpio clock
 *****************************************************************************/
#define MH_USART_RX_GPIO_RCC_DISABLE3 __HAL_RCC_GPIOD_CLK_DISABLE()

/******************************************************************************
 * @param MH_ENABLE_USARTX
 * @brief variable enables usart device
 *****************************************************************************/
#define MH_ENABLE_USART3 1
#define MH_ENABLE_USART4 0

/******************************************************************************
 * @param MH_ENABLE_USART_IRQ
 * @brief variable enable usart interrupt mode
 *****************************************************************************/
#define MH_ENABLE_USART_IRQ 1

/******************************************************************************
 * @param MH_USART_IRQ_X
 * @brief specify usart interrupt number
 *****************************************************************************/
#define MH_USART_IRQ3 USART3_IRQn

/******************************************************************************
 * @parm MH_USART_IRQ_PRIORITY_X
 * @brief specify usart irq priority
 *****************************************************************************/
#define MH_USART_IRQ_PRIORITY3 2

/******************************************************************************
 * @parm MH_USART_IRQ_SUBPRIORITY_X
 * @brief specify usart irq subpriority
 *****************************************************************************/
#define MH_USART_IRQ_SUBPRIORITY3 0

/******************************************************************************
 * @param MH_ENABLE_USART_DMA
 * @brief variable enable usart dma mode
 *****************************************************************************/
#define MH_ENABLE_USART_DMA 0

/******************************************************************************
 * @param MH_USART_BAUD_RATE_X
 * @brief specify usart baud rate
 *****************************************************************************/
#define MH_USART_BAUD_RATE3 9600

/******************************************************************************
 * @param MH_USART_WORD_LENGTH_X
 * @brief specify usart word length
 *****************************************************************************/
#define MH_USART_WORD_LENGTH3 UART_WORDLENGTH_8B

/******************************************************************************
 * @param MH_USART_STOP_BITS_X
 * @brief specify usart stop bits
 *****************************************************************************/
#define MH_USART_STOP_BITS3 UART_STOPBITS_1

/******************************************************************************
 * @param MH_USART_PARITY_X
 * @brief specify usart parity
 *****************************************************************************/
#define MH_USART_PARITY3 UART_PARITY_ODD

/******************************************************************************
 * @param MH_USART_HWCTRL_X
 * @brief specify usart hw control
 *****************************************************************************/
#define MH_USART_HWCTRL3 UART_HWCONTROL_NONE

/******************************************************************************
 * @param MH_USART_MODE_X
 * @brief specify usart mode
 *****************************************************************************/
#define MH_USART_MODE3 UART_MODE_TX_RX

/******************************************************************************
 * @param MH_USART_OVERSAMPLING_X
 * @brief specify usart oversampling
 *****************************************************************************/
#define MH_USART_OVERSAMPLING3 UART_OVERSAMPLING_16

/******************************************************************************
 * @param MH_USART_TX_GPIO_PIN_X
 * @brief specify usart tx pin
 *****************************************************************************/
#define MH_USART_TX_GPIO_PIN3 GPIO_PIN_8

/******************************************************************************
 * @param MH_USART_RX_GPIO_PIN_X
 * @brief specify usart rx pin
 *****************************************************************************/
#define MH_USART_RX_GPIO_PIN3 GPIO_PIN_9

/******************************************************************************
 * @param MH_USART_TX_GPIO_PORT_X
 * @brief specify usart tx gpio port
 *****************************************************************************/
#define MH_USART_TX_GPIO_PORT_3 GPIOD

/******************************************************************************
 * @param MH_USART_RX_GPIO_PORT_X
 * @brief specify usart rx gpio port
 *****************************************************************************/
#define MH_USART_RX_GPIO_PORT_3 GPIOD

/******************************************************************************
 * @param MH_USART_TX_GPIO_MODE_X
 * @brief specify usart tx gpio mode
 *****************************************************************************/
#define MH_USART_TX_GPIO_MODE_3 GPIO_MODE_AF_PP

/******************************************************************************
 * @param MH_USART_TX_GPIO_PDPU_X
 * @brief specify usart tx gpio pin pull up or pull down
 *****************************************************************************/
#define MH_USART_TX_GPIO_PDPU_3 GPIO_PULLUP

/******************************************************************************
 * @param MH_USART_TX_GPIO_SPEED_X
 * @brief specify usart tx gpio speed
 *****************************************************************************/
#define MH_USART_TX_GPIO_SPEED_3 GPIO_SPEED_FREQ_HIGH

/******************************************************************************
 * @param MH_USART_TX_GPIO_AF_X
 * @brief specify alternate mode for tx gpio pin
 *****************************************************************************/
#define MH_USART_TX_GPIO_AF_3 GPIO_AF7_USART3

/******************************************************************************
 * @param MH_USART_RX_GPIO_MODE_X
 * @brief specify usart rx gpio mode
 *****************************************************************************/
#define MH_USART_RX_GPIO_MODE_3 GPIO_MODE_AF_PP

/******************************************************************************
 * @param MH_USART_RX_GPIO_PDPU_X
 * @brief specify usart rx gpio pin pull up or pull down
 *****************************************************************************/
#define MH_USART_RX_GPIO_PDPU_3 GPIO_PULLUP

/******************************************************************************
 * @param MH_USART_RX_GPIO_SPEED_X
 * @brief specify usart rx gpio speed
 *****************************************************************************/
#define MH_USART_RX_GPIO_SPEED_3 GPIO_SPEED_FREQ_HIGH

/******************************************************************************
 * @param MH_USART_RX_GPIO_AF_X
 * @brief specify alternate mode for rx gpio pin
 *****************************************************************************/
#define MH_USART_RX_GPIO_AF_3 GPIO_AF7_USART3


#endif /* MH_USART_CONF_H_ */
