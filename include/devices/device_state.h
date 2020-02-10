/*
 * device_state.h
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin
 */

#ifndef MH_DEVICE_STATE_H_
#define MH_DEVICE_STATE_H_

/* ****************************************************************************
 * @type: MHDeviceState
 * @brief: Describe the state of device
 * ***************************************************************************/
enum MHDeviceState
{
	eDSUnknown = 0,
	eDSInitialized,
	eDSStarted,
	eDSStopped,
	eDSPermitted,
	eDSNoData,
	eDSSuccess = 254,
	eDSError = 255
};

#endif /* MH_DEVICES_DEVICE_STATE_H_ */
