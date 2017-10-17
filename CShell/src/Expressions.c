/*
 * Expressions.c
 *
 *  Created on: Oct 3, 2017
 *      Author: mira
 */
#include "Expressions.h"

// return 1 if is expression
int is_Expression(char** parsed_command, int size) {

	return (strcmp(parsed_command[0], "export") == 0
			|| (((size > 2) && (strcmp(parsed_command[1], "==") == 0))));

}

int evaluate_expression(char** expression, int size) {

	int i, last_index = -19, at_least_one_correct = 0;
	for (i = 0; i < size; i++) {

		if (i > 0 && i < (size - 1) && strcmp(expression[i], "==") == 0
				&& i > (last_index + 2) && expression[i - 1][0] != '$') {
			last_index = i;

			if (is_quoted(expression[i + 1])){} // remove double quotes before storing
				remove_quotes(expression[i + 1]);

			char* result2 = getEnv(expression[i - 1]);
			if (strcmp(result2, "") == 0)  //user value
				add_variable(expression[i - 1], expression[i + 1]);

			else { // environment variable
				char* value = malloc(sizeof(char));
				strcpy(value, expression[i - 1]);
				strcat(value, "=");
				strcat(value, expression[i + 1]);
				putenv(value);
			}
			at_least_one_correct = 1;
		}
	}
	return at_least_one_correct;
}
