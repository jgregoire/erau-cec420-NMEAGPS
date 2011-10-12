#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parse.h"

bool parseGGA(OutData &message, char *sentence)
{
    char token[32];
    char* cursor = 0;
    double lat = 0.0f;
    double lon = 0.0f;
    double alt = 0.0f;

    ////////////////////
    //                //
    //  EXTRACT TIME  //
    //                //
    ////////////////////
    
    tokenize(token, sentence, ",", &cursor); // "hhmmss.ss"
    
    strncpy(message.UTC_time, token, 4);
    message.UTC_time[4] = '.';
    strncpy(message.UTC_time + 5, token + 4, 2);
    message.UTC_time[8] = '\0';

    ////////////////////////
    //                    //
    //  EXTRACT LATITUDE  //
    //                    //
    ////////////////////////
    
    // extract lat val
    tokenize(token, sentence, ",", &cursor);
    
    if (token[0] != 0) 
    {
	// convert latitude to float
        lat = strtod(token, NULL);

        // extract N/S val

        
        // if South, make latitude negative
        //toupper(token[0]);
 /*       if (token[0] == 'S') 
	{
	   // lat *= -1;
	}
*/
        message.lat = lat;
    }
    else 
    {
	message.lat = 0.0;
    }

        tokenize(token, sentence, ",", &cursor);
        message.latletter = token[0] + 32;
    /////////////////////////
    //                     //
    //  EXTRACT LONGITUDE  //
    //                     //
    /////////////////////////
    
    // extract lon val
    tokenize(token, sentence, ",", &cursor);
    
   // if (token[0] ==  0) 
    //{
	// convert lon to float
        lon = strtod(token, NULL);
        //convertLon(lon, token);

        // extract E/W val

        
        // if West, make lon negative
        //toupper(token[0]);
        if (token[0] == 'W')
	{
	 //   lon *= -1;
	}
        message.lon = lon;
 //   }
 //   else 
 //   {
//	message.lon = 1.0;
 //   }
    
            tokenize(token, sentence, ",", &cursor);
            message.lonletter = token[0] + 32;
            
    ///////////////////////
    //                   //
    //  EXTRACT QUALITY  //
    //                   //
    ///////////////////////
    
    // extract quality val
    tokenize(token, sentence, ",", &cursor);
    if (strtol(token, NULL, 10) >= 1)
    {
      message.has_lock = true;
    }
    else
    {
  //    message.has_lock = false;
    }
    
    //////////////////////////////
    //                          //
    //  EXTRACT NUM SATELLITES  //
    //                          //
    //////////////////////////////
    
    // extract number
    tokenize(token, sentence, ",", &cursor);
    //message.num_sats = strtol(token, NULL, 10);
    // we don't care about this. Carry on...
   
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
    
//    if (token[0] == 0) 
//    {
	// convert to float
        alt = strtod(token, NULL);

        tokenize(token, sentence, ",", &cursor);
        //toupper(token[0]);

        if(token[0] == 'F')
        {
            alt *= 0.3048;
	}
            
        message.alt = alt;
 //   }
 //   else 
//	message.alt = 1.0;


    return true;
}
