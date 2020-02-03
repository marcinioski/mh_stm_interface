/*
 * http_server_low_level.h
 *
 *  Created on: Dec 2, 2019
 *      Author: marcin
 */

#ifndef HTTP_SERVER_LOW_LEVEL_H_
#define HTTP_SERVER_LOW_LEVEL_H_

#include "lwip/opt.h"
#include "lwip/timeouts.h"
#include "netif/ethernet.h"
#include "netif/etharp.h"

/**
 * @brief callback method responsible for sending data to physical layer
 * @param netif pointer to initialized network interface
 * @param pbuf pointer to pbuf object
 * @return ERR_OK on success, other value otherwise
 */
err_t http_server_low_level_output(struct netif* netif, struct pbuf* pbuf);

/**
 * @brief callback method responsible for receiving data from physical layer
 * @param netif pointer to initialized network interface
 * @return pointer to received buffer
 */
struct pbuf * http_server_low_level_input(struct netif *netif);

#endif /* HTTP_SERVER_LOW_LEVEL_H_ */
