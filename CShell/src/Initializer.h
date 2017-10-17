/*
 * Initializer.h
 *
 *  Created on: Sep 30, 2017
 *      Author: mira
 */

#ifndef INITIALIZER_H_
#define INITIALIZER_H_
#include "LineParser.h"
#include "HistoryHandler.h"
#include "LoggerHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void initialize(char** file_names);
void fill_directories_name(char** file_names);


#endif /* INITIALIZER_H_ */
