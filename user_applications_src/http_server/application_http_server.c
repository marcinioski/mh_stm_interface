/*
 * application_http_server.c
 *
 *  Created on: Nov 20, 2019
 *      Author: marcin
 */

#include "mh/devices/device_list.h"
#include "mh/devices/ethernet/ethernet_private.h"
#include "mh/freertos_api/freertos_api.h"
#include "mh/error_handler/error_codes.h"
#include "user_applications/http_server/application_http_server.h"
#include "user_applications/http_server/application_http_server_private.h"
#include "user_applications/http_server/http_server_low_level.h"
#include <lwip/tcpip.h>

extern mh_fr_thread_t http_server_netconn_thr;
extern mh_fr_thread_t http_server_ethernetif_input_thr;

/******************************************************************************
 * @brief private data of app http server application
 *****************************************************************************/
http_server_private_t app_http_server_private;

u32_t sys_now(void)
{
	return HAL_GetTick();
}

/******************************************************************************
 * @brief initializes privte_data basing on device
 * @param netif - pointer to netif structure
 * @return 0 on success, otherwise negative
 *****************************************************************************/
char _app_http_server_init_private(struct netif* netif)
{
	char result = 1;

	if (netif)
	{
		pmh_device_t ethernet = mh_device_startup_get_by_name("ETHERNET");
		if (ethernet)
		{
			pmh_ethernet_private_t device_private = (pmh_ethernet_private_t)ethernet->private_data;

			if (device_private)
			{
				result = 0;

				netif->hwaddr[0] = device_private->macAddr[0];
				netif->hwaddr[1] = device_private->macAddr[1];
				netif->hwaddr[2] = device_private->macAddr[2];

				netif->hwaddr[3] = device_private->macAddr[3];
				netif->hwaddr[4] = device_private->macAddr[4];
				netif->hwaddr[5] = device_private->macAddr[5];

				netif->hwaddr_len = 6;

				netif->flags |= NETIF_FLAG_LINK_UP;
				netif->mtu = APP_HTTP_SERVER_MTU;
				netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;
			}
		}
	}

	return result;
}

err_t _app_http_server_ethernetif_init(struct netif *netif)
{
	LWIP_ASSERT("netif != NULL", (netif != NULL));

#if 0
	netif->name[0] = IFNAME0;
	netif->name[1] = IFNAME1;

#endif
	netif->linkoutput = http_server_low_level_output;

	netif->output = etharp_output;

	_app_http_server_init_private(netif);

	return ERR_OK;
}

/******************************************************************************
 * @brief initialized network interface
 * @param netif - pointer to network interface
 * @return None
 *****************************************************************************/
void _app_http_server_initialize_netif(struct netif* netif)
{
	ip_addr_t address;
	ip_addr_t netmask;
	ip_addr_t gateway;

	IP_ADDR4(&address, APP_HTTP_SERVER_IP_ADDR0, APP_HTTP_SERVER_IP_ADDR1, APP_HTTP_SERVER_IP_ADDR2, APP_HTTP_SERVER_IP_ADDR3);
	IP_ADDR4(&netmask, APP_HTTP_SERVER_NETMASK0, APP_HTTP_SERVER_NETMASK1, APP_HTTP_SERVER_NETMASK2, APP_HTTP_SERVER_NETMASK3);
	IP_ADDR4(&gateway, APP_HTTP_SERVER_GW_0, APP_HTTP_SERVER_GW_1, APP_HTTP_SERVER_GW_2, APP_HTTP_SERVER_GW_3);

	netif_add(netif, &address, &netmask, &gateway, NULL, &_app_http_server_ethernetif_init, &tcpip_input);

	netif_set_default(netif);

	if (netif_is_link_up(netif))
	{
		netif_set_up(netif);
	}
	else
	{
		netif_set_down(netif);
	}
}

/******************************************************************************
 * @brief initialize netif library and tcp ip stack
 * @param netif - pointer to network interface
 * @return None
 *****************************************************************************/
void _app_http_server_init_netif(struct netif* netif)
{
	tcpip_init(NULL, NULL);

	_app_http_server_initialize_netif(netif);

	http_server_ethernetif_input_thr.arg = netif;
}

enum MHApplicationState app_http_server_init(void* arg)
{
	enum MHApplicationState result = eASInitialized;

	(void)arg;

	return result;
}

enum MHApplicationState app_http_server_start(void* arg)
{
	enum MHApplicationState result = eASError;
	pmh_application_t application = (pmh_application_t)arg;
	phttp_server_private_t server = (phttp_server_private_t)application->private_data;

	_app_http_server_init_netif(&server->netif);
	if (mh_fr_start_thread_list(application->thread) == MH_ERR_SUCCESS)
	{
		result = eASStarted;
		application->last_error = MH_ERR_SUCCESS;
	}
	else
	{
		application->last_error = MH_ERR_CANNOT_START_THR;
	}

	return result;
}

enum MHApplicationState app_http_server_stop(void* arg)
{
	enum MHApplicationState result = eASError;
	pmh_application_t application = (pmh_application_t)arg;

	return result;
}

char app_http_server_name[] = "httpserver";

mh_fr_thread_node_t app_http_server_thread_ethernetif_input = {
		&http_server_ethernetif_input_thr, UNKNOWN_THREAD
};

mh_fr_thread_node_t app_http_server_thread_netconn = {
		&http_server_netconn_thr, &app_http_server_thread_ethernetif_input
};

mh_fr_thread_node_t app_http_server_thread_list = {
		UNKNOWN_THREAD, &app_http_server_thread_netconn
};

mh_application_t app_http_server = {
	app_http_server_name,
	&app_http_server_init,
	&app_http_server_start,
	&app_http_server_stop,
	NULL,
	&app_http_server_private,
	&app_http_server_thread_list,
	eASUnknown,
	0
};
