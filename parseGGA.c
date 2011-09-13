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

// handle different units of altitude

int parseGGA(struct NMEAData *dataStore, char* sentence) {
    char token[256];
    char* cursor = 0;
    char temp[3] = "\0\0\0";
    float lat = 0.0f;
    float lon = 0.0f;
    short numSatellites = 0;
    float alt = 0.0f;
    struct tm tt;
    tt.tm_isdst = -1;
    
    ////////////////////
    //                //
    //  EXTRACT TIME  //
    //                //
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

    ////////////////////////
    //                      //
    //  EXTRACT LATITUDE  //
    //                      //
    ////////////////////////
    
    // extract lat val
    tokenize(token, sentence, ",", &cursor);
    
    if (strcmp(token, "") != 0) 
    {
	// convert latitude to float
        lat = strtof(token, NULL);
        
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
    //                       //
    //  EXTRACT LONGITUDE  //
    //                       //
    /////////////////////////
    
    // extract lon val
    tokenize(token, sentence, ",", &cursor);
    
    if (strcmp(token, "") != 0) 
    {
	// convert lon to float
        lon = strtof(token, NULL);
        
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

    ///////////////////////
    //                     //
    //  EXTRACT QUALITY  //
    //                     //
    ///////////////////////
    
    // extract quality val
    tokenize(token, sentence, ",", &cursor);
    
    // we don't care about fix quality. Carry on...
    
    //////////////////////////////
    //                            //
    //  EXTRACT NUM SATELLITES  //
    //                            //
    //////////////////////////////
    
    // extract number
    tokenize(token, sentence, ",", &cursor);
    
    if (strcmp(token, "") != 0) 
    {
	// convert to int
        numSatellites = (short) strtol(token, NULL, 10);        
    }
    else 
	return 1;
    
    ////////////////////////
    //                      //
    //  EXTRACT DILUTION  //
    //                      //
    ////////////////////////
    
    // extract dilution
    tokenize(token, sentence, ",", &cursor);
    
    // we don't care about this. Carry on...
    
    ////////////////////////
    //                      //
    //  EXTRACT ALTITUDE  //
    //                      //
    ////////////////////////
    
    // extract altitude
    tokenize(token, sentence, ",", &cursor);
    
    if (strcmp(token, "") != 0) 
    {
	// convert to float
        alt = strtof(token, NULL);

        tokenize(token, sentence, ",", &cursor);
        toupper(token[0]);

        if(token[0] == 'F')
        {
            alt *= 0.3048;
	}
        else if (token[0] == 'M')
        {;}
        else 
            return 1;
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
	dataStore->lat = lat;
	dataStore->lon = lon;
	dataStore->altitude = alt;
	dataStore->numSatellites = numSatellites;

	dataStore->date.tm_hour = tt.tm_hour;
	dataStore->date.tm_min = tt.tm_min;
	dataStore->date.tm_sec = tt.tm_sec;

	// set UTC and TAI
	dataStore->epochTime = mktime(&dataStore->date);
	dataStore->taiTime = dataStore->epochTime + 34;
       
	convertLatLong(dataStore->dmsLat, lat);
	convertLatLong(dataStore->dmsLon, lon);                

	dataStore->allDataSet |= (LATX | LONGX | SATSX | ALTX | TIMEX);
    }
    return 0;
}

