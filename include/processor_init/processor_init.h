/*
 * processor_init.h
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin
 */

#ifndef MH_PROCESSOR_INIT_H_
#define MH_PROCESSOR_INIT_H_

#include "mh/mh_config_system.h"

#ifdef MH_STM_COREF0
#include "stm32f0xx.h"
#include "processor_init_stm32f0.h"
#define SystemClock_Config SystemClock_Config_F0
#define MPU_Config ;
#define CPU_CACHE_Enable ;
#endif

#ifdef MH_STM_COREF3
#include "stm32f3xx.h"
#include "processor_init_stm32f3.h"
#define SystemClock_Config SystemClock_Config_F3
#define MPU_Config ;
#define CPU_CACHE_Enable ;
#endif

#ifdef MH_STM_COREF4
#include "stm32f4xx.h"
#include "processor_init_stm32f4.h"
#define SystemClock_Config SystemClock_Config_F4
#define MPU_Config	MPU_Config_F4
#define CPU_CACHE_Enable CPU_CACHE_Enable_F4
#endif

#ifdef MH_STM_COREF7
#include "stm32f7xx.h"
#include "processor_init_stm32f7.h"
#define SystemClock_Config SystemClock_Config_F7
#define MPU_Config MPU_Config_F7
#define CPU_CACHE_Enable CPU_CACHE_Enable_F7
#endif

#endif /* MH_PROCESSOR_INIT_PROCESSOR_INIT_H_ */
