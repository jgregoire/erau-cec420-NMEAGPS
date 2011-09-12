#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "parse.h"

// Carole Fountain //

int parseRMC(struct NMEAData *dataStore, char* sentence) {
    char token[256], *cursor = 0;
    char temp[3] = "\0\0\0";
    float lat = 0;
    float lon = 0;
    struct tm t_time;
    t_time.tm_isdst = -1;
 
    //////////////////////////////
    //                          //
    //  Extract UTC time        //
    //                          //
    //////////////////////////////
    
    tokenize(token, sentence, ",", &cursor); // "hhmmss.ss"
    
    // turn time into a useful value
    // get "hh" from "hhmmss.ss"
    strncpy(temp, token, 2);
    t_time.tm_hour = (int) strtol(temp, NULL, 10) - dataStore->localOffset;

    // get mm
    memcpy(temp, &token[2], 2);
    t_time.tm_min = (int) strtol(temp, NULL, 10);

    // get ss (ignoring .ss)
    memcpy(temp, &token[4], 2);
    t_time.tm_sec = (int) strtol(temp, NULL, 10);

    //////////////////////
    //                  //
    //  Extract Status  //
    //                  //
    //////////////////////
    
    // extract status
    tokenize(token, sentence, ",", &cursor);
 
    // Don't care move on...
    
    ////////////////////////
    //                    //
    //  Extract Latitude  //
    //                    //
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
    }
    else
	return 1;
    
    ////////////////////////
    //                      //
    //  Extract Longitude //
    //                      //
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
    }
    else
	return 1;
    
    ////////////////////////////////
    //                              //
    //  Extract Speed over ground //
    //                                 //
    ////////////////////////////////    
    
    // extract speed
    tokenize(token, sentence, ",", &cursor);
    
    //  don't care move on...

    ///////////////////////////////////
    //                                 //
    //  Extract angle in degrees     //
    //                                 //
    ///////////////////////////////////
    
    // extract angle
    tokenize(token, sentence, ",", &cursor);
    
    // don't care move on...
    
    ///////////////////////////////////
    //                                 //
    //  Extract date                 //
    //                                 //
    ///////////////////////////////////

    // extract day
    tokenize(token, sentence, ",", &cursor); //ddmmyy

    // assign day
    if (strcmp(token, "") != 0)
    {    
        strncpy(temp, token, 2);
        t_time.tm_mday = (int) strtol(temp, NULL, 10);        
    }
    else
	return 1;
    
    // assign month
    if (strcmp(token, "") != 0)
    {
	memcpy(temp, &token[2], 2);
        t_time.tm_mon = (int) strtol(temp, NULL, 10) - 1; // tm_mon is 0 indexed
    }
    else
	return 1;
    
    // assign year
    if (strcmp(token, "") != 0)
    {
        memcpy(temp, &token[4], 2);
        t_time.tm_year = (int) strtol(temp, NULL, 10) + 100;
    }
    else
	return 1;

    ///////////////////////////////////
    //                                 //
    //  Extract magnetic variation   //
    //                                 //
    ///////////////////////////////////
    
    // extract magnetic variation
    tokenize(token, sentence, ",", &cursor);
    
    // don't care ending...    
    

    if (mktime(&t_time) < dataStore->epochTime)
    {
	puts("Aborting parse: Stale data");
	return 2;
    }
    else
    {
	dataStore->lat = lat;
	dataStore->lon = lon;

	dataStore->date.tm_hour = t_time.tm_hour;
	dataStore->date.tm_min = t_time.tm_min;
	dataStore->date.tm_sec = t_time.tm_sec;

	dataStore->date.tm_mday = t_time.tm_mday;
	dataStore->date.tm_mon = t_time.tm_mon;
	dataStore->date.tm_year = t_time.tm_year;

	// set UTC and TAI
	dataStore->epochTime = mktime(&dataStore->date);
	dataStore->taiTime = dataStore->epochTime + 34;

	convertLatLong(dataStore->dmsLat, lat);
	convertLatLong(dataStore->dmsLon, lon);   

	dataStore->allDataSet |= (LATX | LONGX | TIMEX | DATEX);
    }  
    return 0;
}
