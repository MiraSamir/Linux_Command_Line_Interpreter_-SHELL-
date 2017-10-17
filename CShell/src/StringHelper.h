/*
 * StringHelper.h
 *
 *  Created on: Oct 8, 2017
 *      Author: mira
 */

#ifndef STRINGHELPER_H_
#define STRINGHELPER_H_

#include "string.h"
#include <stdlib.h>
#include <ctype.h>

int find_last_index(char* str, char character);
void replace_part_of_str(char* str1, char* str2, int first_index,
		int last_index);
void remove_multiple_spaces(char* str);
void append(char* s, char c, int len);
int is_quoted(char* str);
void remove_quotes(char* str);
int count_chars(char* s, char c);
void remove_char_from_string(char* str, int index);
#endif /* STRINGHELPER_H_ */
