#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "parse.h"

// This function checks to see if the next value in the NMEA string is empty.
// If so, by calling strtok, we would get the wrong value (the next one non-null
// one in line). Thus, we check to make sure that the first character in the string
// isn't a comma (that would indicate null value).
void tokenize(char * dest, char* string, char* delims)
{
    // if the first instance of a comma is the beginning of the string...
    if (strstr(string, ",") == string) {
	char * t = malloc(1);
	t = "";

	// return an empty string
	strncpy(dest, t, 1);
		
    } else {
	
	char* t = strtok(string, delims);
	// otherwise, return the expected string
	strcpy(dest, t);
		
    } 
}
