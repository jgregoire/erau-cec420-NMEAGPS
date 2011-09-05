/* File: Main.c
 * Author: Elliot Robinson
 * Date modified: 3 Sept, 2011
 * Changes:
 *   3 Sept, 2011: Inititial creation
 */

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "main.h"

/* Author: Elliot Robinson
 * Contains the main event loop for the application
 */

#define MAX_MESSAGE_LENGTH 82 // 80 char max + "\r\n"

int verifySentence(char *);
int validateChecksum(char *);
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
	if((verifySentence(lineIn) && validateChecksum(lineIn)) == 1)
	{
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
    while(message[n] != '*')
	++n;

    strncpy(str->data, intMsg, n-1); // Everything up to but not including the * is the data

    return str;
}

/* Author: Elliot Robinson
 * Takes a NMEAData struct and turns it into an output string for file storage.
 */
int makeNMEADataString(char *toFill, struct NMEAData *data)
{
    return sprintf(toFill, "%u,%u,%u,%u,%u,%u,%.4f,%.4f,%s,%s,%.4f,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\r\n", data->date.month, data->date.day, data->date.year, data->utcTime, (unsigned int)data->epochTime, (unsigned int)data->taiTime, data->lat, data->lon, data->dmsLat, data->dmsLon, data->altitude, data->numSatellites, data->satellites[0].prn, data->satellites[0].elevation, data->satellites[0].snr, data->satellites[0].azimuth, data->satellites[1].prn, data->satellites[1].elevation, data->satellites[1].snr, data->satellites[1].azimuth, data->satellites[2].prn, data->satellites[2].elevation, data->satellites[2].snr, data->satellites[2].azimuth, data->satellites[3].prn, data->satellites[3].elevation, data->satellites[3].snr, data->satellites[3].azimuth, data->satellites[4].prn, data->satellites[4].elevation, data->satellites[4].snr, data->satellites[4].azimuth, data->satellites[5].prn, data->satellites[5].elevation, data->satellites[5].snr, data->satellites[5].azimuth, data->satellites[6].prn, data->satellites[6].elevation, data->satellites[6].snr, data->satellites[6].azimuth, data->satellites[7].prn, data->satellites[7].elevation, data->satellites[7].snr, data->satellites[7].azimuth, data->satellites[8].prn, data->satellites[8].elevation, data->satellites[8].snr, data->satellites[8].azimuth, data->satellites[9].prn, data->satellites[9].elevation, data->satellites[9].snr, data->satellites[9].azimuth, data->satellites[10].prn, data->satellites[10].elevation, data->satellites[10].snr, data->satellites[10].azimuth, data->satellites[11].prn, data->satellites[11].elevation, data->satellites[11].snr, data->satellites[11].azimuth);
}
