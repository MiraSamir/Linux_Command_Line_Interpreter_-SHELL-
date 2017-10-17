/*
 * CommandExecuter.h
 *
 *  Created on: Oct 3, 2017
 *      Author: mira
 */

#ifndef COMMANDEXECUTER_H_
#define COMMANDEXECUTER_H_

#include "string.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "Variables.h"
#include "HistoryHandler.h"
#include "LineParser.h"
#include <stdio.h>

#include "ShellColors.h"
#include "SpecialCommandsExecuter.h"

void execute_command(char** parsed_command, int size, char** file_directories);
char* find_path(char** parsed_command, int size, char** file_directories);
int check_background_task(char* string, int len);
void call_execv(char* path, char** params);

#endif /* COMMANDEXECUTER_H_ */
