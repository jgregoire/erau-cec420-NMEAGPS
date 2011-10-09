#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "NMEAMessage.hpp"
#include "parse.h"

int parse(NMEAMessage **message, NMEASentence sentence) {
    // chop off the first section of the comma-delimited sentence
    // and store it in a new string

    &message = 0;

    if (strcmp(sentence->type, "GPGGA") == 0)
    {
        &message = new GGA(sentence);
	return 0;
    }
    else if (strcmp(sentence->type, "GPGSV") == 0)
    {
        &message = new GSV(sentence);
	return 0;
    } 
    else
    {
    	// We didn't get a message we care about.
	return 1;
    }
} // end parse()
