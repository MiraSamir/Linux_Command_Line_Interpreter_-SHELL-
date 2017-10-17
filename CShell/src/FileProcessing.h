

#ifndef FILE_PROCESSING_H_   /* Include guard */
#define FILE_PROCESSING_H_
#include <stdio.h>

int initialize_input_file(char* path);
void read_file_line(char* line);
int is_end_of_file();
void close_file();

#endif
