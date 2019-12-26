/*
 * ethernet_private.h
 *
 *  Created on: Nov 21, 2019
 *      Author: marcin
 */

#ifndef MH_ETHERNET_PRIVATE_H_
#define MH_ETHERNET_PRIVATE_H_

typedef struct
{
	unsigned char macAddr[6];
	void* private_data;
} mh_ethernet_private_t, *pmh_ethernet_private_t;

#endif /* MH_ETHERNET_PRIVATE_H_ */
