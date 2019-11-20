/*
 * error_handler.h
 *
 *  Created on: Nov 8, 2019
 *      Author: marcin hujdus
 */

#ifndef MH_ERROR_HANDLER_H_
#define MH_ERROR_HANDLER_H_

/* ****************************************************************************
 * @method: Error_Handler
 * @brief:  Method used for handling errors. When task/program occur this point
 *          it will hang
 * @param:  None
 * @return: None
 * ***************************************************************************/
void Error_Handler(void);

/* ****************************************************************************
 * @method: Log_Init_Error
 * @brief:  Method used for logging init error.
 * @param:  dev_name device name
 * @param:  error_no error number
 * @return: None
 * ***************************************************************************/
void Log_Init_Error(char* dev_name, int error_no);

/* ****************************************************************************
 * @method: Log_Startup_Error
 * @brief:  Method used for logging startup error.
 * @param:  dev_name device name
 * @param:  error_no error number
 * @return: None
 * ***************************************************************************/
void Log_Startup_Error(char* dev_name, int error_no);

/* ****************************************************************************
 * @method: Log_Stop_Error
 * @brief:  Method used for logging stop error.
 * @param:  dev_name device name
 * @param:  error_no error number
 * @return: None
 * ***************************************************************************/
void Log_Stop_Error(char* dev_name, int error_no);

#endif /* MH_ERROR_HANDLER_H_ */
