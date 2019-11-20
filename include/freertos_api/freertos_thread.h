/*
 * freertos_thread.h
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin
 */

#ifndef MH_FREERTOS_THREAD_H_
#define MH_FREERTOS_THREAD_H_

#include "cmsis_os.h"

/* ****************************************************************************
 * @type:  mh_fr_thread_clb_t
 * @brief: declaration of free rtos callback thread
 * ***************************************************************************/
typedef void (*mh_fr_thread_clb_t)(void* arg);

/* ****************************************************************************
 * @type:  mh_fr_thread_t
 * @brief: definition of structure which stores freertos thread
 * ***************************************************************************/
typedef struct
{
	osThreadDef_t thread;
	void* arg;
	void* nextThread;
	unsigned char id;
} mh_fr_thread_t, *pmh_fr_thread_t;

#endif /* MH_FREERTOS_THREAD_H_ */
