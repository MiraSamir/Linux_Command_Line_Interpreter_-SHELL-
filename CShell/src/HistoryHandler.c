/*
 * HistoryHandler.c0
 *
 *  Created on: Oct 5, 2017
 *      Author: mira
 */

#include "HistoryHandler.h"
#include <stdio.h>

char * history_file_path;

void append_to_history(char* line) {

	FILE *fp = fopen(history_file_path, "a");
	if (fp != NULL) {
		fputs(line, fp);
		fputs("\n", fp);
		fclose(fp);
	}

}
void read_history_file() {
	FILE *fp = fopen(history_file_path, "r");
	char* str = malloc(514);
	if (fp != NULL) {
		while (fgets(str, 514, fp)) {
			printf("%s", str);
		}
		fclose(fp);
	} else {
		printf("CANNOT READ HISTORY FILE\n");
	}
}
void set_history_path() {
	history_file_path = malloc(200);
	char* temp = malloc(100);
	strcpy(temp, getenv("HOME"));
	strcat(history_file_path, temp);
	free(temp);
	strcat(history_file_path, "/shell_history");

}
