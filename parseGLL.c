#include "main.h"
#include "parse.h"

int parseGLL(struct NMEAData *dataStore, char* sentence) {
    char token[256], temp[256], *cursor = 0;
    char la[12];
    char lo[12];
    float lat, lon;
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
	
	    dataStore->allDataSet |= ALTX;
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
	
    	dataStore->allDataSet |= LONGX;
		
    }
	
    ////////////////////
    //				  //
    //  EXTRACT TIME  //
    //				  //
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
    
    dataStore->allDataSet |= TIMEX;
	
    //////////////////////
    //				    //
    //  EXTRACT STATUS  //
    //					//
    //////////////////////
	
    tokenize(token, sentence, ",", &cursor);
	
    // I don't think we care about status?
    return 0;
}
