#include "main.h"
#include "parse.h"

int parseGLL(struct NMEAData *dataStore, char* sentence) {
    char token[256], temp[256], *cursor = 0;
    char dmsLat[16]; // (dddommm’sss.ss”\0)
    char dmsLon[16]; // Same as above.
    float lat, lon;
    struct tm tt;
    tt.tm_isdst = -1;

    ////////////////////////
    //                    //
    //  EXTRACT LATITUDE  //
    //                    //
    ////////////////////////
    
    // extract lat val
    tokenize(token, sentence, ",", &cursor);
    
    if (strcmp(token, "") != 0) 
    {
        // convert latitude to float
        lat = strtof(token, NULL);
        convertLat(dmsLat, token);
        
        // extract N/S val
        tokenize(token, sentence, ",", &cursor);
        
        // if South, make latitude negative
        toupper(token[0]);
        if (strcmp(token, "S") == 0) 
	{
	    lat *= -1;
	}
    }
    else
	return 1;
    
    /////////////////////////
    //                     //
    //  EXTRACT LONGITUDE  //
    //                     //
    /////////////////////////
    
    // extract lon val
    tokenize(token, sentence, ",", &cursor);
    
    if (strcmp(token, "") != 0) 
    {
        // convert lon to float
        lon = strtof(token, NULL);
        convertLon(dmsLon, token);
        
        // extract E/W val
        tokenize(token, sentence, ",", &cursor);
        
        // if West, make lon negative
        toupper(token[0]);
        if (strcmp(token, "W") == 0) 
	{
	    lon *= -1;
	}
    }
    else
	return 1;
    
    ////////////////////
    //                  //
    //  EXTRACT TIME  //
    //                  //
    ////////////////////
    
    tokenize(token, sentence, ",", &cursor); // "hhmmss.ss"
    
    // turn time into a useful value
    // get "hh" from "hhmmss.ss"
    strncpy(temp, token, 2);
    tt.tm_hour = (int) strtol(temp, NULL, 10) - dataStore->localOffset;
    
    // get mm
    memcpy(temp, &token[2], 2);
    tt.tm_min = (int) strtol(temp, NULL, 10);
    
    // get ss (ignoring .ss)
    memcpy(temp, &token[4], 2);
    tt.tm_sec = (int) strtol(temp, NULL, 10);
    
    tt.tm_mday = dataStore->date.tm_mday;
    tt.tm_mon = dataStore->date.tm_mon;
    tt.tm_year = dataStore->date.tm_year;

    //////////////////////
    //                  //
    //  EXTRACT STATUS  //
    //                  //
    //////////////////////
    
    tokenize(token, sentence, ",", &cursor);
    
    // I don't think we care about status?

    if (mktime(&tt) < dataStore->epochTime)
    {
	puts("Aborting parse: Stale data");
	return 2;
    }
    else
    {
	if (mktime(&tt) > dataStore->epochTime)
	    dataStore->isDelta = 1;

        dataStore->lon = lon;
        dataStore->lat = lat;

	dataStore->date.tm_hour = tt.tm_hour;
	dataStore->date.tm_min = tt.tm_min;
	dataStore->date.tm_sec = tt.tm_sec;

	dataStore->date.tm_mday = tt.tm_mday;
	dataStore->date.tm_mon = tt.tm_mon;
	dataStore->date.tm_year = tt.tm_year;

	// set UTC and TAI
	dataStore->epochTime = mktime(&dataStore->date);
	dataStore->taiTime = dataStore->epochTime + 34;

	strcpy(dataStore->dmsLat, dmsLat);
	strcpy(dataStore->dmsLon, dmsLon);   

	dataStore->allDataSet |= (LATX | LONGX | TIMEX);
    }

    return 0;
}
