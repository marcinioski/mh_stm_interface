/*
 * ethernet_stm32f7.c
 *
 *  Created on: Nov 11, 2019
 *      Author: marcin
 */


#include "mh/devices/ethernet/ethernet.h"
#include "mh/error_handler/error_handler.h"
#include "stm32f7xx_hal.h"

#if MH_ETHERNET_ENABLE_DMA
#if defined ( __GNUC__ )

/******************************************************************************
 * @variable g_mh_eth_dmaRxArr
 * @brief array of rx dma buffers descriptors
 *****************************************************************************/
ETH_DMADescTypeDef g_mh_eth_dmaRxArr[MH_ETHERNET_DMA_RX_BUF_N] __attribute__((section(".RxDescripSection")));

/******************************************************************************
 * @variable g_mh_eth_dmaTxArr
 * @brief array of tx dma buffers descriptors
 *****************************************************************************/
ETH_DMADescTypeDef g_mh_eth_dmaTxArr[MH_ETHERNET_DMA_TX_BUF_N] __attribute__((section(".TxDescripSection")));

/******************************************************************************
 * @variable g_mh_eth_rx_buffers
 * @brief array of rx dma buffers
 *****************************************************************************/
unsigned char g_mh_eth_rx_buffers[MH_ETHERNET_DMA_RX_BUF_N][MH_ETHERNET_RX_BUF_SIZE] __attribute__((section(".RxarraySection")));

/******************************************************************************
 * @variable g_mh_eth_tx_buffers
 * @brief array of tx dma buffers
 *****************************************************************************/
unsigned char g_mh_eth_tx_buffers[MH_ETHERNET_DMA_TX_BUF_N][MH_ETHERNET_TX_BUF_SIZE] __attribute__((section(".TxarraySection")));

#endif
#endif

/*****************************************************************************
 * @variable: g_mh_eth_handle
 * @brief:    global ethernet handle
 ****************************************************************************/
ETH_HandleTypeDef g_mh_eth_handle;

/*****************************************************************************
 * @method: HAL_ETH_MspInit
 * @brief:  method called through HAL_ETH_Init method for initializing gpios
 ****************************************************************************/
void HAL_ETH_MspInit(ETH_HandleTypeDef *heth)
{
	GPIO_InitTypeDef gpios;

	MH_ENABLE_ETH_GPIO_RCC();

	gpios.Speed = GPIO_SPEED_HIGH;
	gpios.Mode = GPIO_MODE_AF_PP;
	gpios.Pull = GPIO_NOPULL;
	gpios.Alternate = GPIO_AF11_ETH;
	gpios.Pin = MH_ETHERNET_RMII_REF_CLK_PIN | MH_ETHERNET_MDIO_PIN | MH_ETHERNET_MII_CRS_DV_PIN;
	HAL_GPIO_Init(GPIOA, &gpios);

	/* Configure PB13 */
	gpios.Pin = MH_ETHERNET_MII_TXD0_PIN;
	HAL_GPIO_Init(GPIOB, &gpios);

	/* Configure PC1, PC4 and PC5 */
	gpios.Pin = MH_ETHERNET_MDC_PIN | MH_ETHERNET_MII_RXD0_PIN | MH_ETHERNET_MII_RXD1_PIN;
	HAL_GPIO_Init(GPIOC, &gpios);

	/* Configure PG2, PG11, PG13 and PG14 */
	gpios.Pin =  MH_ETHERNET_MII_RXER_PIN | MH_ETHERNET_MII_TX_EN_PIN | MH_ETHERNET_MII_TXD0_PIN;
	HAL_GPIO_Init(GPIOG, &gpios);

#if MH_ETHERNET_ENABLE_IRQ
		HAL_NVIC_SetPriority(ETH_IRQn, MH_ETHERNET_IRQ_PREEMPT, MH_ETHERNET_IRQ_SUB_PRIORITY);
		HAL_NVIC_EnableIRQ(ETH_IRQn);
#endif
	MH_ETHERNET_ENABLE_RCC();

	HAL_RCC_MCOConfig(MH_ETHERNET_MCO_DIRECTION,
			MH_ETHERNET_MCO_DIRECTION,
			MH_ETHERNET_MCO_DIVIDER);

}

void _mh_ethernet_init_eth_handle()
{
	uint8_t macaddres [] = {MH_ETHERNET_MAC_ADDR0,
			MH_ETHERNET_MAC_ADDR1,
			MH_ETHERNET_MAC_ADDR2,
			MH_ETHERNET_MAC_ADDR3,
			MH_ETHERNET_MAC_ADDR4,
			MH_ETHERNET_MAC_ADDR5};

	g_mh_eth_handle.Instance = ETH;
	g_mh_eth_handle.Init.MACAddr = macaddres;
	g_mh_eth_handle.Init.AutoNegotiation = MH_ETHERNET_AUTONEGOTIATION;
	g_mh_eth_handle.Init.Speed = MH_ETHERNET_SPEED;
	g_mh_eth_handle.Init.DuplexMode = MH_ETHERNET_DUPLEX_MODE;
	g_mh_eth_handle.Init.MediaInterface = MH_ETHERNET_MEDIA_INTERFACE;
	g_mh_eth_handle.Init.RxMode = MH_ETHERNET_RXMODE;
	g_mh_eth_handle.Init.ChecksumMode = MH_ETHERNET_CHECKSUM_MODE;
	g_mh_eth_handle.Init.PhyAddress = MH_ETHERNET_PHY_ADDRESS;
}

enum MHDeviceState mh_f7_ethernet_init(void* arg)
{
	pmh_device_t mh_dev = (pmh_device_t)arg;
	enum MHDeviceState result = eDSError;

	mh_dev->private_data = &g_mh_eth_handle;

	_mh_ethernet_init_eth_handle();

	if (HAL_ETH_Init(&g_mh_eth_handle) == HAL_OK)
	{

#if MH_ETHERNET_ENABLE_DMA
		if (HAL_ETH_DMATxDescListInit(&g_mh_eth_handle, g_mh_eth_dmaTxArr,
				(uint8_t*)&g_mh_eth_tx_buffers[0][0], MH_ETHERNET_DMA_TX_BUF_N) == HAL_OK)
		{
			if (HAL_ETH_DMARxDescListInit(&g_mh_eth_handle, g_mh_eth_dmaRxArr,
					(uint8_t*)&g_mh_eth_rx_buffers[0][0], MH_ETHERNET_DMA_RX_BUF_N) == HAL_OK)
			{
				result = eDSInitialized;
			}
			else
			{
				Error_Handler();
			}
		}
		else
		{
			Error_Handler();
		}
#endif
	}

	return result;
}

enum MHDeviceState mh_f7_ethernet_start(void* arg)
{

#if MH_ETHERNET_ENABLE_IRQ

#endif

#if MH_ETHERNET_ENABLE_DMA

#endif

	HAL_ETH_Start(&g_mh_eth_handle);

	return eDSStarted;
}

enum MHDeviceState mh_f7_ethernet_stop(void* arg)
{
	(void)arg;
	return eDSError;
}
