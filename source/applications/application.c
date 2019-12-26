/*
 * application.c
 *
 *  Created on: Nov 20, 2019
 *      Author: marcin
 */


#include "mh/applications/application_list.h"
#include "mh/error_handler/error_handler.h"

extern struct mh_application_node g_user_applications;

void mh_init_startup_applications(void)
{
	struct mh_application_node* node = &g_user_applications;

	while(node)
	{
		pmh_application_t app = node->application;
		MH_APPLICATION_INIT(app);
		if (app && app->state != eASInitialized)
		{
			Log_Init_Error(app->name, app->last_error);
		}

		node = node->next;
	}
}

void mh_start_startup_applications(void)
{
	struct mh_application_node* node = &g_user_applications;

	while(node)
	{
		pmh_application_t app = node->application;
		MH_APPLICATION_START(app);
		if (app && app->state != eASStarted)
		{
			Log_Startup_Error(app->name, app->last_error);
		}

		node = node->next;
	}
}

void mh_stop_startup_applications(void)
{
	struct mh_application_node* node = &g_user_applications;

	while(node)
	{
		pmh_application_t app = node->application;
		MH_APPLICATION_STOP(app);
		if (app && app->state != eASStopped)
		{
			Log_Stop_Error(app->name, app->last_error);
		}

		node = node->next;
	}
}
