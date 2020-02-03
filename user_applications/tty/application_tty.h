/*
 * application_tty.h
 *
 *  Created on: Jan 20, 2020
 *      Author: marcin
 */

#ifndef APPLICATION_TTY_H_
#define APPLICATION_TTY_H_

#include "mh/applications/application.h"

enum MHApplicationState app_tty_init(void* arg);

enum MHApplicationState app_tty_start(void* arg);

enum MHApplicationState app_tty_stop(void* arg);

#endif /* APPLICATION_TTY_H_ */
