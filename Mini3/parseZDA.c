#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "parse.h"

/////////////
//           //
//  TO DO  //
//           //
/////////////

// minutes offset
// UTC and TAI conversions

int parseZDA(struct NMEAData *dataStore, char* sentence) {
    char token[256], temp[256], *cursor = 0;
    struct tm tt;
    tt.tm_isdst = -1;
    int timezone = 0;
    
    ////////////////////
    //                //
    //  EXTRACT TIME  //
    //                //
    ////////////////////
        
    tokenize(token, sentence, ",", &cursor); // "hhmmss.ss"
    
    // turn time into a useful value
    // get "hh" from "hhmmss.ss"
    strncpy(temp, token, 2);
    tt.tm_hour = (int) strtol(temp, NULL, 10);
    
    // get mm
    memcpy(temp, &token[2], 2);
    tt.tm_min = (int) strtol(temp, NULL, 10);
    
    // get ss (ignoring .ss)
    memcpy(temp, &token[4], 2);
    tt.tm_sec = (int) strtol(temp, NULL, 10);
    
    ////////////////////
    //                //
    //  EXTRACT DATE  //
    //                //
    ////////////////////
    
    // extract day
    tokenize(token, sentence, ",", &cursor);
    
    if (strcmp(token, "") != 0) 
    {
        tt.tm_mday = (short) strtol(token, NULL, 10);
    }
    else
	return 1;   

    // extract month
    tokenize(token, sentence, ",", &cursor);
    
    if (strcmp(token, "") != 0) 
    {
	tt.tm_mon = (short) strtol(token, NULL, 10) - 1; // tm_mon is 0 indexed
    }
    else
	return 1;
    
    // extract year
    tokenize(token, sentence, ",", &cursor);
    
    if (strcmp(token, "") != 0)
    {
        tt.tm_year = (short) strtol(token, NULL, 10) - 1900;
    }
    else
	return 1;
    
    ////////////////////////
    //                      //
    //  EXTRACT TIMEZONE  //
    //                      //
    ////////////////////////
    
    // extract timezone
    tokenize(token, sentence, ",", &cursor);
    
    if (strcmp(token, "") != 0) 
    {
	timezone = (short) strtol(token, NULL, 10);
	tt.tm_hour += timezone - dataStore->localOffset;
    }
    else
	return 1;

    if (mktime(&tt) < dataStore->epochTime)
    {
	puts("Aborting parse: Stale data");
	return 2;
    }
    else
    {
	if (mktime(&tt) > dataStore->epochTime)
	    dataStore->isDelta = 1;

	dataStore->date.tm_hour = tt.tm_hour;
	dataStore->date.tm_min = tt.tm_min;
	dataStore->date.tm_sec = tt.tm_sec;

	dataStore->date.tm_mday = tt.tm_mday;
	dataStore->date.tm_mon = tt.tm_mon;
	dataStore->date.tm_year = tt.tm_year;

	// set UTC and TAI
	dataStore->epochTime = mktime(&dataStore->date);
	dataStore->taiTime = dataStore->epochTime + 34;

	dataStore->allDataSet |= (DATEX | TIMEX);
    }
    return 0;
}










