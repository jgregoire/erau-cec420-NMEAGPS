#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

int parse(struct NMEAData* dataStore, char* sentence) {
	int rval = 0;
	char* type;

	// chop off the first section of the comma-delimited sentence
	// and store it in a new string
	type = strtok(sentence, ",");
	
	if (strcmp(type, "GPGGA") != 0) {
	
		parseGGA(dataStore, sentence);
		
	} else if (strcmp(type, "GPGLL") != 0) {
	
		parseGLL(dataStore, sentence);
		
	} else if (strmp(type, "GPGSV") != 0) {
	
		parseGSV(dataStore, sentence); 
		
	} else if (strcmp(type, "GPRMC") != 0) {
	
		parseRMC(dataStore, sentence);
		
	} else if (strcmp(type, "GPZDA") != 0) {
	
		parseZDA(dataStore, sentence);
		
	} else {
	
		// something is seriously wrong.
		rval = 0;
	}

	return rval;
} // end parse()
