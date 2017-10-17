/*
 * HistoryHandler.h
 *
 *  Created on: Oct 5, 2017
 *      Author: mira
 */

#ifndef HISTORYHANDLER_H_
#define HISTORYHANDLER_H_
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void append_to_history(char* line);
void read_history_file();
void set_history_path();
#endif /* HISTORYHANDLER_H_ */
