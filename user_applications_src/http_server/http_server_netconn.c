/*
 * http_server_netconn.c
 *
 *  Created on: Nov 27, 2019
 *      Author: marcin
 */

#include "mh/devices/device_list.h"
#include "mh/devices/ethernet/ethernet_private.h"
#include "mh/freertos_api/freertos_api.h"
#include "user_applications/http_server/application_http_server.h"
#include "user_applications/http_server/application_http_server_private.h"
#include "user_applications/http_server/application_http_server_threads.h"
#include "user_applications/http_server/application_http_server_defines.h"
#include "pages/page.h"
#include "pages/index.h"
#include <lwip/tcpip.h>
#include "cmsis_os.h"
#include <stddef.h>
#include <string.h>

/******************************************************************************
 * @method http_server_netconn_thread
 * @brief main method used for handling user input events through ethernet
 * @param arg
 * @return None
 *****************************************************************************/
void http_server_netconn_thread(void const* arg);

mh_http_page_node_t http_pages = {&index_page, NULL};

volatile mh_fr_thread_t http_server_netconn_thr = {
		{"httpNETCONN" \
		, &http_server_netconn_thread \
		, osPriorityAboveNormal \
		, 1 \
		, DEFAULT_THREAD_STACKSIZE},
		NULL,
		NULL,
		1,
		eTHSUnknown
};

pmh_http_page_t _http_server_find_page(char* buf, int buflen)
{
	if (buflen > 0)
	{
		pmh_http_page_node_t current_page = &http_pages;
		while (current_page)
		{
			if (strncmp(buf, current_page->page->url, buflen) == 0)
			{
				return current_page->page;
			}
			current_page = current_page->next;
		}
	}

	return NULL;
}

void _http_server_generate_status_200(struct netconn* netconn, size_t contLen)
{
	(void)netconn;
	(void)contLen;
}

void _http_server_generate_status_400(struct netconn* netconn)
{
	(void)netconn;
}

void _http_server_handle_GET(struct netconn* netconn, char* buf, int buflen, struct netbuf* inbuf)
{
	char* content = NULL;
	int content_len = 0;
	if (buflen == 0)
	{
		content = index_http_content;
		content_len = sizeof(index_http_content);
	}
	else
	{
		pmh_http_page_t page = _http_server_find_page(buf, buflen);
		if (page)
		{
			if (page->generate)
			{
				page->generate(buf);
			}
			content = page->content;
			content_len = page->len;
		}
	}

	if (content && content_len)
	{
		_http_server_generate_status_200(netconn, content_len);
		netconn_write(netconn,
					(const unsigned char*)content,
					(size_t)sizeof(content_len),
					NETCONN_NOCOPY);
	}
	else
	{
		_http_server_generate_status_400(netconn);
	}
}

void _http_server_handle_POST(struct netconn* netconn, char* buf, int buflen, struct netbuf* inbuf)
{
	(void)netconn;
	(void)inbuf;
	(void)buflen;
	(void)buf;
}

void _http_server_netconn_serve_netconn(struct netconn* netconn)
{
	struct netbuf *inbuf;
	err_t recv_err;
	char* buf;
	u16_t buflen;

	/* Read the data from the port, blocking if nothing yet there.
	We assume the request (the part we care about) is in one netbuf */
	recv_err = netconn_recv(netconn, &inbuf);

	if (recv_err == ERR_OK)
	{
		if (netconn_err(netconn) == ERR_OK)
		{
			netbuf_data(inbuf, (void**)&buf, &buflen);

			/* Is this an HTTP GET command? (only check the first 5 chars, since
			there are other formats for GET, and we're keeping it very simple )*/
			if ((buflen >=5) && (strncmp(buf, "GET /", 5) == 0))
			{
				_http_server_handle_GET(netconn, buf + 5, buflen - 5, inbuf);

#if 0
				else if(strncmp(buf, "GET /STM32F7xxTASKS.html", 24) == 0)
				{
				   /* Load dynamic page */
					DynWebPage(netconn);
				}
#endif
			}
			if ((buflen >= 6) && strncmp(buf, "POST /", 5) == 0)
			{
				_http_server_handle_POST(netconn, buf, buflen, inbuf);
			}
		}
	}

	/* Close the connection (server closes in HTTP) */
	netconn_close(netconn);

	/* Delete the buffer (netconn_recv gives us ownership,
	so we have to make sure to deallocate the buffer) */

	netbuf_delete(inbuf);

}

void http_server_netconn_thread(void const* arg)
{
	struct netconn *conn, *newconn;
	err_t err, accept_err;

	/* Create a new TCP connection handle */
	conn = netconn_new(APP_HTTP_SERVER_NETCONN_TYPE);

	if (conn!= NULL)
	{
		err = netconn_bind(conn, NULL, APP_HTTP_SERVER_NETCONN_PORT);

		if (err == ERR_OK)
		{
			/* Put the connection into LISTEN state */
			netconn_listen(conn);

			http_server_netconn_thr.thread_state = eTHSStarted;

			while(http_server_netconn_thr.thread_state != eTHSStopping)
			{
				/* accept any icoming connection */
				accept_err = netconn_accept(conn, &newconn);
				if(accept_err == ERR_OK)
				{
					/* serve connection */
					_http_server_netconn_serve_netconn(newconn);

					/* delete connection */
					netconn_delete(newconn);
				}
			}

			http_server_netconn_thr.thread_state = eTHSStopped;
		}
	}
}

void http_server_netconn_init(pmh_application_t application)
{
	http_server_netconn_thr.thread_state = eTHSStarting;
	mh_fr_start_thread(&http_server_netconn_thr);
}
