/*
 * CommandExecuter.c
 *
 *  Created on: Oct 3, 2017
 *      Author: Mira
 */

#include "CommandExecuter.h"

extern char* default_path;
int pid, background, length;

void execute_command(char** parsed_command, int size, char** file_directories) {

	if (strcmp(parsed_command[0], "exit") == 0)
		execute_exit();
	else if (strcmp(parsed_command[0], "clear") == 0)
		execute_clear();
	else if (strcmp(parsed_command[0], "cd") == 0)
		execute_cd(parsed_command, size);
	else {
		length = strlen(parsed_command[size - 1]);
		background = check_background_task(parsed_command[size - 1], length);
		pid = fork();
		if (pid == 0) { //child

			if (background == 1)
				parsed_command[size - 1] = NULL;

			else if (background == 2)
				parsed_command[size - 1][length - 1] = '\0';

			parsed_command[size] = NULL;
			if (strcmp(parsed_command[0], "history") == 0) {
				read_history_file();
				exit(0);
			} else if (strcmp(parsed_command[0], "echo") == 0
					|| strcmp(parsed_command[0], "printf") == 0) {
				execute_echo(parsed_command, size);
				exit(0);
			} else {
				char* actual_path = find_path(parsed_command, size,
						file_directories);

				if (actual_path == NULL)
					printf(KRED "ERROR :: UNDEFINED COMMAND\n" KNRM);
				else
					call_execv(actual_path, parsed_command);

			}
		} else { //parent
			if (!background)
				waitpid(pid, NULL, 0);
			else
				printf("[%d]\n", pid);
		}
	}
}

int check_background_task(char* string, int len) { // 1 if background

	if (strcmp(string, "&") == 0)
		return 1;
	if (string[len - 1] == '&')
		return 2;
	return 0;
}

char* find_path(char** parsed_command, int size, char** file_directories) {
	char *value = getenv("PATH");
	char* path = NULL;
	if (strcmp(value, default_path) == 0) { //default
		int i = 0, found = 0;
		while ((file_directories[i] != NULL) && (file_directories[i][0] == '/')
				&& (!found)) {
			char* temp = malloc(512 * sizeof(char));
			strcpy(temp, file_directories[i]);
			if (access(parsed_command[0], F_OK) != -1) {
				path = parsed_command[0];
				found = 1;
			} else {
				char separator[512];
				strcpy(separator, "/");
				if (access(strcat(temp, strcat(separator, parsed_command[0])),
				F_OK) != -1) {
					path = temp;
					found = 1;
				}
				separator[0] = '\0';
			}
			i++;
		}
	} else { //user defined path
		char separator[512];
		strcpy(separator, "/");
		strcat(value, strcat(separator, parsed_command[0]));
		if (access(value, F_OK) != -1)
			path = value;
	}
	return path;
}

void call_execv(char* path, char** params) {

	if (execv(path, params) == -1) {
		perror("Error");
		exit(0);
	}
}

