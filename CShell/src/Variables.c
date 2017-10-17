/*
 * Variables.c
 *
 *  Created on: Oct 3, 2017
 *      Author: mira
 */

#include "Variables.h"

char** user_keys;
char** user_values;
int user_defined_variables_counter;

void initialize_tables() {

	user_keys = (char**) malloc(MAX_LEN * sizeof(char*));
	user_values = (char**) malloc(MAX_LEN * sizeof(char*));
	user_defined_variables_counter = 0;
}
void add_variable(char* key, char* value) {

	int index, flag = 1;
	//remove_multiple_spaces(value);
	for (index = 0; index < user_defined_variables_counter && flag; index++) {
		if (strcmp(user_keys[index], key) == 0) { //override
			flag = 0;
			user_values[index] = realloc(user_values[index], strlen(value));
			strcpy(user_values[index], value);
		}
	}

	if (flag) {
		user_keys[user_defined_variables_counter] = (char*) malloc(strlen(key));
		user_values[user_defined_variables_counter] = (char*) malloc(
				strlen(value));
		strcpy(user_keys[user_defined_variables_counter], key);
		strcpy(user_values[user_defined_variables_counter], value);
		user_defined_variables_counter++;
	}

}
char* get_value(char* key) {
	int index;
	for (index = 0; index < user_defined_variables_counter; index++) {
		if (strcmp(user_keys[index], key) == 0) {
			return user_values[index];
		}
	}
	return ""; //empty string
}

