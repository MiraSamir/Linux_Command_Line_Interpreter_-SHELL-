/*
 * SpecialCommands.h
 *
 *  Created on: Oct 7, 2017
 *      Author: mira
 */

#ifndef SPECIALCOMMANDSEXECUTER_H_
#define SPECIALCOMMANDSEXECUTER_H_
#include "string.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ShellColors.h"
#include "StringHelper.h"

void execute_cd(char** parsed_command, int size);
void execute_exit();
void execute_echo(char** parsed_command , int size);
void execute_clear();
#endif /* SPECIALCOMMANDSEXECUTER_H_ */
