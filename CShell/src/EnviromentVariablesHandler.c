/*
 * EnviromentVariablesHandler.c
 *
 *  Created on: Oct 3, 2017
 *      Author: mira
 */

#include "EnviromentVariablesHandler.h"

//returns empty string if does not exist
char* getEnv(char* env_variable) {

	char* result = getenv(env_variable);
	if (result == NULL)
		return "";
	char* value = malloc(strlen(result) + 1);
	strcpy(value, result);
	return value;

}
