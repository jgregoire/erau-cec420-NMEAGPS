#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "parse.h"

// This function checks to see if the next value in the NMEA string is empty.
// If so, by calling strtok, we would get the wrong value (the next one non-null
// one in line). Thus, we check to make sure that the first character in the string
// isn't a comma (that would indicate null value).
char* tokenize(char* string, char* delims)
{
	// if the first instance of a comma is the beginning of the string...
	if (strstr(string, ",") == string) {
	
		// return an empty string
		return "";
		
	} else {
	
		// otherwise, return the expected string
		return strtok(string, delims);
		
	} 
}
