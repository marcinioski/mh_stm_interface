/*
 * freertos_thread.h
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin
 */

#ifndef MH_FREERTOS_THREAD_H_
#define MH_FREERTOS_THREAD_H_

#include "cmsis_os.h"
#include "freertos_thread_state.h"

/* ****************************************************************************
 * @type:  mh_fr_thread_clb_t
 * @brief: declaration of free rtos callback thread
 * ***************************************************************************/
typedef void (*mh_fr_thread_clb_t)(void* arg);

/******************************************************************************
 * @type mh_fr_thread_init_clb_t
 * @brief declaration of initialization method for the thread
 * @param arg - input argument for the thread
 *****************************************************************************/
typedef void (*mh_fr_thread_init_clb_t)(void* arg);

/* ****************************************************************************
 * @type:  mh_fr_thread_t
 * @brief: definition of structure which stores freertos thread
 * ***************************************************************************/
typedef struct
{
	osThreadDef_t thread;
	mh_fr_thread_init_clb_t init;
	void* arg;
	unsigned char id;
	enum MHThreadState thread_state;
} mh_fr_thread_t, *pmh_fr_thread_t;

/******************************************************************************
 * @type mh_fr_thread_node
 * @brief list used to store list of application threads
 *****************************************************************************/
typedef struct mh_fr_thread_node
{
	pmh_fr_thread_t thread;
	struct mh_fr_thread_node* next;
} mh_fr_thread_node_t, *pmh_fr_thread_node_t;

/******************************************************************************
 * @type UNKNOWN_THREAD
 * @brief
 *****************************************************************************/
#define UNKNOWN_THREAD NULL

#endif /* MH_FREERTOS_THREAD_H_ */
