#include <stdlib.h>
#include <stdio.h>
#include "parse.h"

// Carole Fountain  //

/////////////
//		   //
//  TO DO  //
//		   //
/////////////


int parseGSV(struct NMEAData *dataStore, char* sentence) {
    char token[256], *cursor = 0;
    short prn = 0;
    short snr = 0;
    short azimuth = 0;
    short elevation = 0;

    //////////////////////////////////////////////////
    //				                                //
    //  Extract Number of sentences for full data   //
    //				                                //
    //////////////////////////////////////////////////
	
    tokenize(token, sentence, ",", &cursor);
	
    // We don't need this value so moving on...
	
	
    //////////////////////////////////////
    //					                //
    //  Extract what sentence (1 or 2)  //
    //					                //
    //////////////////////////////////////
	
    // extract what sentence (1 or 2)
    tokenize(token, sentence, ",", &cursor);
 
    // We don't care so moving on...
    
    ////////////////////////////////////////////
    //					                      //
    //  Extract number of satellites in view  //
    //					                      //
    ////////////////////////////////////////////
	
    // extract # of satellites
    tokenize(token, sentence, ",", &cursor);
	
    dataStore->numSatellites = (short)strtol(token, NULL, 10);

// We already have this info so moving on...
	
    /**** FOR THE FOLLOWING PARAMETERS, INFORMATION CAN BE GIVEN FOR 
	  UP TO 4 SATELLITES PER SENTENCE  ***/
	
    //////////////////////////
    //					    //
    //  Extract PRN number  //
    //					    //
    //////////////////////////
	
    // turn PRN (for 1st satellite) into a useful value
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0)
    {
        // convert to int
	prn = (short)strtol(token, NULL, 10);
        dataStore->satellites[0].prn = prn; // store value in prearranged spot
    }
	
    /////////////////////////
    //					   //
    //  Extract Elevation  //
    //				   	   //
    /////////////////////////
	
    // extract elevation
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) 
    {
	// convert to int
	elevation = (short)strtol(token, NULL, 10);
	dataStore->satellites[0].elevation = elevation;
    }
	
    ////////////////////////
    //					  //
    //  Extract Azimuth   //
    //					  //
    ////////////////////////
	
    // extract azimuth
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0)
    {
        //convert to int
        azimuth = (short)strtol(token, NULL, 10);
        dataStore->satellites[0].azimuth = azimuth;
    }
	
    ////////////////////////
    //					  //
    //  Extract SNR       //
    //					  //
    ////////////////////////
	
    // extract SNR
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) 
    {
	// convert to int
	snr = (short)strtol(token, NULL, 10);
	dataStore->satellites[0].snr = snr;
    }
	
    //////////////////////////
    //					    //
    //  Extract PRN number  //
    //					    //
    //////////////////////////

    if (dataStore->numSatellites == 1)
	return 0;

    // turn PRN (for 2nd satellite) into a useful value
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0)
    {
        // convert to int
        prn = (short)strtol(token, NULL, 10);
        dataStore->satellites[1].prn = prn; // store value in prearranged spot
    }
	
    /////////////////////////
    //					   //
    //  Extract Elevation  //
    //				   	   //
    /////////////////////////
	
    // extract elevation
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) 
    {
	// convert to int
	elevation = (short)strtol(token, NULL, 10);
	dataStore->satellites[1].elevation = elevation;
    }
	
    ////////////////////////
    //					  //
    //  Extract Azimuth   //
    //					  //
    ////////////////////////
	
    // extract azimuth
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0)
    {
        //convert to int
        azimuth = (short)strtol(token, NULL, 10);
        dataStore->satellites[1].azimuth = azimuth;
    }
	
    ////////////////////////
    //					  //
    //  Extract SNR       //
    //					  //
    ////////////////////////
	
    // extract SNR
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) 
    {
	// convert to int
	snr = (short)strtol(token, NULL, 10);
	dataStore->satellites[1].snr = snr;
    }
	
    //////////////////////////
    //					    //
    //  Extract PRN number  //
    //					    //
    //////////////////////////	
    if (dataStore->numSatellites == 2)
	return 0;
    
// turn PRN (for 3rd satellite) into a useful value
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0)
    {
        // convert to int
        prn = (short)strtol(token, NULL, 10);
        dataStore->satellites[2].prn = prn; // store value in prearranged spot
    }
	
    /////////////////////////
    //					   //
    //  Extract Elevation  //
    //				   	   //
    /////////////////////////
	
    // extract elevation
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) 
    {
	// convert to int
	elevation = (short)strtol(token, NULL, 10);
	dataStore->satellites[2].elevation = elevation;
    }
	
    ////////////////////////
    //					  //
    //  Extract Azimuth   //
    //					  //
    ////////////////////////
	
    // extract azimuth
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0)
    {
        //convert to int
        azimuth = (short)strtol(token, NULL, 10);
        dataStore->satellites[2].azimuth = azimuth;
    }
	
    ////////////////////////
    //					  //
    //  Extract SNR       //
    //					  //
    ////////////////////////
	
    // extract SNR
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) 
    {
	// convert to int
	snr = (short)strtol(token, NULL, 10);
	dataStore->satellites[2].snr = snr;
    }
	
    //////////////////////////
    //					    //
    //  Extract PRN number  //
    //					    //
    //////////////////////////
    if (dataStore->numSatellites == 3)
	return 0;	
    // turn PRN (for 4th satellite) into a useful value
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0)
    {
        // convert to int
        prn = (short)strtol(token, NULL, 10);
        dataStore->satellites[3].prn = prn; // store value in prearranged spot
    }
	
    /////////////////////////
    //					   //
    //  Extract Elevation  //
    //				   	   //
    /////////////////////////
	
    // extract elevation
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) 
    {
	// convert to int
	elevation = (short)strtol(token, NULL, 10);
	dataStore->satellites[3].elevation = elevation;
    }
	
    ////////////////////////
    //					  //
    //  Extract Azimuth   //
    //					  //
    ////////////////////////
	
    // extract azimuth
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0)
    {
        //convert to int
        azimuth = (short)strtol(token, NULL, 10);
        dataStore->satellites[3].azimuth = azimuth;
    }
	
    ////////////////////////
    //					  //
    //  Extract SNR       //
    //					  //
    ////////////////////////
	
    // extract SNR
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0) 
    {
	// convert to int
	snr = (short)strtol(token, NULL, 10);
	dataStore->satellites[3].snr = snr;
    }
	
	
    return 0;
}







