/*
 * freertos_thread_state.h
 *
 *  Created on: Dec 8, 2019
 *      Author: marcin
 */

#ifndef FREERTOS_THREAD_STATE_H_
#define FREERTOS_THREAD_STATE_H_

/* ****************************************************************************
 * @type: MHThreadState
 * @brief: Describe the state of thread
 * ***************************************************************************/
enum MHThreadState
{
	eTHSUnknown = 0,
	eTHSInitialized,
	eTHSStarting,
	eTHSStarted,
	eTHSStopping,
	eTHSStopped,
	eTHSError = 255
};

#endif /* FREERTOS_THREAD_STATE_H_ */
