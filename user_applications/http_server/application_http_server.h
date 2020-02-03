/*
 * application_http_server.h
 *
 *  Created on: Nov 20, 2019
 *      Author: marcin
 */

#ifndef APPLICATION_HTTP_SERVER_H_
#define APPLICATION_HTTP_SERVER_H_

#include "mh/applications/application.h"

enum MHApplicationState app_http_server_init(void* arg);

enum MHApplicationState app_http_server_start(void* arg);

enum MHApplicationState app_http_server_stop(void* arg);

#endif /* APPLICATION_HTTP_SERVER_H_ */
