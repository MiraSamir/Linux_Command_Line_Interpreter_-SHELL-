/*
 * LoggerHandler.c
 *
 *  Created on: Oct 6, 2017
 *      Author: mira
 */

#include "LoggerHandler.h"

char * logger_file_path;

void append_to_log() {
	pid_t pid;
	pid = wait(NULL);

	FILE *fp = fopen(logger_file_path, "a");
	if (fp != NULL) {
		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);

		fputs(asctime(timeinfo), fp);
		fputs(" : ~~ Child process was terminated~~ ", fp);
		if (pid != -1) {
			char * pidd = malloc(20);
			sprintf(pidd, "%d", pid);
			fputs("[", fp);
			fputs(pidd, fp);
			fputs("]", fp);
			free(pidd);
		}
		fputs("\n", fp);
		fclose(fp);
	}
}
void set_logger_path() {
	logger_file_path = malloc(200);
	char* temp = malloc(100);
	strcpy(temp, getenv("HOME"));
	strcat(logger_file_path, temp);
	free(temp);
	strcat(logger_file_path, "/shell_logger");
}
