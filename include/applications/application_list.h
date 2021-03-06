/*
 * application_list.h
 *
 *  Created on: Nov 19, 2019
 *      Author: marcin
 */

#ifndef MH_APPLICATION_LIST_H_
#define MH_APPLICATION_LIST_H_

#include "mh/applications/application.h"

#include "mh/mh_config_system.h"

#define UNKNOWN_APPLICATION NULL

/******************************************************************************
 * @brief entry for application list
 *****************************************************************************/
typedef struct mh_application_node
{
	pmh_application_t application;
	struct mh_application_node* next;
} mh_application_node_t, *pmh_application_node_t;

/******************************************************************************
 * @brief appends application to list of startup applications
 *****************************************************************************/
void mh_append_startup_application(struct mh_application_node* node);

/******************************************************************************
 * @brief method returns specific application based on name
 *****************************************************************************/

#endif /* MH_APPLICATION_LIST_H_ */
