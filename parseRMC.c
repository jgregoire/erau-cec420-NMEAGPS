#include <stdlib.h>
#include <stdio.h>
#include "parse.h"

// Carole Fountain //

int parseRMC(struct NMEAData *dataStore, char* sentence) {
    char token[256], *cursor = 0;
    short lat = 0;
    short lon = 0;

    //////////////////////////////
    //				            //
    //  Extract UTC time        //
    //				            //
    //////////////////////////////
	
    // get UTC time 
    tokenize(token, sentence, ",", &cursor);
    
    if (strcmp(token, "") != 0)
    {
        dataStore->utcTime = strtol(token, NULL, 0);
    }
	
	
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
	
    // extract date
    tokenize(token, sentence, ",", &cursor);
	
    // don't care move on...
	
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
