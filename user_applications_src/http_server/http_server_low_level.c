/*
 * http_server_low_level.c
 *
 *  Created on: Dec 2, 2019
 *      Author: marcin
 */


#include "mh/devices/device_list.h"
#include "mh/devices/ethernet/ethernet.h"
#include "mh/devices/ethernet/ethernet_private.h"
#include "user_applications/http_server/application_http_server.h"
#include "user_applications/http_server/application_http_server_private.h"
#include "user_applications/http_server/http_server_low_level.h"
#include <string.h>

/**
 * @brief mainly copy paste from LwIP implementation, changed only access to
 * 		  EthHandle object
 */
err_t http_server_low_level_output(struct netif* netif, struct pbuf* pbuf)
{
	err_t result;

	pmh_device_t ethernet = mh_device_startup_get_by_name("ETHERNET");
	pmh_ethernet_private_t private_data = (pmh_ethernet_private_t)ethernet->private_data;
	ETH_HandleTypeDef* EthHandle = private_data->private_data;

	struct pbuf *q;
	uint8_t *buffer = (uint8_t *)(EthHandle->TxDesc->Buffer1Addr);
	__IO ETH_DMADescTypeDef *DmaTxDesc = EthHandle->TxDesc;
	uint32_t framelength = 0;
	uint32_t bufferoffset = 0;
	uint32_t byteslefttocopy = 0;
	uint32_t payloadoffset = 0;

	for (q = pbuf; q != NULL; q = q->next)
	{
		if((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET)
		{
			result = ERR_USE;
			goto error;
		}

		byteslefttocopy = q->len;
		payloadoffset = 0;

		while( (byteslefttocopy + bufferoffset) > ETH_TX_BUF_SIZE )
		{
			/* Copy data to Tx buffer*/
			memcpy( (uint8_t*)((uint8_t*)buffer + bufferoffset),
					(uint8_t*)((uint8_t*)q->payload + payloadoffset),
					(ETH_TX_BUF_SIZE - bufferoffset) );

			/* Point to next descriptor */
			DmaTxDesc = (ETH_DMADescTypeDef *)(DmaTxDesc->Buffer2NextDescAddr);

			/* Check if the buffer is available */
			if((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET)
			{
				result = ERR_USE;
				goto error;
			}

			buffer = (uint8_t *)(DmaTxDesc->Buffer1Addr);

			byteslefttocopy = byteslefttocopy - (ETH_TX_BUF_SIZE - bufferoffset);
			payloadoffset = payloadoffset + (ETH_TX_BUF_SIZE - bufferoffset);
			framelength = framelength + (ETH_TX_BUF_SIZE - bufferoffset);
			bufferoffset = 0;
		}

		/* Copy the remaining bytes */
		memcpy( (uint8_t*)((uint8_t*)buffer + bufferoffset),
				(uint8_t*)((uint8_t*)q->payload + payloadoffset),
				byteslefttocopy );
		bufferoffset = bufferoffset + byteslefttocopy;
		framelength = framelength + byteslefttocopy;
	}

	/* Prepare transmit descriptors to give to DMA */
	HAL_ETH_TransmitFrame(EthHandle, framelength);

	result = ERR_OK;

error:
	/* When Transmit Underflow flag is set, clear it and issue a Transmit Poll Demand to resume transmission */
	if ((EthHandle->Instance->DMASR & ETH_DMASR_TUS) != (uint32_t)RESET)
	{
		/* Clear TUS ETHERNET DMA flag */
		EthHandle->Instance->DMASR = ETH_DMASR_TUS;

		/* Resume DMA transmission*/
		EthHandle->Instance->DMATPDR = 0;
	}

	return result;
}

struct pbuf * http_server_low_level_input(struct netif *netif)
{
	struct pbuf* result;
	struct pbuf* q = NULL;
	uint16_t len = 0;
	uint8_t *buffer;
	__IO ETH_DMADescTypeDef *dmarxdesc;
	uint32_t bufferoffset = 0;
	uint32_t payloadoffset = 0;
	uint32_t byteslefttocopy = 0;
	uint32_t ii=0;

	pmh_device_t ethernet = mh_device_startup_get_by_name("ETHERNET");
	pmh_ethernet_private_t private_data = (pmh_ethernet_private_t)ethernet->private_data;
	ETH_HandleTypeDef* EthHandle = private_data->private_data;

	/* get received frame */
	if(HAL_ETH_GetReceivedFrame_IT(EthHandle) != HAL_OK)
	{
		return NULL;
	}
	/* Obtain the size of the packet and put it into the "len" variable. */
	len = EthHandle->RxFrameInfos.length;
	buffer = (uint8_t *)EthHandle->RxFrameInfos.buffer;

	if (len > 0)
	{
		/* We allocate a pbuf chain of pbufs from the Lwip buffer pool */
		result = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
	}

	if (result != NULL)
	{
		dmarxdesc = EthHandle->RxFrameInfos.FSRxDesc;
		bufferoffset = 0;

		for(q = result; q != NULL; q = q->next)
		{
			byteslefttocopy = q->len;
			payloadoffset = 0;

			/* Check if the length of bytes to copy in current pbuf is bigger than Rx buffer size */
			while( (byteslefttocopy + bufferoffset) > ETH_RX_BUF_SIZE )
			{
				/* Copy data to pbuf */
				memcpy( (uint8_t*)((uint8_t*)q->payload + payloadoffset),
						(uint8_t*)((uint8_t*)buffer + bufferoffset),
						(ETH_RX_BUF_SIZE - bufferoffset));

				/* Point to next descriptor */
				dmarxdesc = (ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
				buffer = (uint8_t *)(dmarxdesc->Buffer1Addr);

				byteslefttocopy = byteslefttocopy - (ETH_RX_BUF_SIZE - bufferoffset);
				payloadoffset = payloadoffset + (ETH_RX_BUF_SIZE - bufferoffset);
				bufferoffset = 0;
			}

			/* Copy remaining data in pbuf */
			memcpy( (uint8_t*)((uint8_t*)q->payload + payloadoffset),
					(uint8_t*)((uint8_t*)buffer + bufferoffset),
					byteslefttocopy);
			bufferoffset = bufferoffset + byteslefttocopy;
		}
	}

	/* Release descriptors to DMA */
	/* Point to first descriptor */
	dmarxdesc = EthHandle->RxFrameInfos.FSRxDesc;
	/* Set Own bit in Rx descriptors: gives the buffers back to DMA */

	for (ii=0; ii< EthHandle->RxFrameInfos.SegCount; ii++)
	{
		dmarxdesc->Status |= ETH_DMARXDESC_OWN;
		dmarxdesc = (ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
	}

	/* Clear Segment_Count */
	EthHandle->RxFrameInfos.SegCount =0;

	/* When Rx Buffer unavailable flag is set: clear it and resume reception */
	if ((EthHandle->Instance->DMASR & ETH_DMASR_RBUS) != (uint32_t)RESET)
	{
		/* Clear RBUS ETHERNET DMA flag */
		EthHandle->Instance->DMASR = ETH_DMASR_RBUS;
		/* Resume DMA reception */
		EthHandle->Instance->DMARPDR = 0;
	}

	return result;
}
