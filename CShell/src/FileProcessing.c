/*
 * FileProcessing.c
 *
 *  Created on: Sep 30, 2017
 *      Author: mira
 */
#include "FileProcessing.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

FILE * file;
size_t len = 514;

int initialize_input_file(char* path) {
	file = fopen(path, "r");

	if (file) {
		return 1; //true
	} else {
		return 0; //does not exist
	}

}
void read_file_line(char *line) {

	fgets(line, len, file);
	size_t ln = strlen(line) - 1;
	if (line[ln] == '\n')
		line[ln] = '\0';

}
int is_end_of_file() {
	int res;
	long currentOffset = ftell(file);

	fseek(file, 0, SEEK_END);

	if (currentOffset >= ftell(file))
		res = 1;
	else
		res = 0;

	fseek(file, currentOffset, SEEK_SET);

	return res;
}
void close_file() {
	fclose(file);
}
