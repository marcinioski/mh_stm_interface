/*
 * device.h
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin
 */

#ifndef MH_DEVICE_H_
#define MH_DEVICE_H_

#include "device_state.h"

/* ****************************************************************************
 * @param: MH_DEVICES_MAX
 * @brief: declaration of amount devices used in system
 * ***************************************************************************/
#define MH_DEVICES_MAX 3

/* ****************************************************************************
 * @param: MH_DEVICE_NAME_MAX_LEN
 * @brief: declaration of max device name len
 * ***************************************************************************/
#define MH_DEVICE_NAME_MAX_LEN 10

/* ****************************************************************************
 * @type:   mh_device_init_clb_t
 * @brief:  callback responsible for initializing device
 * @param:  arg pointer to mh_device_t
 * @return: state of device, eDSError in case of error
 * ***************************************************************************/
typedef enum MHDeviceState (*mh_device_init_clb_t)(void* arg);

/* ****************************************************************************
 * @type:   mh_device_start_clb_t
 * @brief:  callback responsible for starting device
 * @param:  arg pointer to mh_device_t
 * @return: state of device, eDSError in case of error
 * ***************************************************************************/
typedef enum MHDeviceState (*mh_device_start_clb_t)(void* arg);

/* ****************************************************************************
 * @type:   mh_device_stop_clb_t
 * @brief:  callback responsible for stopping device
 * @param:  arg pointer to mh_device_t
 * @return: state of device, eDSError in case of error
 * ***************************************************************************/
typedef enum MHDeviceState (*mh_device_stop_clb_t)(void* arg);

/* ****************************************************************************
 * @type:  mh_device
 * @brief: structure used for holding information about device
 * ***************************************************************************/
typedef struct
{
	mh_device_init_clb_t init;
	mh_device_start_clb_t start;
	mh_device_stop_clb_t stop;
	enum MHDeviceState state;
	unsigned int last_error;
	void* private_data;
	char name[MH_DEVICE_NAME_MAX_LEN];
} mh_device_t, *pmh_device_t;

/* ****************************************************************************
 * @method mh_init_startup_devices
 * @brief: method used for initializing list of devices using on startup
 * @param: None
 * @return None
 * ***************************************************************************/
void mh_init_startup_devices(void);

/* ****************************************************************************
 * @method mh_start_startup_devices
 * @brief: method used for starting list of devices using on startup
 * @param: None
 * @return None
 * ***************************************************************************/
void mh_start_startup_devices(void);

/* ****************************************************************************
 * @method mh_stop_startup_devices
 * @brief: method used for stopping list of devices using on startup
 * @param: None
 * @return None
 * ***************************************************************************/
void mh_stop_startup_devices(void);

/* ****************************************************************************
 * @method: MH_DEVICE_INIT
 * @brief: macro used for calling mh_init_startup_devices
 * ***************************************************************************/
#define MH_DEVICE_INIT(X) if (((pmh_device_t)X) &&\
							  ((pmh_device_t)X)->init) \
						  	  ((pmh_device_t)X)->state = ((pmh_device_t)X)->init((pmh_device_t)X)

/* ****************************************************************************
 * @method: MH_DEVICE_START
 * @brief: macro used for calling mh_start_startup_devices
 * ***************************************************************************/
#define MH_DEVICE_START(X) if (((pmh_device_t)X) && \
							   ((pmh_device_t)X)->start) \
							   ((pmh_device_t)X)->state = ((pmh_device_t)X)->start((pmh_device_t)X)

/* ****************************************************************************
 * @method: MH_DEVICE_STOP
 * @brief: macro used for calling mh_stop_startup_devices
 * ***************************************************************************/
#define MH_DEVICE_STOP(X) if (((pmh_device_t)X) && \
							  ((pmh_device_t)X)->stop) \
							  ((pmh_device_t)X)->state = ((pmh_device_t)X)->stop((pmh_device_t)X)

#endif /* MH_DEVICE_H_ */
