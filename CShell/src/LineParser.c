/*
 * LineParser.c
 *
 *  Created on: Sep 30, 2017
 *      Author: mira
 */

#include "LineParser.h"



int parse_line(char **list, char* line) {

	int line_size = strlen(line);
	int i = 0, j = 0, quote_found = 0, last_quote_index = 0, counter_list = 0;
	char last_quote = '0';
	list[counter_list] = malloc(MAX_CHAR * sizeof(char));
	LOOP: while (i < line_size) {
		if (((line[i] == '"' && !quote_found)
				|| (line[i] == '\'' && !quote_found))
				&& (i == 0 || (i > 0 && isspace(line[i - 1]))
						|| line[i - 1] == '=')) { //quote for the first time
			quote_found = 1;
			last_quote = line[i];
			last_quote_index = i;
			append(list[counter_list], line[i], j);
			j++;

		} else if (((line[i] == '"' && quote_found)
				|| (line[i] == '\'' && quote_found)) && (last_quote == line[i])
				&& ((i < line_size - 1 && isspace(line[i + 1]))
						|| i == line_size - 1)) { //quote last time
			quote_found = 0;
			last_quote = '0';
			append(list[counter_list], line[i], j);
			if (i < line_size - 1 && !isspace(line[line_size - 1])) {
				counter_list++;
				list[counter_list] = malloc(MAX_CHAR * sizeof(char));
				j = 0;
			}

		} else if (isspace(line[i]) && !quote_found) { //white space
			if (i > 0 && !isspace(line[i + 1]) && j != 0
					&& (i < line_size - 1)) {
				counter_list++;
				list[counter_list] = malloc(MAX_CHAR * sizeof(char));
				j = 0;
			}

		} else if (line[i] == '=' && i > 0 && i < line_size
				&& !isspace(line[i - 1]) && !isspace(line[i + 1])
				&& !quote_found) { // expression
			counter_list++;
			list[counter_list] = malloc(sizeof(char));
			strcpy(list[counter_list], "==");  //<=== expression flag
			if (i < line_size - 1) {
				counter_list++;
				list[counter_list] = malloc(MAX_CHAR * sizeof(char));
				j = 0;
			}
		} else { //append  character
			append(list[counter_list], line[i], j);
			j++;
		}

		i++;
	}
	if (quote_found && last_quote != '0' && last_quote_index < line_size - 1) {
		i = last_quote_index + 1;
		j = 1;
		list[counter_list][0] = last_quote;
		list[counter_list][1] = '\0';
		quote_found = 0;
		last_quote = '0';
		goto LOOP;
	}
	return counter_list + 1;
}

int parse_by_delimiter(char** list, char* line, char* delimiter) {
	int i = 0;
	char* token = malloc(sizeof(line));
	token = strtok(line, delimiter);
	while (token != NULL) {
		list[i] = token;
		token = strtok(NULL, delimiter);
		i++;
	}
	return i;
}
