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
	char* token;
	char temp[3];
	float lat = 0.0f;
	float lon = 0.0f;
	short numSatellites = 0;
	float alt = 0.0f;
	
	////////////////////
	//				  //
	//  EXTRACT TIME  //
	//				  //
	////////////////////
	
	TOKENIZE; // "hhmmss.ss"
	
	// turn time into a useful value
	// get "hh" from "hhmmss.ss"
	strncpy(temp, token, 2);
	dataStore->date.tm_hr = (int) strtol(temp, NULL) - 1;
	
	// get mm
	memcpy(temp, &token[2], 2);
	dataStore->date.tm_min = (int) strtol(temp, NULL) - 1;
	
	// get ss (ignoring .ss)
	memcpy(temp, $token[4], 2);
	dataStore->date.tm_sec = (int) strtol(temp, NULL) - 1;
	
	
	////////////////////////
	//					  //
	//  EXTRACT LATITUDE  //
	//					  //
	////////////////////////
	
	// extract lat val
	TOKENIZE;
	
	if (NONEMPTY) {
	
		// convert latitude to float
		lat = strtof(token, NULL);
		
		// extract N/S val
		TOKENIZE;
		
		// if South, make latitude negative
		toupper(token);
		if (strcmp(token, "S") == 0) {
			
			lat *= -1;
			
		}
		
		dataStore->lat = lat;
	}
	/////////////////////////
	//					   //
	//  EXTRACT LONGITUDE  //
	//					   //
	/////////////////////////
	
	// extract lon val
	TOKENIZE;
	
	if (NONEMPTY) {
	
		// convert lon to float
		lon = strtof(token, NULL);
		
		// extract E/W val
		TOKENIZE;
		
		// if West, make lon negative
		toupper(token);
		if (strcmp(token, "W") == 0) {
		
			lon *= -1;
			
		}
		
		dataStore->lon = lon;
	}
	///////////////////////
	//					 //
	//  EXTRACT QUALITY  //
	//					 //
	///////////////////////
	
	// extract quality val
	TOKENIZE;
	
	// we don't care about fix quality. Carry on...
	
	//////////////////////////////
	//							//
	//  EXTRACT NUM SATELLITES  //
	//							//
	//////////////////////////////
	
	// extract number
	TOKENIZE;
	
	if (NONEMPTY) {
	
		// convert to int
		numSatellites = (short) strtol(token, NULL, 10);
		dataStore->numSatellites = numSatellites;
		
	}
	
	////////////////////////
	//					  //
	//  EXTRACT DILUTION  //
	//					  //
	////////////////////////
	
	// extract dilution
	TOKENIZE;
	
	// we don't care about this. Carry on...
	
	////////////////////////
	//					  //
	//  EXTRACT ALTITUDE  //
	//					  //
	////////////////////////
	
	// extract altitude
	TOKENIZE;
	
	if (NONEMPTY) {
	
		// convert to float
		alt = strtof(token, NULL);
		dataStore->altitude = alt;
		
	}
	
	// extract units
	TOKENIZE;
	
	// assuming always meters for now
	
	return 0;
}






