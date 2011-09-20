#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    
	// We didn't get a message we care about.
	return 1;
    }
} // end parse()


void convertLon(char* dest, char* temp) {
    dest[0] = temp[0]; // d
    dest[1] = temp[1]; // d
    dest[2] = temp[2]; // d
    
    dest[3] = 'o';     // o

    dest[4] = temp[3]; // m
    dest[5] = temp[4]; // m
    dest[6] = '.';

    dest[7] = temp[6];
    dest[8] = temp[7];
    dest[9] = temp[8];
    dest[10] = '\0';
}

void convertLat(char* dest, char* temp) {
    dest[0] = '0';     // d
    dest[1] = temp[0]; // d
    dest[2] = temp[1]; // d
    
    dest[3] = 'o';     // o

    dest[4] = temp[2]; // m
    dest[5] = temp[3]; // m
    dest[6] = '.';     // .
    
    dest[7] = temp[5]; // s
    dest[8] = temp[6]; // s
    dest[9] = temp[7]; // s
    dest[10] = '\0';
}
