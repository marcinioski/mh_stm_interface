/*
 * application.h
 *
 *  Created on: Nov 19, 2019
 *      Author: marcin
 */

#ifndef MH_APPLICATION_H_
#define MH_APPLICATION_H_

#include "mh/applications/application_state.h"
#include "mh/freertos_api/freertos_thread.h"

/******************************************************************************
 * @type mh_application_init_clb_t
 * @brief callback responsible of application initialization
 * @param arg pointer to mh_application_t
 * @return state of application, eASError in case of error
 *****************************************************************************/
typedef enum MHApplicationState (*mh_application_init_clb_t)(void* arg);

/******************************************************************************
 * @type mh_application_start_clb_t
 * @brief callback responsible of application start, if thread is defined it
 *        will start os thread.
 * @param arg pointer to mh_application_t
 * @return state of application, eASError in case of error
 *****************************************************************************/
typedef enum MHApplicationState (*mh_application_start_clb_t)(void* arg);

/******************************************************************************
 * @type mh_application_stop_clb_t
 * @brief callback responsible of application stop, if thread is defined it
 *        will stop os thread.
 * @param arg pointer to mh_application_t
 * @return state of application, eASError in case of error
 *****************************************************************************/
typedef enum MHApplicationState (*mh_application_stop_clb_t)(void* arg);

/******************************************************************************
 * @method mh_init_startup_applications
 * @brief method use for initializing list of startup applications
 * @param None
 * @return None
 *****************************************************************************/
void mh_init_startup_applications(void);

/******************************************************************************
 * @method mh_start_startup_applications
 * @brief method use for starting list of startup applications
 * @param None
 * @return None
 *****************************************************************************/
void mh_start_startup_applications(void);

/******************************************************************************
 * @method mh_stop_startup_applications
 * @brief method use for stopping list of startup applications
 * @param None
 * @return None
 *****************************************************************************/
void mh_stop_startup_applications(void);

/******************************************************************************
 * @brief describe application which will be run in system.
 *****************************************************************************/
typedef struct
{
	char* name;
	mh_application_init_clb_t init;
	mh_application_start_clb_t start;
	mh_application_stop_clb_t stop;
	pmh_fr_thread_t thread;
	enum MHApplicationState state;
	int last_error;
} mh_application_t, *pmh_application_t;

/* ****************************************************************************
 * @method: MH_APPLICATION_INIT
 * @brief: macro used for calling mh_init_startup_applications
 * ***************************************************************************/
#define MH_APPLICATION_INIT(X) if (((pmh_application_t)X)->init) \
						  	  ((pmh_application_t)X)->state = ((pmh_application_t)X)->init((pmh_application_t)X)

/* ****************************************************************************
 * @method: MH_APPLICATION_START
 * @brief: macro used for calling mh_start_startup_applications
 * ***************************************************************************/
#define MH_APPLICATION_START(X) if (((pmh_application_t)X)->start) \
							   ((pmh_application_t)X)->state = ((pmh_application_t)X)->start((pmh_application_t)X)

/* ****************************************************************************
 * @method: MH_APPLICATION_STOP
 * @brief: macro used for calling mh_stop_startup_applications
 * ***************************************************************************/
#define MH_APPLICATION_STOP(X) if (((pmh_application_t)X)->stop) \
							   ((pmh_application_t)X)->state = ((pmh_application_t)X)->stop((pmh_application_t)X)

#endif /* MH_APPLICATION_H_ */
