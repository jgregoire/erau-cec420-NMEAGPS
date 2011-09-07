#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "parse.h"

/////////////
//		   //
//  TO DO  //
//		   //
/////////////

// minutes offset
// UTC and TAI conversions

int parseZDA(struct NMEAData *dataStore, char* sentence) {
    char token[256], temp[256], *cursor = 0;
    int day = 0;
    int month = 0;
    int year = 0;
    int timezone = 0;
	
    ////////////////////
    //		      //
    //  EXTRACT TIME  //
    //		      //
    ////////////////////
		
    tokenize(token, sentence, ",", &cursor); // "hhmmss.ss"
	
    // turn time into a useful value
    // get "hh" from "hhmmss.ss"
    strncpy(temp, token, 2);
    dataStore->date.tm_hour = (int) strtol(temp, NULL, 10) - 1;
	
    // get mm
    memcpy(temp, &token[2], 2);
    dataStore->date.tm_min = (int) strtol(temp, NULL, 10) - 1;
	
    // get ss (ignoring .ss)
    memcpy(temp, &token[4], 2);
    dataStore->date.tm_sec = (int) strtol(temp, NULL, 10) - 1;
	
		
    ////////////////////
    //		      //
    //  EXTRACT DATE  //
    //		      //
    ////////////////////
	
    // extract day
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) {
	
	day = (short) strtol(token, NULL, 10);
	dataStore->date.tm_mday = day - 1;
		
    }
	
    // extract month
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) {
	
	month = (short) strtol(token, NULL, 10);
	dataStore->date.tm_mon = month - 1;
	
    }
	
    // extract year
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) {
	
	year = (short) strtol(token, NULL, 10);
	dataStore->date.tm_year = year - 1900;
	
    }
	
    ////////////////////////
    //					  //
    //  EXTRACT TIMEZONE  //
    //					  //
    ////////////////////////
	
    // extract timezone
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) {
	
	timezone = (short) strtol(token, NULL, 10);
		
	// uncomment next line to convert UTC to local time:
	//dataStore->date.tm_hour += timezone;
	
    }
	
    //////////////////////////////
    //							//
    //  EXTRACT MINUTES OFFSET  //
    //							//
    //////////////////////////////
	
    tokenize(token, sentence, ",", &cursor);
	
    // do shit
	
    ////////////////////////////
    //						  //
    //  GENERATE UTC and TAI  //
    //						  //
    ////////////////////////////
	
    // do shit
    return 0;
}










