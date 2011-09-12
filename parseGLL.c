#include "main.h"
#include "parse.h"

int parseGLL(struct NMEAData *dataStore, char* sentence) {
    char token[256], temp[256], *cursor = 0;
    char la[8];
    char lo[8];
    char dmsLa[12];
    char dmsLo[12];
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
	        dmsLa[0] = la[0];
	        dmsLa[1] = la[1];
	        dmsLa[2] = 'o';
	        dmsLa[3] = la[2];
	        dmsLa[4] = la[3];
	        dmsLa[5] = '.';
	        dmsLa[6] = la[5];
	        dmsLa[7] = la[6];
	        dmsLa[8] = '\0';
	    } else {
	        dmsLa[0] = la[0];
	        dmsLa[1] = la[1];
	        dmsLa[2] = la[3];
	        dmsLa[3] = 'o';
	        dmsLa[4] = la[4];
	        dmsLa[5] = la[5];
	        dmsLa[6] = '.';
	        dmsLa[7] = la[6];
	        dmsLa[8] = la[7];
	        dmsLa[9] = '\0';	
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
	
	    // split latitide float into 3 strings.
	    sprintf(lo, "%f", lon);
	    if (strlen(lo) == 7) {
	        dmsLo[0] = lo[0];
	        dmsLo[1] = lo[1];
	        dmsLo[2] = 'o';
	        dmsLo[3] = lo[2];
	        dmsLo[4] = lo[3];
	        dmsLo[5] = '.';
	        dmsLo[6] = lo[5];
	        dmsLo[7] = lo[6];
	        dmsLo[8] = '\0';
	    } else {
	        dmsLo[0] = lo[0];
	        dmsLo[1] = lo[1];
	        dmsLo[2] = lo[3];
	        dmsLo[3] = 'o';
	        dmsLo[4] = lo[4];
	        dmsLo[5] = lo[5];
	        dmsLo[6] = '.';
	        dmsLo[7] = lo[6];
	        dmsLo[8] = lo[7];
	        dmsLo[9] = '\0';	
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
