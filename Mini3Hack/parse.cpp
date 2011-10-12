#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "main.h"
#include "parse.h"

/* Author: Elliot Robinson
 * Parses a raw string into a NMEAMessage struct
 */
struct Parser::NMEAMessage Parser::messagify(char *message)
{
    struct NMEAMessage str;

    char *intMsg = message + 1; // Skip the initial '$'

    int n = 0;
    while(intMsg[n] != ',')
	++n;

    strncpy(str.type, intMsg, n-1); // Everything up to but not including the comma is the type

    intMsg += n; // Move the pointer up to ignore the header

    n = 0; // Reset n;
    while(intMsg[n] != '*')
	++n;

    strncpy(str.data, intMsg, n); // Everything up to but not including the * is the data

    if (str.data[n-1] == ',')
    {
	str.data[n] = ',';
	++n;
    }

    str.data[n] = '\0';

    return str;
}

bool Parser::parse(OutData &outdata, char *sentence) {
    // chop off the first section of the comma-delimited sentence
    // and store it in a new string

 //   if (!verify(sentence))
//	return false;

    //NMEAMessage message = messagify(sentence);
    
    if (sentence[4] == 71)
    {
        return parseGGA(outdata, sentence + 7);
    }
  /*  else if (message.type[4] == 'V')
    {
        return parseGSV(outdata, message.data);
    } 
    else if (message.type[3] == 'D')
    {
	return parseZDA(outdata, message.data);
    }
    else
    {
        return parseGSA(outdata, message.data);
    	// We didn't get a message we care about.
	return false;
    }*/
//    return false;
} // end parse()


/* Author: Bryce Dodds
 * Checks to see if the NMEA string provided is a valid NMEA string. If string the string is valid return 0 and 2 on on invalid string
 * 9//2011
 */
bool Parser::validate(char *sentence)
{
    int i=0; 
    int sum=0, sump=0;   
    int a = strlen(sentence) - 4;
    char sumProvided[3];
    strncpy(sumProvided, sentence + a, 2);

    sump = strtol(sumProvided, NULL, 16);

    for(i=1; i<(a - 1); i++)
    {
	sum=sum ^ sentence[i];
    } //calculate the checksum

    if(sump != sum) //check if the checksum is the same with the prodived one. 
    {
	return false;
    }
    else
    {
	return true;  
    }
}  


/* Author: Bryce Dodds
 *  Checks to see if the NMEA string provided is a valid NMEA string.  If string the string is valid return 0 and 1 on invalid string
 *  9/4/2011
 */
bool Parser::verify(char *sentence)
{
    //check to see if string is longer than 82 characters
    /*if(strlen(sentence) > 82)
	return false;*/

    //check to see if the length is less than 12
    if(strlen(sentence) < 12)
	return false;

    //check to see if there is a dollar sign at the beginning of the string 
    if(sentence[0] != '$')
	return false;

    //check to see if there is a G
    if(sentence[1] != 'G')
	return false;

    //check to see if there is a P
    if(sentence[2] != 'P')
	return false;

 /*   //check to see if the checksum is a valid checksum
    if(sentence[strlen(sentence) - 5] != '*')
	return false;

    //checks the frist number in the checksum is correct 
    if(! (((sentence[strlen(sentence) - 4] <= 57) && (sentence[strlen(sentence) - 4] >= 48)) || ((sentence[strlen(sentence) - 4] <= 70) && (sentence[strlen(sentence) - 4] >= 65))))
	return false;

    if(! (((sentence[strlen(sentence) - 3] <= 57) && (sentence[strlen(sentence) - 3] >= 48)) || ((sentence[strlen(sentence) - 3] <= 70) && (sentence[strlen(sentence) - 3] >= 65))))
	return false;

    //checks to see if formate at the end of the NMEA sequence is correct
    if(sentence[strlen(sentence) - 2] != '\r')
	return false;

    if(sentence[strlen(sentence) - 1] != '\n')
	return false;
*/
    //checks to see if the NMEA strings are between the proper ASCII values 
    int dotCount = 0;
    int comCount = 0;
    int i;
    for( i = 1; i < strlen(sentence) - 5; i++)
    {
	char w = sentence[i];
	if (!(((w <= 57) && (w >= 48)) || ((w <= 90) && (w >= 65)) || (w == '.') || (w == ',') || (w == '-')))  
            return false;            
         

	//if a dot is found increment the dotcounter 
	if(w == '.')
	    dotCount++;

	//if a , is found reset the dotcount
	if(w == ',') {
	    dotCount = 0;
	    comCount++;       
	}
         
    }

    if(comCount == 0)
	return false;
    
    return true;
}
