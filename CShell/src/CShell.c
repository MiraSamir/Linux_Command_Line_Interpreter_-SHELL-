/*
 ============================================================================
 Name        : CShell.c
 Author      : Mira
 Version     : 0
 Copyright   : @MS
 Description : Ubuntu C shell
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include "signal.h"
#include <termios.h>
#include "FileProcessing.h"
#include "BufferLineReader.h"
#include "LineParser.h"
#include "Initializer.h"
#include "CommandHandler.h"
#include "Variables.h"
#include "LoggerHandler.h"
#include "HistoryHandler.h"
#include "ShellColors.h"
#define MAX_LINE_LEN 512

int mode; // 1 for interactive , 0 for batch

char** file_directories;
char** parsed_line_tokens;
char* parsed_line;



void exit_system() { // ctrl + d
	exit(0);
}


void initialize_signals() {
	signal(SIGCHLD, append_to_log);

	struct termios old_termios, new_termios;
	tcgetattr(0, &old_termios);
	new_termios = old_termios;
	new_termios.c_cc[VEOF] = 3;  //^c
	new_termios.c_cc[VINTR] = 4;  //^D
	tcsetattr(0, TCSANOW, &new_termios);

	signal(SIGINT, exit_system);
}

void locate_variables() {

	parsed_line = (char*) malloc(514 * sizeof(char));
	file_directories = (char**) malloc(30 * sizeof(char*));
	parsed_line_tokens = (char**) malloc(30 * sizeof(char*));
}
void freee(int size) {
	int i;
	for (i = 0; i < size; i++)
		free(parsed_line_tokens[i]);
}
void start_shell_loop() {

	for (;;) {
		if (mode == 1) {
			printf(KBLU "Shell>  " KNRM);
			read_line(parsed_line);

		} else if (mode == 0) {
			if (!is_end_of_file()) {
				read_file_line(parsed_line);
				if (parsed_line[0] != '\0')
					printf(">> %s\n", parsed_line);
			} else {
				mode = 1;
				close_file();
			}
		}
		if (strlen(parsed_line) > MAX_LINE_LEN)
			printf(KRED "ERROR :: TOO LONG COMMAND\n" KNRM);

		else {
			if (parsed_line[0] != '\0') { // not empty
				int size = parse_line(parsed_line_tokens, parsed_line);
				handle_command(parsed_line_tokens, size, file_directories);
				freee(size);
			}
		}
		if (parsed_line[0] != '\0')
			append_to_history(parsed_line);
	}
	parsed_line[0] = '\0';
}
int main(int argc, char *argv[]) {

	if (argc < 1 || argc > 2) {
		printf(KRED "ERROR :: INVALID ARGUMENTS\n" KNRM);
		return EXIT_FAILURE;
	} else if (argc == 1) { //interactive mode
		mode = 1;
	} else if (argc == 2) { // batch mode
		mode = 0;
		if (!initialize_input_file(argv[1])) {
			printf(KRED "ERROR :: INVALID FILE PATH\n" KNRM);
			return EXIT_FAILURE;
		}
	}
	initialize_signals();
	locate_variables();
	initialize_tables();
	initialize(file_directories);
	start_shell_loop();
	return EXIT_SUCCESS;
}
