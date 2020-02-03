/*
 * user_applications.c
 *
 *  Created on: Nov 20, 2019
 *      Author: marcin
 */


#include "mh/applications/application_list.h"

/******************************************************************************
 * @brief list of user applications which will be configured on startup
 *****************************************************************************/
extern mh_application_t app_http_server;

struct mh_application_node app_server = {&app_http_server, NULL};
struct mh_application_node g_user_applications = {NULL, &app_server};
