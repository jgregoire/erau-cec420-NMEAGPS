#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "parse.h"

// Carole Fountain //

int parseRMC(struct NMEAData *dataStore, char* sentence) {
    char token[256], *cursor = 0;
	char temp[3];
    float lat = 0;
    float lon = 0;
	int day = 0;
	int month = 0;
	int year = 0;

    //////////////////////////////
    //				            //
    //  Extract UTC time        //
    //				            //
    //////////////////////////////
	
	tokenize(token, sentence, ",", &cursor); // "hhmmss.ss"
	
	// turn time into a useful value
	// get "hh" from "hhmmss.ss"
	strncpy(temp, token, 2);
	dataStore->date.tm_hour = (int) strtol(temp, NULL, 10);
	
	// get mm
	memcpy(temp, &token[2], 2);
	dataStore->date.tm_min = (int) strtol(temp, NULL, 10);
	
	// get ss (ignoring .ss)
	memcpy(temp, &token[4], 2);
	dataStore->date.tm_sec = (int) strtol(temp, NULL, 10);
	
	// set UTC and TAI
	dataStore->epochTime = mktime(&dataStore->date);	
	
	dataStore->date.tm_sec += 34;
	dataStore->taiTime = mktime(&dataStore->date);
	
	
    //////////////////////
    //			        //
    //  Extract Status  //
    //			        //
    //////////////////////
	
    // extract status
    tokenize(token, sentence, ",", &cursor);
 
    // Don't care move on...
    
    ////////////////////////
    //                    //
    //  Extract Latitude  //
    //			          //
    ////////////////////////
	
    // extract latitude
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) {
	// convert latitude to float
	lat = strtof(token, NULL);
		
	// extract N/S val
	tokenize(token, sentence, ",", &cursor);
		
	// if South, make latitude negative
	if (toupper(token[0]) == 'S') 
	{
	    lat *= -1;
       	}
		
	dataStore->lat = lat;
    }
	
    ////////////////////////
    //				      //
    //  Extract Longitude //
    //				      //
    ////////////////////////
	
    // extract lon val
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) {
	// convert lon to float
	lon = strtof(token, NULL);
		
	// extract E/W val
	tokenize(token, sentence, ",", &cursor);
		
	// if West, make lon negative
	if (toupper(token[0]) == 'W') 
	{
	    lon *= -1;
	}
		
	dataStore->lon = lon;
    }
	
    ////////////////////////////////
    //					          //
    //  Extract Speed over ground //
    //				   	          //
    ////////////////////////////////    
	
    // extract speed
    tokenize(token, sentence, ",", &cursor);
	
    //  don't care move on...
 
	
    ///////////////////////////////////
    //					             //
    //  Extract angle in degrees     //
    //					             //
    ///////////////////////////////////
	
    // extract angle
    tokenize(token, sentence, ",", &cursor);
	
    // don't care move on...
	
    ///////////////////////////////////
    //					             //
    //  Extract date                 //
    //					             //
    ///////////////////////////////////

	    // extract day
    tokenize(token, sentence, ",", &cursor); //ddmmyy
	
	// assign day
    if (strcmp(token, "") != 0) {
		
		strncpy(temp, token, 2);
		day = (int) strtol(temp, NULL, 10);
		dataStore->date.tm_mday = day;
		
    }
	
	// assign month
    if (strcmp(token, "") != 0) {
	
		memcpy(temp, &token[2], 2);
		month = (int) strtol(temp, NULL, 10);
		dataStore->date.tm_mon = month;
		
    }
	
	// assign year
    if (strcmp(token, "") != 0) {
		
		memcpy(temp, &token[4], 2);
		year = (int) strtol(temp, NULL, 10);
		dataStore->date.tm_year = year + 100;
		
    }
	
    ///////////////////////////////////
    //					             //
    //  Extract magnetic variation   //
    //					             //
    ///////////////////////////////////
	
    // extract magnetic variation
    tokenize(token, sentence, ",", &cursor);
	
    // don't care ending...	
	
    return 0;
}
