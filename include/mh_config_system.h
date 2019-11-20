/*
 * mh_config_system.h
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin
 */

#ifndef MH_CONFIG_SYSTEM_H_
#define MH_CONFIG_SYSTEM_H_

/* ****************************************************************************
 * @param: MH_ERROR_HANDLER_ALLOW_ASSERT
 * @brief: in case of error occuring this variable allow to call assert method
 * ***************************************************************************/
#define MH_ERROR_HANDLER_ALLOW_ASSERT 0

/* ****************************************************************************
 * @param: MH_STARTUP_ERROR_ALLOW_ASSERT
 * @brief: in case of error occuring on startup this variable allow to call
 *         assert method
 * ***************************************************************************/
#define MH_STARTUP_ERROR_ALLOW_ASSERT 0

/* ****************************************************************************
 * @param: MH_INIT_ERROR_ALLOW_ASSERT
 * @brief: in case of error occuring on init this variable allow to call
 *         assert method
 * ***************************************************************************/
#define MH_INIT_ERROR_ALLOW_ASSERT 0

/* ****************************************************************************
 * @param: MH_STOP_ERROR_ALLOW_ASSERT
 * @brief: in case of error occuring on stop this variable allow to call
 *         assert method
 * ***************************************************************************/
#define MH_STOP_ERROR_ALLOW_ASSERT 0

/* ****************************************************************************
 * @param: MH_DEBUG_LEVEL
 * @brief: defines debug level of program
 * ***************************************************************************/
#define MH_DEBUG_LEVEL 0

/* ****************************************************************************
 * @param: MH_STM_COREFX
 * @brief: defines STM core family
 * ***************************************************************************/

/* ****************************************************************************
 * @param: MH_STM_COREFX_INCLUDE
 * @brief: defines stm32fXxx.h file to include
 * ***************************************************************************/

#ifdef STM32F0
#define MH_STM_COREF0
#endif

#ifdef STM32F3
#define MH_STM_COREF3
#endif

#ifdef STM32F4
#define MH_STM_COREF4
#endif

#ifdef STM32F7
#define MH_STM_COREF7
#endif

#endif /* MH_CONFIG_SYSTEM_H_ */
