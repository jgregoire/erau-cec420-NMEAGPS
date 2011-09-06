#include "main.h"
#include "parse.h"

int parseGLL(struct NMEAData *dataStore, char* sentence) {
	char* token;
	
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
	
	//////////////////////
	//				    //
	//  EXTRACT STATUS  //
	//					//
	//////////////////////
	
	TOKENIZE;
	
	// I don't think we care about status?
	
}
