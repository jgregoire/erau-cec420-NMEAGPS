#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

// make a macro for tokenizing, since we always do it the same way

void tokenize(char *, char *, char *, char **);

int parseGGA(struct NMEAData*, char*);

int parseGLL(struct NMEAData*, char*);

int parseGSV(struct NMEAData*, char*);

int parseRMC(struct NMEAData*, char*);

int parseZDA(struct NMEAData*, char*);

void convertLatLong(char* dest, float loc) {
    char temp[12];

    // pull out integer digits, these translate directly
    sprintf(temp, "%3.0f", loc);
    dest[0] = temp[0]; // d
    dest[1] = temp[1]; // d
    dest[2] = temp[2]; // d
    
    dest[3] = 'o';     // o
    
    loc = loc - (int) loc; // cut out integer portion
    loc *= 60;
    sprintf(temp, "%f", loc);
    dest[4] = temp[0]; // m
    dest[5] = temp[1]; // m
    dest[6] = '.';     // .
    dest[7] = temp[3]; // s
    dest[8] = temp[4]; // s
}
