/*
 * SpecialCommands.c
 *
 *  Created on: Oct 7, 2017
 *      Author: mira
 */

#include "SpecialCommandsExecuter.h"
#define clear() printf("\033[H\033[J")

void execute_exit() {
	exit(0);
}
void execute_cd(char** parsed_command, int size) {
	if (size == 1)
		chdir(getenv("HOME"));
	else {
		int result_change_dir = chdir(parsed_command[1]);
		if (result_change_dir == -1)
			printf(KRED "ERROR :: NO SUCH DIRECTORY\n" KNRM);
	}

}
void execute_echo(char** parsed_command, int size) {
	int i;
	for (i = 1; i < size; i++) {
		printf(KMAG"%s", parsed_command[i]);
		if (i < size - 1)
			printf(" ");
	}
	printf("\n" KNRM);
}
void execute_clear() {
	clear();
}
