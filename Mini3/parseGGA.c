#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "parse.h"


int parseGGA(struct NMEAData *dataStore, char* sentence) {
    char token[256];
    char* cursor = 0;
    char temp[3] = "\0\0\0";
    char dmsLat[16]; // (dddommm’sss.ss”\0)
    char dmsLon[16]; // Same as above.
    float lat = 0.0f;
    float lon = 0.0f;
    short numSatellites = 0;
    float alt = 0.0f;
    struct Time time;
    
    ////////////////////
    //                //
    //  EXTRACT TIME  //
    //                //
    ////////////////////
    
    tokenize(token, sentence, ",", &cursor); // "hhmmss.ss"
    
    // turn time into a useful value
    // get "hh" from "hhmmss.ss"
    strncpy(temp, token, 2);
    time.hour = (int) strtol(temp, NULL, 10) - dataStore->localOffset;
    
    // get mm
    memcpy(temp, &token[2], 2);
    time.mins = (int) strtol(temp, NULL, 10);
    
    // get ss (ignoring .ss)
    memcpy(temp, &token[4], 2);
    time.sec = (int) strtol(temp, NULL, 10);
    /* obsolete for Arduino
    tt.tm_mday = dataStore->date.tm_mday;
    tt.tm_mon = dataStore->date.tm_mon;
    tt.tm_year = dataStore->date.tm_year;
    */
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

    ///////////////////////
    //                   //
    //  EXTRACT QUALITY  //
    //                   //
    ///////////////////////
    
    // extract quality val
    tokenize(token, sentence, ",", &cursor);
    
    // we don't care about fix quality. Carry on...
    
    //////////////////////////////
    //                          //
    //  EXTRACT NUM SATELLITES  //
    //                          //
    //////////////////////////////
    
    // extract number
    tokenize(token, sentence, ",", &cursor);
    
    if (strcmp(token, "") != 0) 
    {
	// convert to int
	//       numSatellites = (short) strtol(token, NULL, 10);        
    }
    else 
	return 1;
    
    ////////////////////////
    //                    //
    //  EXTRACT DILUTION  //
    //                    //
    ////////////////////////
    
    // extract dilution
    tokenize(token, sentence, ",", &cursor);
    
    // we don't care about this. Carry on...
    
    ////////////////////////
    //                    //
    //  EXTRACT ALTITUDE  //
    //                    //
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
 /*
    if (mktime(&tt) < dataStore->epochTime)
    {
	puts("Aborting parse: Stale data");
	return 2;
    }
    else
    {*/
	//if (mktime(&tt) > dataStore->epochTime)
	dataStore->isDelta = 1;

	dataStore->lat = lat;
	dataStore->lon = lon;
	dataStore->altitude = alt;
//	dataStore->numSatellites = numSatellites;

	dataStore->time = time;

	// set UTC
	sprintf(dataStore->epochTime, "%2u%2u:%2u", time.hour, time.mins, time.sec);
       
	strcpy(dataStore->dmsLat, dmsLat);
	strcpy(dataStore->dmsLon, dmsLon);                

	dataStore->allDataSet |= (LATX | LONGX | SATSX | ALTX | TIMEX);
   // }
    return 0;
}

