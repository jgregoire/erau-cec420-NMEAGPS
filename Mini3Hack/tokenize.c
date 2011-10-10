#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "parse.h"

// This function checks to see if the next value in the NMEA string is empty.
// If so, by calling strtok, we would get the wrong value (the next one non-null
// one in line). Thus, we check to make sure that the first character in the string
// isn't a comma (that would indicate null value).
void tokenize(char * dest, char* string, char* delims, char **pos)
{
    char *t = 0;
    // if the first instance of a comma is the beginning of the string...
    if (*pos != 0 && *pos[0] == ',') {
	t = malloc(1);
	t[0] = '\0';

	*pos += 1;
    
	// return an empty string
	strncpy(dest, t, 1);
	free(t);
	t = NULL;    
    } 
    else
    {
	if (*pos == 0)
	{
	    t = strtok_r(string, delims, pos);
	    // otherwise, return the expected string
	}
	else
	{
	    t = strtok_r(NULL, delims, pos);
	}
	strcpy(dest, t);
    }
}
