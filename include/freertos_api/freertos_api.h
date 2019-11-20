/*
 * freertos_api.h
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin
 */

#ifndef MH_FREERTOS_API_H_
#define MH_FREERTOS_API_H_

#include "mh/freertos_api/freertos_thread.h"

/* ****************************************************************************
 * @param: MH_FREERRTOS_API_THREADS_MAX
 * @brief: declaration of amount of threads used during initialization of
 *         freertos kernel
 * ***************************************************************************/
#define MH_FREERRTOS_API_THREADS_MAX 5

/* ****************************************************************************
 * @method: mh_fr_start_kernel
 * @brief:  method initialize threads defined in mh_fr_threads_start_list and
 *          start them
 * @param:  None
 * @return: None
 * ***************************************************************************/
void mh_fr_start_kernel(void);

/* ****************************************************************************
 * @method: mh_fr_append_thread
 * @brief:  method appends thread to thread list
 * @param:  mh_thread thread to append
 * @return: 0 on succes positive number in otherwise
 * ***************************************************************************/
unsigned char mh_fr_append_thread(pmh_fr_thread_t mh_thread);

#endif /* MH_FREERTOS_API_H_ */
