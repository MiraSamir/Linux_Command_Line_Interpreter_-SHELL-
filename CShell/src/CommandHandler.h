/*
 * CommandHandler.h
 *
 *  Created on: Oct 3, 2017
 *      Author: mira
 */

#ifndef COMMANDHANDLER_H_
#define COMMANDHANDLER_H_

#include "CommandExecuter.h"
#include "Variables.h"
#include "Expressions.h"
#include "EnviromentVariablesHandler.h"
#include "ShellColors.h"
#include "StringHelper.h"

void handle_command(char** parsed_command, int size, char** file_directories);
void handle_variables(char** parsed_command, int size);
void handle_tidle(char** parsed_command, int size);
char* find_variable(char* temp);
int handle_params(char** params, int size, char** final_params);
#endif /* COMMANDHANDLER_H_ */
