/*
 * index.h
 *
 *  Created on: Dec 13, 2019
 *      Author: marcin
 */

#ifndef PAGES_INDEX_H_
#define PAGES_INDEX_H_

#include "page.h"
#include <stddef.h>

char index_http_url [] = "";
char index_http_content [] = "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\"><html><body><h1>INDEX PAGE<br>NOTHING TO SHOW<br></h1></body></html>";

static mh_http_page_t index_page =
{
	index_http_url,
	index_http_content,
	NULL,
	sizeof(index_http_content)
};

#endif /* PAGES_INDEX_H_ */
