/* File: Main.c
 * Author: Elliot Robinson
 * Date modified: 3 Sept, 2011
 * Changes:
 *   3 Sept, 2011: Inititial creation
 *   5 Sept, 2011: Adds verifySentence and validateChecksum
 */

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "main.h"

/* Author: Elliot Robinson
 * Contains the main event loop for the application
 */

#define MAX_MESSAGE_LENGTH 82 // 80 char max + "\r\n"

int parse (struct NMEAData*, struct NMEAMessage*);

int main(int argc, char **argv)
{
    char *inFile = 0, *outFile = 0;
    parseCommandLine(argc, argv, &inFile, &outFile);

    // Open files
    FILE *fin = fopen(inFile, "r"); // Open input file for reading
    FILE *fout = fopen(outFile, "w"); // Open output file for writing, truncating current file

    struct NMEAData persistentData = EMPTY_NMEADATA;
    struct NMEAMessage *message = 0;

    char *lineIn = 0; // Will be automatically alloc'ed by getline
    size_t messageLen = 0;

    char *outMessage = malloc(1024); // Way more memory than I'll ever need because I'm too lazy to figure out the maximum length of our output strings. No sizeof because the standard says sizeof(char) always == 1.

    while (getline(&lineIn, &messageLen, fin) != EOF)
    {
	if((verifySentence(lineIn) == 0) && (validateChecksum(lineIn) == 0))
	{
	    // If we're in here, the lines were good
	    message = messagify(lineIn);

	    parse(&persistentData, message);

	    if (persistentData.isDelta == 1)
	    {
		makeNMEADataString(outMessage, &persistentData);
	   	fputs(outMessage, fout);
		persistentData.isDelta = 0;
	    }
	}
	else
	{
	    printf("Invalid sentence: %s", lineIn);
	}

	free(message); // Have to free this, since it gets malloc'ed in a function
	message = 0; // Avoiding re-free errors is a Good Thing™
    }

    free(outMessage); // Yep, more freeing.
    outMessage = 0; // Now I'm just being pedantic.

    return 0;
}

/* Author: Elliot Robinson
 * Parses command line into char arrays inFile and outFile. Prints usage message and exits if argc != 3
 */
void parseCommandLine(int argc, char **argv, char **inFile, char **outFile)
{
    if (argc == 3)
    {
	*inFile = argv[1];
        *outFile = argv[2];
	return;
    }
    else
    {
	printf("Usage: %s infile outfile\n", argv[0]);
	exit(1);
    }
}

/* Author: Elliot Robinson
 * Parses a raw string into a NMEAMessage struct
 */
struct NMEAMessage * messagify(char *message)
{
    struct NMEAMessage *str = malloc(sizeof(struct NMEAMessage));

    char *intMsg = message + 1; // Skip the initial '$'

    int n = 0;
    while(message[n] != ',')
	++n;

    strncpy(str->type, intMsg, n-1); // Everything up to but not including the comma is the type

    intMsg += n; // Move the pointer up to ignore the header

    n = 0; // Reset n;
    while(intMsg[n] != '*')
	++n;

    strncpy(str->data, intMsg, n-1); // Everything up to but not including the * is the data

    return str;
}

/* Author: Elliot Robinson
 * Takes a NMEAData struct and turns it into an output string for file storage.
 */
int makeNMEADataString(char *toFill, struct NMEAData *data)
{
    char t[1024];
    sprintf(t, "%u,%u,%u,%u,%u,%u,%.4f,%.4f,%s,%s,%.4f,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\r\n", data->date.tm_mon, data->date.tm_mday, data->date.tm_year + 1900, data->utcTime, (unsigned int)data->epochTime, (unsigned int)data->taiTime, data->lat, data->lon, data->dmsLat, data->dmsLon, data->altitude, data->numSatellites, data->satellites[0].prn, data->satellites[0].elevation, data->satellites[0].snr, data->satellites[0].azimuth, data->satellites[1].prn, data->satellites[1].elevation, data->satellites[1].snr, data->satellites[1].azimuth, data->satellites[2].prn, data->satellites[2].elevation, data->satellites[2].snr, data->satellites[2].azimuth, data->satellites[3].prn, data->satellites[3].elevation, data->satellites[3].snr, data->satellites[3].azimuth, data->satellites[4].prn, data->satellites[4].elevation, data->satellites[4].snr, data->satellites[4].azimuth, data->satellites[5].prn, data->satellites[5].elevation, data->satellites[5].snr, data->satellites[5].azimuth, data->satellites[6].prn, data->satellites[6].elevation, data->satellites[6].snr, data->satellites[6].azimuth, data->satellites[7].prn, data->satellites[7].elevation, data->satellites[7].snr, data->satellites[7].azimuth, data->satellites[8].prn, data->satellites[8].elevation, data->satellites[8].snr, data->satellites[8].azimuth, data->satellites[9].prn, data->satellites[9].elevation, data->satellites[9].snr, data->satellites[9].azimuth, data->satellites[10].prn, data->satellites[10].elevation, data->satellites[10].snr, data->satellites[10].azimuth, data->satellites[11].prn, data->satellites[11].elevation, data->satellites[11].snr, data->satellites[11].azimuth);
    strcpy(toFill, t);
    return 0;
}

/* Author: Bryce Dodds
 * Checks to see if the NMEA string provided is a valid NMEA string. If string the string is valid return 0 and 2 on on invalid string
 * 9//2011
 */
int validateChecksum(char *sentence)
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
	return 1;
    }
    else
    {
	return 0;  
    }
}  

/* Author: Bryce Dodds
 *  Checks to see if the NMEA string provided is a valid NMEA string.  If string the string is valid return 0 and 1 on invalid string
 *  9/4/2011
 */
int verifySentence(char *sentence)
{
    //check to see if string is longer than 82 characters
    if(strlen(sentence) > MAX_MESSAGE_LENGTH)
	return 1;
    //check to see if the length is less than 12
    if(strlen(sentence) < 12)
	return 1;
    //check to see if there is a dollar sign at the beginning of the string 
    if(sentence[0] != '$')
	return 1;
    //check to see if there is a G
    if(sentence[1] != 'G')
	return 1;
    
    //check to see if there is a P
    if(sentence[2] != 'P')
	return 1;
    
    //check to see if the checksum is a valid checksum
    if(sentence[strlen(sentence) - 5] != '*')
	return 1;

    //checks the frist number in the checksum is correct 
    if(! (((sentence[strlen(sentence) - 4] <= 57) && (sentence[strlen(sentence) - 4] >= 48)) || ((sentence[strlen(sentence) - 4] <= 70) && (sentence[strlen(sentence) - 4] >= 65))))
	return 1;

    if(! (((sentence[strlen(sentence) - 3] <= 57) && (sentence[strlen(sentence) - 3] >= 48)) || ((sentence[strlen(sentence) - 3] <= 70) && (sentence[strlen(sentence) - 3] >= 65))))
	return 1;
    
    //checks to see if formate at the end of the NMEA sequence is correct
    if(sentence[strlen(sentence) - 2] != '\r')
	return 1;
    
    if(sentence[strlen(sentence) - 1] != '\n')
	return 1;
    
    //checks to see if the NMEA strings are between the proper ASCII values 
    int dotCount = 0;
    int comCount = 0;
    int i;
    for( i = 1; i < strlen(sentence) - 5; i++)
    {
	char w = sentence[i];
	if (!(((w <= 57) && (w >= 48)) || ((w <= 90) && (w >= 65)) || (w == '.') || (w == ',')))  
            return 1;            
         
         
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
	return 1;
    
    
    return 0;
}





