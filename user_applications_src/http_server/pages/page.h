/*
 * page.h
 *
 *  Created on: Dec 19, 2019
 *      Author: marcin
 */

#ifndef HTTP_SERVER_PAGES_PAGE_H_
#define HTTP_SERVER_PAGES_PAGE_H_

typedef void (*mh_http_content_gen_clb_t)(char* arguments);

typedef struct
{
	char * url;
	char * content;
	mh_http_content_gen_clb_t generate;
	uint16_t len;
} mh_http_page_t, *pmh_http_page_t;

typedef struct mh_http_page_node
{
	pmh_http_page_t page;
	struct mh_http_page_node* next;
} mh_http_page_node_t, *pmh_http_page_node_t;

#endif /* HTTP_SERVER_PAGES_PAGE_H_ */
