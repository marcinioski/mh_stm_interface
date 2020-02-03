/*
 * application_http_server_threads.h
 *
 *  Created on: Dec 3, 2019
 *      Author: marcin
 */

#ifndef APPLICATION_HTTP_SERVER_THREADS_H_
#define APPLICATION_HTTP_SERVER_THREADS_H_

#include "application_http_server_private.h"
#include "application_http_server.h"

void http_server_netconn_thread(void const* arg);
void http_server_ethernetif_input_thread(void const* arg);

#endif /* APPLICATION_HTTP_SERVER_THREADS_H_ */
