/*
 * applcation_tty.c
 *
 *  Created on: Jan 20, 2020
 *      Author: marcin
 */

#include "mh/devices/device_list.h"
#include "mh/devices/usart/usart_private.h"
#include "mh/devices/usart/usart.h"
#include "mh/freertos_api/freertos_api.h"
#include "mh/error_handler/error_codes.h"
#include "user_applications/tty/application_tty.h"
#include "user_applications/tty/application_tty_private.h"
#include "user_applications/tty/application_tty_defines.h"

/**
 ******************************************************************************
 * @brief private structure used for handling tty specific data
 ******************************************************************************
 */
tty_private_t app_tty_private;

/**
 ******************************************************************************
 * @brief name of tty application
 ******************************************************************************
 */
char app_tty_name[] = "tty";



enum MHApplicationState app_tty_init(void* arg)
{
	enum MHApplicationState result = eASInitialized;

	(void)arg;

	return result;
}

enum MHApplicationState app_tty_start(void* arg)
{
	enum MHApplicationState result = eASError;

	(void)arg;

	pmh_device_t dev = NULL;

	size_t* len = NULL;
	char* buffer = NULL;

	MH_USART3_READ(dev, buffer, 0, len);
	MH_USART3_WRITE(dev, buffer, 0, len);

	return result;
}

enum MHApplicationState app_tty_stop(void* arg)
{
	enum MHApplicationState result = eASError;

	(void)arg;

	return result;
}

mh_fr_thread_node_t app_tty_main_thread = {
	UNKNOWN_THREAD, UNKNOWN_THREAD
};

mh_application_t app_tty = {
	app_tty_name,
	&app_tty_init,
	&app_tty_start,
	&app_tty_stop,
	NULL,
	&app_tty_private,
	&app_tty_main_thread,
	eASUnknown,
	0
};
