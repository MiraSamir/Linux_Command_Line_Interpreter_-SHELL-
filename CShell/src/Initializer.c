/*
 * Initializer.c
 *
 *  Created on: Sep 30, 2017
 *      Author: mira
 */

#include "Initializer.h"

char* default_path;

void initialize(char** file_names) {

	chdir(getenv("HOME"));
	default_path = malloc(1024 * sizeof(char));
	strcpy(default_path, getenv("PATH"));
	fill_directories_name(file_names);
	set_history_path();
	set_logger_path();

}

void fill_directories_name(char** file_names) {
	char* path = malloc(1024);
	strcpy(path, default_path);
	parse_by_delimiter(file_names, path, ":");
}
