#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parse.h"

bool parseGGA(OutData &message, char *sentence)
{
    char token[32];
    char* cursor = 0;
    float lat = 0.0f;
    float lon = 0.0f;
    float alt = 0.0f;

    ////////////////////
    //                //
    //  EXTRACT TIME  //
    //                //
    ////////////////////
    
    tokenize(token, sentence, ",", &cursor); // "hhmmss.ss"
    
    strncpy(message.UTC_time, token, 4);
    message.UTC_time[4] = '.';
    strncpy(messate.UTC_time + 5, token + 4, 2);
    message.UTC_time[8] = '\0';

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
	return false;

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
	return false;

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
    // we don't care about this. Carry on...
   
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
            return false;
    }
    else 
	return false;


    return true;
}
