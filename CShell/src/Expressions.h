/*
 * Expressions.h
 *
 *  Created on: Oct 3, 2017
 *      Author: mira
 */

#ifndef EXPRESSIONS_H_
#define EXPRESSIONS_H_


#include <stdio.h>
#include <string.h>
#include "Variables.h"
#include "EnviromentVariablesHandler.h"
int is_Expression(char** parsed_command , int size);
int evaluate_expression(char** expression , int size);

#endif /* EXPRESSIONS_H_ */
