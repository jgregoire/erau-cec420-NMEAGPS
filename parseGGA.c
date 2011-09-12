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

// handle different units of altitude

int parseGGA(struct NMEAData *dataStore, char* sentence) {
	char token[256];
	char* cursor = 0;
	char temp[3];
	float lat = 0.0f;
	float lon = 0.0f;
    char la[12];
    char lo[12];
	short numSatellites = 0;
	float alt = 0.0f;
	
	////////////////////
	//                //
	//  EXTRACT TIME  //
	//                //
	////////////////////
	
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
	
	// calculate UTC and TAI
	dataStore->epochTime = mktime(&dataStore->date);	
	
	dataStore->date.tm_sec += 34;
	dataStore->taiTime = mktime(&dataStore->date);
	
	// record that time is set
	dataStore->allDataSet |= TIMEX;
	
	////////////////////////
	//					  //
	//  EXTRACT LATITUDE  //
	//					  //
	////////////////////////
	
	// extract lat val
	tokenize(token, sentence, ",", &cursor);
	
	if (strcmp(token, "") != 0) {
	
		// convert latitude to float
		lat = strtof(token, NULL);
		
		// extract N/S val
		tokenize(token, sentence, ",", &cursor);
		
		// if South, make latitude negative
		toupper(token[0]);
		if (strcmp(token, "S") == 0) {
			
			lat *= -1;
			
		}
		
		dataStore->lat = lat;
	    // split latitide float into 3 strings.
	    sprintf(la, "%f", lat);
	    if (strlen(la) == 7) {
	        dataStore->dmsLat[0] = la[0];
	        dataStore->dmsLat[1] = la[1];
	        dataStore->dmsLat[2] = 'o';
	        dataStore->dmsLat[3] = la[2];
	        dataStore->dmsLat[4] = la[3];
	        dataStore->dmsLat[5] = '.';
	        dataStore->dmsLat[6] = la[5];
	        dataStore->dmsLat[7] = la[6];
	        dataStore->dmsLat[8] = '\0';
	    } else {
	        dataStore->dmsLat[0] = la[0];
	        dataStore->dmsLat[1] = la[1];
	        dataStore->dmsLat[2] = la[3];
	        dataStore->dmsLat[3] = 'o';
	        dataStore->dmsLat[4] = la[4];
	        dataStore->dmsLat[5] = la[5];
	        dataStore->dmsLat[6] = '.';
	        dataStore->dmsLat[7] = la[6];
	        dataStore->dmsLat[8] = la[7];
	        dataStore->dmsLat[9] = '\0';	
	    }
	    		
		// record that lat is set
		dataStore->allDataSet |= LATX;
	}
	/////////////////////////
	//					   //
	//  EXTRACT LONGITUDE  //
	//					   //
	/////////////////////////
	
	// extract lon val
	tokenize(token, sentence, ",", &cursor);
	
	if (strcmp(token, "") != 0) {
	
		// convert lon to float
		lon = strtof(token, NULL);
		
		// extract E/W val
		tokenize(token, sentence, ",", &cursor);
		
		// if West, make lon negative
		toupper(token[0]);
		if (strcmp(token, "W") == 0) {
		
			lon *= -1;
			
		}
		
		dataStore->lon = lon;

	    // split longitide float into 3 strings.
	    sprintf(lo, "%f", lon);
	    if (strlen(lo) == 7) {
	        dataStore->dmsLon[0] = lo[0];
	        dataStore->dmsLon[1] = lo[1];
	        dataStore->dmsLon[2] = 'o';
	        dataStore->dmsLon[3] = lo[2];
	        dataStore->dmsLon[4] = lo[3];
	        dataStore->dmsLon[5] = '.';
	        dataStore->dmsLon[6] = lo[5];
	        dataStore->dmsLon[7] = lo[6];
	        dataStore->dmsLon[8] = '\0';
	    } else {
	        dataStore->dmsLon[0] = lo[0];
	        dataStore->dmsLon[1] = lo[1];
	        dataStore->dmsLon[2] = lo[3];
	        dataStore->dmsLon[3] = 'o';
	        dataStore->dmsLon[4] = lo[4];
	        dataStore->dmsLon[5] = lo[5];
	        dataStore->dmsLon[6] = '.';
	        dataStore->dmsLon[7] = lo[6];
	        dataStore->dmsLon[8] = lo[7];
	        dataStore->dmsLon[9] = '\0';	
	    }
		
		// record that lon is set
		dataStore->allDataSet |= LONGX;
	}
	///////////////////////
	//					 //
	//  EXTRACT QUALITY  //
	//					 //
	///////////////////////
	
	// extract quality val
	tokenize(token, sentence, ",", &cursor);
	
	// we don't care about fix quality. Carry on...
	
	//////////////////////////////
	//							//
	//  EXTRACT NUM SATELLITES  //
	//							//
	//////////////////////////////
	
	// extract number
	tokenize(token, sentence, ",", &cursor);
	
	if (strcmp(token, "") != 0) {
	
		// convert to int
		numSatellites = (short) strtol(token, NULL, 10);
		dataStore->numSatellites = numSatellites;
		
		// record that the numsats is set
		dataStore->allDataSet |= SATSX;
		
	}
	
	////////////////////////
	//					  //
	//  EXTRACT DILUTION  //
	//					  //
	////////////////////////
	
	// extract dilution
	tokenize(token, sentence, ",", &cursor);
	
	// we don't care about this. Carry on...
	
	////////////////////////
	//					  //
	//  EXTRACT ALTITUDE  //
	//					  //
	////////////////////////
    
	// extract altitude
	tokenize(token, sentence, ",", &cursor);
	
	if (strcmp(token, "") != 0) {
	
		// convert to float
		alt = strtof(token, NULL);

        tokenize(token, sentence, ",", &cursor);
        toupper(token[0]);

        if(token[0] == 'F')
        {
            dataStore->altitude = alt;
            dataStore->allDataSet |= ALTX;
        }
        else if (token[0] == 'M')
        {
            alt *= 0.3048;
    		dataStore->altitude = alt;
            dataStore->allDataSet |= ALTX;
        }
        else {
            return 1;
        }
	}
	
	return 0;
}

