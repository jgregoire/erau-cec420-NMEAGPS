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

    long mult = strtol(token, NULL, 10);
    mult = (mult - 1) * 4;

    if (mult == 0) // first GSV message
    {
	dataStore->satellites[0].prn = 0;
	dataStore->satellites[0].elevation = 0;
	dataStore->satellites[0].azimuth = 0;
	dataStore->satellites[0].snr = 0;	

	dataStore->satellites[1].prn = 0;
	dataStore->satellites[1].elevation = 0;
	dataStore->satellites[1].azimuth = 0;
	dataStore->satellites[1].snr = 0;	

	dataStore->satellites[2].prn = 0;
	dataStore->satellites[2].elevation = 0;
	dataStore->satellites[2].azimuth = 0;
	dataStore->satellites[2].snr = 0;	

	dataStore->satellites[3].prn = 0;
	dataStore->satellites[3].elevation = 0;
	dataStore->satellites[3].azimuth = 0;
	dataStore->satellites[3].snr = 0;	

	dataStore->satellites[4].prn = 0;
	dataStore->satellites[4].elevation = 0;
	dataStore->satellites[4].azimuth = 0;
	dataStore->satellites[4].snr = 0;	

	dataStore->satellites[5].prn = 0;
	dataStore->satellites[5].elevation = 0;
	dataStore->satellites[5].azimuth = 0;
	dataStore->satellites[5].snr = 0;	

	dataStore->satellites[6].prn = 0;
	dataStore->satellites[6].elevation = 0;
	dataStore->satellites[6].azimuth = 0;
	dataStore->satellites[6].snr = 0;	

	dataStore->satellites[7].prn = 0;
	dataStore->satellites[7].elevation = 0;
	dataStore->satellites[7].azimuth = 0;
	dataStore->satellites[7].snr = 0;	

	dataStore->satellites[8].prn = 0;
	dataStore->satellites[8].elevation = 0;
	dataStore->satellites[8].azimuth = 0;
	dataStore->satellites[8].snr = 0;	

	dataStore->satellites[9].prn = 0;
	dataStore->satellites[9].elevation = 0;
	dataStore->satellites[9].azimuth = 0;
	dataStore->satellites[9].snr = 0;	

	dataStore->satellites[10].prn = 0;
	dataStore->satellites[10].elevation = 0;
	dataStore->satellites[10].azimuth = 0;
	dataStore->satellites[10].snr = 0;	

	dataStore->satellites[11].prn = 0;
	dataStore->satellites[11].elevation = 0;
	dataStore->satellites[11].azimuth = 0;
	dataStore->satellites[11].snr = 0;	

    }

    ////////////////////////////////////////////
    //					                      //
    //  Extract number of satellites in view  //
    //					                      //
    ////////////////////////////////////////////
	
    // extract # of satellites
    tokenize(token, sentence, ",", &cursor);
	
    dataStore->numSatellites = (short)strtol(token, NULL, 10);
    dataStore->allDataSet |= SATSX;

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
        dataStore->satellites[mult + 0].prn = prn; // store value in prearranged spot
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
	dataStore->satellites[mult + 0].elevation = elevation;
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
        dataStore->satellites[mult + 0].azimuth = azimuth;
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
	dataStore->satellites[mult + 0].snr = snr;
    }
	
    //////////////////////////
    //					    //
    //  Extract PRN number  //
    //					    //
    //////////////////////////

    if (dataStore->numSatellites == (1 + mult))
	return 0;

    // turn PRN (for 2nd satellite) into a useful value
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0)
    {
        // convert to int
        prn = (short)strtol(token, NULL, 10);
        dataStore->satellites[mult + 1].prn = prn; // store value in prearranged spot
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
	dataStore->satellites[mult + 1].elevation = elevation;
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
        dataStore->satellites[mult + 1].azimuth = azimuth;
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
	dataStore->satellites[mult + 1].snr = snr;
    }
	
    //////////////////////////
    //					    //
    //  Extract PRN number  //
    //					    //
    //////////////////////////	
    if (dataStore->numSatellites == (2 + mult))
	return 0;
    
// turn PRN (for 3rd satellite) into a useful value
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0)
    {
        // convert to int
        prn = (short)strtol(token, NULL, 10);
        dataStore->satellites[mult + 2].prn = prn; // store value in prearranged spot
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
	dataStore->satellites[mult + 2].elevation = elevation;
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
        dataStore->satellites[mult + 2].azimuth = azimuth;
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
	dataStore->satellites[mult + 2].snr = snr;
    }
	
    //////////////////////////
    //					    //
    //  Extract PRN number  //
    //					    //
    //////////////////////////
    if (dataStore->numSatellites == (3 + mult))
	return 0;
	
    // turn PRN (for 4th satellite) into a useful value
    tokenize(token, sentence, ",", &cursor);
	
    if (strcmp(token, "") != 0)
    {
        // convert to int
        prn = (short)strtol(token, NULL, 10);
        dataStore->satellites[mult + 3].prn = prn; // store value in prearranged spot
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
	dataStore->satellites[mult + 3].elevation = elevation;
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
        dataStore->satellites[mult + 3].azimuth = azimuth;
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
	dataStore->satellites[mult + 3].snr = snr;
    }
	
	dataStore->allDataSet |= CONSTELLATIONX;
	
    return 0;
}







