/*
 * BufferLineReader.c
 *
 *  Created on: Sep 30, 2017
 *      Author: mira
 */

#include "BufferLineReader.h"

void read_line(char *line) {


	size_t len = 514 ;
	fgets (line, len, stdin);
	size_t ln = strlen(line) - 1;
	if (line[ln] == '\n'){
		line[ln] = '\0';
	}
}
