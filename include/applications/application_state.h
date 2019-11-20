/*
 * application_state.h
 *
 *  Created on: Nov 19, 2019
 *      Author: marcin
 */

#ifndef MH_APPLICATION_STATE_H_
#define MH_APPLICATION_STATE_H_

/******************************************************************************
 * @brief describe application state
 *****************************************************************************/
enum MHApplicationState
{
	eASUnknown = 0,
	eASInitialized,
	eASStarted,
	eASStopped,
	eASError = 255
};

#endif /* MH_APPLICATION_STATE_H_ */
