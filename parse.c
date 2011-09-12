#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "parse.h"

int parse(struct NMEAData* dataStore, struct NMEAMessage * sentence) {
    // chop off the first section of the comma-delimited sentence
    // and store it in a new string
    
    dataStore->isDelta = 1;
    
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
    
    // this isn't necessarily reliably set
    dataStore->isDelta = 0;
    // We didn't get a message we care about.
    return 0;
    }
} // end parse()


void convertLatLong(char* dest, float loc) {
    char temp[13];

    // pull out integer digits, these translate directly
    sprintf(temp, "%03u", (int)loc);
    dest[0] = temp[0]; // d
    dest[1] = temp[1]; // d
    dest[2] = temp[2]; // d
    
    dest[3] = 'o';     // o
    
    loc = fabs(loc - (int) loc); // cut out integer portion
    loc *= 60;
    sprintf(temp, "%02u", (int)loc);
    dest[4] = temp[0]; // m
    dest[5] = temp[1]; // m
    dest[6] = '.';
    
    loc = (loc - (int)loc) * 100;

    sprintf(temp, "%02u", (int) loc);
    dest[7] = temp[0];
    dest[8] = temp[1];
    dest[9] = '\0';
}
