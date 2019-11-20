/*
 * freertos_api.c
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin
 */

#include "mh/freertos_api/freertos_api.h"

/* ****************************************************************************
 * @variable: mh_fr_threads_start_list
 * @brief:    list of threads to start during free rtos setting up
 * ***************************************************************************/
static pmh_fr_thread_t mh_fr_threads_start_list;

void mh_fr_start_kernel(void)
{
	pmh_fr_thread_t threadToRun = mh_fr_threads_start_list;
	while (threadToRun)
	{
		osThreadCreate(&threadToRun->thread, threadToRun->arg);
		threadToRun = (pmh_fr_thread_t)threadToRun->nextThread;
	}

	osKernelStart();
}

unsigned char mh_fr_append_thread(pmh_fr_thread_t mh_thread)
{
	if (mh_fr_threads_start_list)
	{
		pmh_fr_thread_t threadToAdd = mh_fr_threads_start_list;
		while (threadToAdd->nextThread)
		{
			threadToAdd = threadToAdd->nextThread;
		}
		if (threadToAdd->id >= MH_FREERRTOS_API_THREADS_MAX)
		{
			return threadToAdd->id;
		}
		threadToAdd->nextThread = (void*)mh_thread;
		mh_thread->id = threadToAdd->id + 1;
	}
	else
	{
		mh_fr_threads_start_list = mh_thread;
		mh_thread->id = 0;
	}

	return 0;
}
