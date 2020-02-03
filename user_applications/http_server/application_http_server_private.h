/*
 * application_http_server_private.h
 *
 *  Created on: Nov 21, 2019
 *      Author: marcin
 */

#ifndef USER_APPLICATION_HTTP_SERVER_PRIVATE_H_
#define USER_APPLICATION_HTTP_SERVER_PRIVATE_H_

#include "lwip/opt.h"
#include "lwip/timeouts.h"
#include "netif/ethernet.h"
#include "netif/etharp.h"

typedef struct
{
	struct netif netif;
} http_server_private_t, *phttp_server_private_t;

#define APP_HTTP_SERVER_MTU 1500

#define APP_HTTP_SERVER_IP_ADDR0 192
#define APP_HTTP_SERVER_IP_ADDR1 168
#define APP_HTTP_SERVER_IP_ADDR2 20
#define APP_HTTP_SERVER_IP_ADDR3 20

#define APP_HTTP_SERVER_NETMASK0 255
#define APP_HTTP_SERVER_NETMASK1 255
#define APP_HTTP_SERVER_NETMASK2 0
#define APP_HTTP_SERVER_NETMASK3 0

#define APP_HTTP_SERVER_GW_0 192
#define APP_HTTP_SERVER_GW_1 168
#define APP_HTTP_SERVER_GW_2 20
#define APP_HTTP_SERVER_GW_3 1

#endif /* USER_APPLICATION_HTTP_SERVER_PRIVATE_H_ */
