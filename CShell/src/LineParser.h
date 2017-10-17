/*
 * LineParser.h
 *
 *  Created on: Sep 30, 2017
 *      Author: mira
 */

#ifndef LINEPARSER_H_
#define LINEPARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "StringHelper.h"

#define MAX_CHAR 508


int parse_line(char** list , char* line);
int parse_by_delimiter(char** list , char* line , char* delimiter);

#endif /* LINEPARSER_H_ */
