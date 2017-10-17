/*
 * Variables.h
 *
 *  Created on: Oct 3, 2017
 *      Author: mira
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_
#define MAX_LEN 512
#include <string.h>
#include <stdlib.h>
#include "StringHelper.h"

void add_variable(char* key, char* value);
char* get_value(char* key);
void initialize_tables();

#endif /* VARIABLES_H_ */
