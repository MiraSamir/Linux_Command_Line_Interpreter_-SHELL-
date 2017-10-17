/*
 * StringHelper.c
 *
 *  Created on: Oct 8, 2017
 *      Author: mira
 */

#include "StringHelper.h"

int find_last_index(char* str, char character) {
	char *chptr = strrchr(str, character);
	return chptr - str;
}

void replace_part_of_str(char* str1, char* str2, int first_index,
		int last_index) {
	char* temp1 = malloc(sizeof(char) * (first_index + 1));
	strncpy(temp1, str1, first_index);
	temp1[first_index] = '\0';
	char* temp2 = malloc(sizeof(char) * (strlen(str1) - last_index));
	strcpy(temp2, str1 + last_index + 1);
	str1[0] = '\0';
	str1 = (char *) realloc(str1,
			(strlen(temp1) + strlen(str2) + strlen(temp2) + 1));
	strcat(str1, temp1);
	strcat(str1, str2);
	strcat(str1, temp2);
	free(temp1);
	free(temp2);
}
void remove_multiple_spaces(char* str) {
	char *dst = str;
	for (; *str; ++str) {
		if (isspace(*str)) {
			do {
				if (*str == '\t')
					*str = ' ';
				++str;
			} while (isspace(*str));

			--str;
		}
		*dst++ = *str;
	}
	*dst = 0;
}
void append(char* s, char c, int len) {
	s[len] = c;
	s[len + 1] = '\0';

}

int is_quoted(char* str) { // 1 if is quoted
	return ((count_chars(str, '"') > 1) || (count_chars(str, '\'') > 1));
}

void remove_quotes(char* str) {
	int i = 0, quote_found = 0, last_quote_index = 0;
	char last_quote_found = '\0';
	while (str[i] != '\0') {

		LOOP: if ((str[i] == '"' || (str[i] == '\'')) && !quote_found) {
			quote_found = 1;
			last_quote_found = str[i];
			last_quote_index = i;
			i++;
		} else if ((str[i] == '"' || str[i] == '\'') && quote_found
				&& (last_quote_found == str[i])) { //quote last time
			quote_found = 0;
			last_quote_found = '0';
			remove_char_from_string(str, i);
			remove_char_from_string(str, last_quote_index);
			i--;
		} else {
			i++;
		}
	}
	if (quote_found) {
		i = last_quote_index + 1;
		quote_found = 0;
		goto LOOP;
	}
}

int count_chars(char* s, char c) {
	return *s == '\0' ? 0 : count_chars(s + 1, c) + (*s == c);
}

void remove_char_from_string(char* str, int index) {
	memmove(&str[index], &str[index + 1], strlen(str) - index);

}
