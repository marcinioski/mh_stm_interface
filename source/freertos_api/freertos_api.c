/*
 * freertos_api.c
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin
 */

#include "mh/freertos_api/freertos_api.h"
#include "mh/error_handler/error_codes.h"

/* ****************************************************************************
 * @variable: mh_fr_threads_start_list
 * @brief:    list of threads to start during free rtos setting up
 * ***************************************************************************/
static pmh_fr_thread_t mh_fr_threads_start_list;


void mh_fr_start_kernel(void)
{
#if 0
	pmh_fr_thread_t threadToRun = mh_fr_threads_start_list;
	while (threadToRun)
	{
		osThreadCreate(&threadToRun->thread, threadToRun->arg);
		threadToRun = (pmh_fr_thread_t)threadToRun->nextThread;
	}
#endif
	osKernelStart();
}

unsigned char mh_fr_start_thread(pmh_fr_thread_t thr)
{
	unsigned char result = MH_ERR_NULL_THR;

	if (thr)
	{
		osThreadCreate(&thr->thread, thr->arg);
		thr->thread_state = eTHSStarted;
		result = MH_ERR_SUCCESS;
	}

	return result;
}

unsigned char mh_fr_start_thread_list(pmh_fr_thread_node_t thrs)
{
	unsigned char result = MH_ERR_CANNOT_START_THR;
	pmh_fr_thread_node_t node = thrs;
	while (node)
	{
		if (node->thread)
		{
			if (node->thread->init)
			{
				node->thread->init(NULL);
				node->thread->thread_state = eTHSInitialized;
			}

			node->thread->thread_state = eTHSStarting;

			result = mh_fr_start_thread(node->thread);
		}
		node = node->next;
	}

	return result;
}

unsigned char mh_fr_append_thread(pmh_fr_thread_t mh_thread)
{
#if 0
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
#endif

	return 0;
}
