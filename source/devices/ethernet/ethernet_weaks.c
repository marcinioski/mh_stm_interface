/*
 * ethernet_weaks.c
 *
 *  Created on: Dec 8, 2019
 *      Author: marcin
 */


#include "mh/devices/ethernet/ethernet.h"

__attribute__((weak)) void user_eth_rx_cplt_callback(ETH_HandleTypeDef * ethHandle)
{
	(void)ethHandle;
}
