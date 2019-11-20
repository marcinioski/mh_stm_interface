/*
 * error_handler.c
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin hujdus
 */

#include "mh/mh_config_system.h"
#include "mh/error_handler/error_handler.h"

void _Error_Handler()
{
#if MH_ERROR_HANDLER_ALLOW_ASSERT
	assert();
#endif
}

void Error_Handler(void)
{
	while(1)
	{
		_Error_Handler();
	}
}

void Log_Init_Error(char* dev_name, int error_no)
{
#if MH_INIT_ERROR_ALLOW_ASSERT
	assert();
#endif
}

void Log_Startup_Error(char* dev_name, int error_no)
{
#if MH_STARTUP_ERROR_ALLOW_ASSERT
	assert();
#endif
}

void Log_Stop_Error(char* dev_name, int error_no)
{
#if MH_STOP_ERROR_ALLOW_ASSERT
	assert();
#endif
}
