#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

int parse(struct NMEAData* dataStore, struct NMEAMessage * sentence) {
	// chop off the first section of the comma-delimited sentence
	// and store it in a new string
	
	if (strcmp(sentence->type, "GPGGA") == 0) {
	
		return parseGGA(dataStore, sentence->data);
		
	} else if (strcmp(sentence->type, "GPGLL") == 0) {
	
		return parseGLL(dataStore, sentence->data);
		
	} else if (strcmp(sentence->type, "GPGSV") == 0) {
	
		return parseGSV(dataStore, sentence->data); 
		
	} else if (strcmp(sentence->type, "GPRMC") == 0) {
	
		return parseRMC(dataStore, sentence->data);
		
	} else if (strcmp(sentence->type, "GPZDA") == 0) {
	
		return parseZDA(dataStore, sentence->data);
		
	} else {
	
		// something is seriously wrong.
		return 1;
	}
} // end parse()
