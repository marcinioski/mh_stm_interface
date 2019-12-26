/*
 * ethernet_conf.h
 *
 *  Created on: Nov 11, 2019
 *      Author: marcin
 */

#ifndef MH_ETHERNET_CONF_H_
#define MH_ETHERNET_CONF_H_

#include "mh/mh_config_system.h"

/* ****************************************************************************
 * @param: MH_ETHERNET_ENABLE_MDIO
 * @brief: enables MDIO interface in system
 * ***************************************************************************/
#define MH_ETHERNET_ENABLE_MDIO 1

/* ****************************************************************************
 * @param: MH_ETHERNET_ENABLE_MII
 * @brief: enables MII interface in system
 * ***************************************************************************/
#define MH_ETHERNET_ENABLE_MII 0

/* ****************************************************************************
 * @param: MH_ETHERNET_ENABLE_IRQ
 * @brief: enables interrupts for ethernet
 * ***************************************************************************/
#define MH_ETHERNET_ENABLE_IRQ 1

/* ****************************************************************************
 * @param: MH_ETHERNET_IRQ_PREEMPT
 * @brief: specify ethernet interrupt preempt value
 * ***************************************************************************/
#define MH_ETHERNET_IRQ_PREEMPT 7

/* ****************************************************************************
 * @param: MH_ETHERNET_IRQ_SUB_PRIORITY
 * @brief: specify ethernet interrupt sub priority value
 * ***************************************************************************/
#define MH_ETHERNET_IRQ_SUB_PRIORITY 0


/* ****************************************************************************
 * @param: MH_ETHERNET_ENABLE_RCC
 * @brief: enables ethernet clock
 * ***************************************************************************/
#define MH_ETHERNET_ENABLE_RCC() __HAL_RCC_ETH_CLK_ENABLE()

/* ****************************************************************************
 * @param: MH_ETHERNET_MCO_DIRECTION
 * @brief: specify MCO clock direction
 * ***************************************************************************/
#define MH_ETHERNET_MCO_DIRECTION RCC_MCO1

/* ****************************************************************************
 * @param: MH_ETHERNET_MCO_SOURCE
 * @brief: specify MCO clock source
 * ***************************************************************************/
#define MH_ETHERNET_MCO_SOURCE RCC_MCO1SOURCE_PLLCLK

/* ****************************************************************************
 * @param: MH_ETHERNET_MCO_DIVIDER
 * @brief: specify MCO clock divider
 * ***************************************************************************/
#define MH_ETHERNET_MCO_DIVIDER RCC_MCODIV_4

/* ****************************************************************************
 * @param: MH_ETHERNET_MAC_ADDRX
 * @brief: ethernet mac addres one byte
 * ***************************************************************************/
#define MH_ETHERNET_MAC_ADDR0 0x01
#define MH_ETHERNET_MAC_ADDR1 0x20
#define MH_ETHERNET_MAC_ADDR2 0x22
#define MH_ETHERNET_MAC_ADDR3 0x01
#define MH_ETHERNET_MAC_ADDR4 0x01
#define MH_ETHERNET_MAC_ADDR5 0x01

/* ****************************************************************************
 * @param: MH_ETHERNET_AUTONEGTIATION
 * @brief: choose does autonegtiation should be enabled or not
 * ***************************************************************************/
#define MH_ETHERNET_AUTONEGOTIATION ETH_AUTONEGOTIATION_DISABLE

/* ****************************************************************************
 * @param: MH_ETHERNET_SPEED
 * @brief: choose ethernet speed
 * ***************************************************************************/
#define MH_ETHERNET_SPEED ETH_SPEED_10M

/* ****************************************************************************
 * @param: MH_ETHERNET_DUPLEX_MODE
 * @brief: choose duplex mode for interface
 * ***************************************************************************/
#define MH_ETHERNET_DUPLEX_MODE ETH_MODE_FULLDUPLEX

/* ****************************************************************************
 * @param: MH_ETHERNET_MEDIA_INTERFACE
 * @brief: choose media interface mode
 * ***************************************************************************/
#define MH_ETHERNET_MEDIA_INTERFACE ETH_MEDIA_INTERFACE_RMII

/* ****************************************************************************
 * @param: MH_ETHERNET_RXMODE
 * @brief: choose rx interface mode
 * ***************************************************************************/
#define MH_ETHERNET_RXMODE ETH_RXINTERRUPT_MODE

/* ****************************************************************************
 * @param: MH_ETHERNET_CHECKSUM_MODE
 * @brief: choose checksum mode
 * ***************************************************************************/
#define MH_ETHERNET_CHECKSUM_MODE ETH_CHECKSUM_BY_HARDWARE

/* ****************************************************************************
 * @param: MH_ETHERNET_PHY_ADDRESS
 * @brief: set phy address
 * ***************************************************************************/
#define MH_ETHERNET_PHY_ADDRESS 0x00

/* ****************************************************************************
 * @param: MH_ETHERNET_ENABLE_DMA
 * @brief: variable decide about initialization of DMA controller for ethernet
 * ***************************************************************************/
#define MH_ETHERNET_ENABLE_DMA 1

#if MH_ETHERNET_ENABLE_DMA

/*****************************************************************************
 * @param: MH_ETHERNET_DMA_RX_BUF_N
 * @brief: variable describe number of ethernet rx dma buffers
 ****************************************************************************/
#define MH_ETHERNET_DMA_RX_BUF_N 4

/*****************************************************************************
 * @param: MH_ETHERNET_DMA_TX_BUF_N
 * @brief: variable describe number of ethernet tx dma buffers
 ****************************************************************************/
#define MH_ETHERNET_DMA_TX_BUF_N 4

#endif

/******************************************************************************
 * @param: MH_ETHERNET_RX_BUF_SIZE
 * @brief: ethernet rx buffers size
 *****************************************************************************/
#define MH_ETHERNET_RX_BUF_SIZE ETH_MAX_PACKET_SIZE

/******************************************************************************
 * @param: MH_ETHERNET_TX_BUF_SIZE
 * @brief: ethernet tx buffers size
 *****************************************************************************/
#define MH_ETHERNET_TX_BUF_SIZE ETH_MAX_PACKET_SIZE

#ifdef MH_STM_COREF4
MH_ENABLE_ETH_GPIO_RCC() ;

#define MH_ETHERNET_RMII_REF_CLK_PIN GPIO_PIN_1
#define MH_ETHERNET_RMII_REF_CLK_GPIO GPIOA

#define MH_ETHERNET_MDIO_PIN GPIO_PIN_2
#define MH_ETHERNET_MDIO_GPIO GPIOA

#define MH_ETHERNET_MDC_PIN GPIO_PIN_1
#define MH_ETHERNET_MDC_GPIO GPIOC

#define MH_ETHERNET_MII_CRS_DV_PIN GPIO_PIN_7
#define MH_ETHERNET_MII_CRS_DV_GPIO GPIOA

#define MH_ETHERNET_MII_RXD0_PIN GPIO_PIN_4
#define MH_ETHERNET_MII_RXD0_GPIO GPIOC

#define MH_ETHERNET_MII_RXD1_PIN GPIO_PIN_5
#define MH_ETHERNET_MII_RXD1_GPIO GPIOC

#define MH_ETHERNET_MII_RXER_PIN GPIO_PIN_2
#define MH_ETHERNET_MII_RXER_GPIO GPIOG

#define MH_ETHERNET_MII_TX_EN_PIN GPIO_PIN_11
#define MH_ETHERNET_MII_TX_EN_GPIO GPIOG

#define MH_ETHERNET_MII_TXD0_PIN GPIO_PIN_13
#define MH_ETHERNET_MII_TXD0_GPIO GPIOG

#define MH_ETHERNET_MII_TXD1_PIN GPIO_PIN_13
#define MH_ETHERNET_MII_TXD1_GPIO GPIOB

#endif

#ifdef MH_STM_COREF7

#define MH_ETHERNET_RMII_REF_CLK_PIN GPIO_PIN_1
#define MH_ETHERNET_RMII_REF_CLK_GPIO GPIOA

#define MH_ETHERNET_MDIO_PIN GPIO_PIN_2
#define MH_ETHERNET_MDIO_GPIO GPIOA

#define MH_ETHERNET_MDC_PIN GPIO_PIN_1
#define MH_ETHERNET_MDC_GPIO GPIOC

#define MH_ETHERNET_MII_CRS_DV_PIN GPIO_PIN_7
#define MH_ETHERNET_MII_CRS_DV_GPIO GPIOA

#define MH_ETHERNET_MII_RXD0_PIN GPIO_PIN_4
#define MH_ETHERNET_MII_RXD0_GPIO GPIOC

#define MH_ETHERNET_MII_RXD1_PIN GPIO_PIN_5
#define MH_ETHERNET_MII_RXD1_GPIO GPIOC

#define MH_ETHERNET_MII_RXER_PIN GPIO_PIN_2
#define MH_ETHERNET_MII_RXER_GPIO GPIOG

#define MH_ETHERNET_MII_TX_EN_PIN GPIO_PIN_11
#define MH_ETHERNET_MII_TX_EN_GPIO GPIOG

#define MH_ETHERNET_MII_TXD0_PIN GPIO_PIN_13
#define MH_ETHERNET_MII_TXD0_GPIO GPIOG

#define MH_ETHERNET_MII_TXD1_PIN GPIO_PIN_13
#define MH_ETHERNET_MII_TXD1_GPIO GPIOB

#if MH_ETHERNET_ENABLE_MII
#define MH_ENABLE_ETH_GPIO_RCC() ;
#else

#define MH_ENABLE_ETH_GPIO_RCC() __HAL_RCC_GPIOA_CLK_ENABLE(); \
	__HAL_RCC_GPIOB_CLK_ENABLE(); \
	__HAL_RCC_GPIOC_CLK_ENABLE(); \
	__HAL_RCC_GPIOG_CLK_ENABLE();
#endif

#endif



#endif /* MH_ETHERNET_CONF_H_ */
