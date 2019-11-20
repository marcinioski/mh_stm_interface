/*
 * processor_init_stm32f7.h
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin
 */

#ifndef MH_PROCESSOR_INIT_STM32F7_H_
#define MH_PROCESSOR_INIT_STM32F7_H_

/* ****************************************************************************
 * @method: SystemClock_Config_F7
 * @brief:  initialization of processor RCC peripherals
 * @param:  None
 * @return: None
 * ***************************************************************************/
void SystemClock_Config_F7(void);

/* ****************************************************************************
 * @method: MPU_Config_F7
 * @brief:  initialization of processor MPU peripheral
 * @param:  None
 * @return: None
 * ***************************************************************************/
void MPU_Config_F7(void);

/* ****************************************************************************
 * @method: CPU_CACHE_Enable_F7
 * @brief:  initialization of processor cache
 * @param:  None
 * @return: None
 * ***************************************************************************/
void CPU_CACHE_Enable_F7(void);

#endif /* MH_PROCESSOR_INIT_PROCESSOR_INIT_STM32F7_H_ */
