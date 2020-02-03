/*
 * applcation_tty.c
 *
 *  Created on: Jan 20, 2020
 *      Author: marcin
 */

#include "mh/devices/device_list.h"
#include "mh/devices/usart/usart_private.h"
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
tty_private_t tty_private;

char app_tty_name[] = "tty";

mh_application_t app_tty = {
	app_tty_name,

};
