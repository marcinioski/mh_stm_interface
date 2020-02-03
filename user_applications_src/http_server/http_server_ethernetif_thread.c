/*
 * http_server_ethernetif_thread.c
 *
 *  Created on: Dec 3, 2019
 *      Author: marcin
 */


#include "mh/devices/device_list.h"
#include "mh/devices/ethernet/ethernet_private.h"
#include "mh/freertos_api/freertos_api.h"
#include "user_applications/http_server/application_http_server.h"
#include "user_applications/http_server/application_http_server_private.h"
#include "user_applications/http_server/application_http_server_threads.h"
#include "user_applications/http_server/http_server_low_level.h"
#include <lwip/tcpip.h>
#include "cmsis_os.h"
#include <stddef.h>

osSemaphoreId _g_semaphore = NULL;

#define TIME_WAITING_FOR_INPUT (osWaitForever)

/******************************************************************************
 * @method _http_server_ethernetif_input_thread_init
 * @brief initialization method for ethernetif input thread
 * @param arg - UNUSED
 * @return None
 *****************************************************************************/
void _http_server_ethernetif_input_thread_init(void* arg);

/******************************************************************************
 * @method http_server_ethernetif_input_thread
 * @brief entry method for ethternetif thread
 * @param arg - pointer to netif structure
 * @return None
 *****************************************************************************/
void http_server_ethernetif_input_thread(void const* arg);

/******************************************************************************
 * @method user_eth_rx_cplt_callback
 * @brief called when ethernet peripheral finished receiving packet. Main goal
 *        of this method is to release a system semaohore.
 * @param ethHandle - UNUSED
 * @return None
 *****************************************************************************/
void user_eth_rx_cplt_callback(ETH_HandleTypeDef* ethHandle)
{
	(void)ethHandle;
	osSemaphoreRelease(_g_semaphore);
}

volatile mh_fr_thread_t http_server_ethernetif_input_thr = {
		{"httpETHIF" \
		, &http_server_ethernetif_input_thread \
		, osPriorityAboveNormal \
		, 1 \
		, DEFAULT_THREAD_STACKSIZE},
		&_http_server_ethernetif_input_thread_init,
		NULL,
		1,
		eTHSUnknown
};

void _http_server_ethernetif_input_thread_init(void* arg)
{
	(void)arg;
	osSemaphoreDef(SEM);
	_g_semaphore = osSemaphoreCreate(osSemaphore(SEM) , 1 );
}

void http_server_ethernetif_input_thread(void const* arg)
{
	if (arg != NULL)
	{
		struct netif* netif = (struct netif*)arg;
		struct pbuf* buffer = NULL;

		while(http_server_ethernetif_input_thr.thread_state != eTHSStopping)
		{
			if (osSemaphoreWait(_g_semaphore, TIME_WAITING_FOR_INPUT)==osOK)
			{
				do
				{
					buffer = http_server_low_level_input(netif);
					if (buffer != NULL)
					{
						if (netif->input(buffer, netif) != ERR_OK )
						{
							pbuf_free(buffer);
						}
					}
				}while (buffer!=NULL);
			}
		}

		http_server_ethernetif_input_thr.thread_state = eTHSStopped;
	}
}
