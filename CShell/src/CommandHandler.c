/*
 * CommandHandler.c
 *
 *  Created on: Oct 3, 2017
 *      Author: mira
 */

#include "CommandHandler.h"

void handle_command(char** parsed_command, int size, char** file_directories) {

	if (parsed_command[0][0] == '#') //comment line
		return;
	handle_variables(parsed_command, size); // replace $variable by it's value
	handle_tidle(parsed_command, size);
	if (is_Expression(parsed_command, size)) { // store user , enviroment variables in table

		int result = evaluate_expression(parsed_command, size);
		if (!result)
			printf(KRED "ERROR:: INVALID EXPRESSION\n" KNRM);

	} else { // execute commands
		char** final_params = malloc(sizeof(char*) * (size + 20));
		int new_size = handle_params(parsed_command, size, final_params);
		execute_command(final_params, new_size, file_directories);
	}

}
//check user defined and environment variables
void handle_variables(char** parsed_command, int size) {
	int i, j, z, val;
	for (i = 0; i < size; i++) {
		j = 0;
		while (j < strlen(parsed_command[i])) {  //j++

			if (parsed_command[i][j] == '$'
					&& ((j > 0 && parsed_command[i][j - 1] != '\\') || j == 0)) {
				z = j; //first occurrence
				j++;
				while ((j < strlen(parsed_command[i]))
						&& isalpha(parsed_command[i][j]))
					j++;
				j--;
				val = j - z + 1;
				char *temp = malloc((sizeof(char) * val));
				strncpy(temp, (parsed_command[i]) + z + 1, val - 1);
				temp[val - 1] = '\0';
				char * result = find_variable(temp);
				replace_part_of_str(parsed_command[i], result, z, j);
				j = z + strlen(result);
				free(temp);
			} else if (parsed_command[i][j] == '$'
					&& (j > 0 && parsed_command[i][j - 1] == '\\')) {
				replace_part_of_str(parsed_command[i], "", j - 1, j - 1);
				j++;
			} else
				j++;

		}
	}

}
char* find_variable(char* key) {
	char* result;
	char* result1 = get_value(key);

	if (strcmp(result1, "") == 0)  //not user_defined_variable
		result = getEnv(key);
	else
		result = result1;
	return result;
}

int handle_params(char** params, int size, char** final_params) {
	int i, j, length, counter = 0;
	for (i = 0; i < size; i++) {

		if (is_quoted(params[i])) {
			remove_quotes(params[i]);
			final_params[counter] = params[i];
			counter++;
		} else {
			char** temp = malloc((size + 20) * sizeof(char*));
			length = parse_by_delimiter(temp, params[i], " \t");
			for (j = 0; j < length; j++) {
				final_params[counter] = temp[j];
				counter++;
			}
			free(temp);
		}
	}
	final_params[counter] = NULL;
	return counter;
}
void handle_tidle(char** parsed_command, int size) {
	char *home_env = getenv("HOME");
	for (int t = 0; t < size; t++) {
		int si = strlen(parsed_command[t]);
		if ((parsed_command[t][0] == '~' && si == 1)) {  // ~
			strcpy(parsed_command[t], home_env);
		} else if (si > 1 && parsed_command[t][0] == '~'
				&& parsed_command[t][1] == '/') {  // ~/blabla
			replace_part_of_str(parsed_command[t], home_env, 0, 0);

		} else if (si > 1 && parsed_command[t][0] == '~') { //~username
			char* temp = "/home/";
			replace_part_of_str(parsed_command[1], temp, 0, 0);
		}
	}
}

