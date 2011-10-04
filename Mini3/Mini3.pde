// Official libraries
#include <NewSoftSerial.h>

// Community libraries stored locally
#include "LiquidCrystal.h"
#include "DateTime.h"
#include "DateTImeStrings.h"

// C libraries
#include "string.h"

// Our libraries
#include "main.h"
#include "parse.h"

// pin definitions
#define GPS_TX 13
#define GPS_RX 14

#define TERMINATOR '\n'

// Global vars
NewSoftSerial GPSSerial(GPS_RX, GPS_TX); 
  // Yes, SoftwareSerial sucks, but we're gonna need the hardare
  // line to talk to the PC for Tuesday. After that we can switch
  // to hardware serial if we need to.

void setup()
{
  
  pinMode(GPS_TX, OUTPUT);
  pinMode(GPS_RX, INPUT);
  
  Serial.begin(9600); // Serial port to PC
  GPSSerial.begin(4200); // Serial port to GPS
  
  
    int parseStatus;

    struct NMEAData persistentData = EMPTY_NMEADATA;
    persistentData.date.tm_isdst = -1; // Necessary to keep hour records from being mangled by automatic DST.
    time_t rawtime = time(NULL);
    persistentData.localOffset = gmtime(&rawtime)->tm_hour - localtime(&rawtime)->tm_hour;
    struct NMEAMessage *message = 0;

    char *lineIn[80]; // Will be automatically alloc'ed by getline
    size_t messageLen = 0;

    char *outMessage = malloc(1024); // Way more memory than I'll ever need because I'm too lazy to figure out the maximum length of our output strings. No sizeof because the standard says sizeof(char) always == 1.

} // end setup()

void loop()
{
  
  // read in next available sentence and parse
   if (GPSSerial.available() == true) {
     
     readNMEASentence(lineIn);
     
     // parsey crap here
     	if((verifySentence(lineIn) == 0) && (validateChecksum(lineIn) == 0))
	{
	    // If we're in here, the lines were good
	    message = messagify(lineIn);
	    parseStatus = parse(&persistentData, message);
	    if ((parseStatus == 0) && (persistentData.isDelta == 1) && (persistentData.allDataSet == 0x7F))
	    {
		makeNMEADataString(outMessage, &persistentData);
		persistentData.isDelta = 0;

                Serial.print("Time (UTC): %02u:%02u.%02u\nCurrent Satellites: %u\nCurrent Lat: %f\nCurrentLon: %f\nCurrentAltitude (m): %f\n\n", persistentData.date.tm_hour + persistentData.localOffset, persistentData.date.tm_min, persistentData.date.tm_sec, persistentData.numSatellites, persistentData.lat/100, persistentData.lon/100, persistentData.altitude);

	    }
	    else
	    {
		persistentData.isDelta = 0;
	    }
	}

   } // end serial available check
  
  // LCD crap here
  
  
} // end loop()


/* Author: James Gregoire
 * Reads in single NMEA sentence from GPS
 */
void readNMEASentence(char* sentence)
{
  
  char string_full = false;
  
  for (int i = 0; string_full = false; i++) {
    
    sentence[i] = (char)GPSSerial.read(); // assuming it will wait until byte is available

    // check to see if this is the end of the sentence
    if (sentence[i] == TERMINATOR) {
      
      string_full = true;
      
    }
    
  } // end for()
  
} // end readNMEASentence()

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

    strncpy(str->data, intMsg, n); // Everything up to but not including the * is the data

    if (str->data[n-1] == ',')
    {
	str->data[n] = ',';
	++n;
    }

    str->data[n] = '\0';

    return str;
}


/* Author: Elliot Robinson
 * Takes a NMEAData struct and turns it into an output string for file storage.
 */
int makeNMEADataString(char *toFill, struct NMEAData *data)
{
    char t[1024];
    int offset = 0;

    offset += sprintf(t, "%u,%u,%u,%02u%02u%02u,%u,%u,%.4f,%.4f,%s,%s,%.4f,%u", data->date.tm_mon + 1, data->date.tm_mday, data->date.tm_year + 1900, data->date.tm_hour + data->localOffset, data->date.tm_min, data->date.tm_sec, (unsigned int)data->epochTime, (unsigned int)data->taiTime, data->lat, data->lon, data->dmsLat, data->dmsLon, data->altitude, data->numSatellites);


    // We can pull off this next part because the satellites all have PRNs between 01 and 32
    if (data->satellites[0].prn != 0)
    {
	offset += sprintf(t + offset, ",%u,%u,%u,%u", data->satellites[0].prn, data->satellites[0].elevation, data->satellites[0].snr, data->satellites[0].azimuth);
    }
    else
    {
	offset += sprintf(t + offset, ",,,,");
    }

    if (data->satellites[1].prn != 0)
    {
	offset += sprintf(t + offset, ",%u,%u,%u,%u", data->satellites[1].prn, data->satellites[1].elevation, data->satellites[1].snr, data->satellites[1].azimuth);
    }
    else
    {
	offset += sprintf(t + offset, ",,,,");
    }

    if (data->satellites[2].prn != 0)
    {
	offset += sprintf(t + offset, ",%u,%u,%u,%u", data->satellites[2].prn, data->satellites[2].elevation, data->satellites[2].snr, data->satellites[2].azimuth);
    }
    else
    {
	offset += sprintf(t + offset, ",,,,");
    }

    if (data->satellites[3].prn != 0)
    {
	offset += sprintf(t + offset, ",%u,%u,%u,%u", data->satellites[3].prn, data->satellites[3].elevation, data->satellites[3].snr, data->satellites[3].azimuth);
    }
    else
    {
	offset += sprintf(t + offset, ",,,,");
    }

    if (data->satellites[4].prn != 0)
    {
	offset += sprintf(t + offset, ",%u,%u,%u,%u", data->satellites[4].prn, data->satellites[4].elevation, data->satellites[4].snr, data->satellites[4].azimuth);
    }
    else
    {
	offset += sprintf(t + offset, ",,,,");
    }

    if (data->satellites[5].prn != 0)
    {
	offset += sprintf(t + offset, ",%u,%u,%u,%u", data->satellites[5].prn, data->satellites[5].elevation, data->satellites[5].snr, data->satellites[5].azimuth);
    }
    else
    {
	offset += sprintf(t + offset, ",,,,");
    }

    if (data->satellites[6].prn != 0)
    {
	offset += sprintf(t + offset, ",%u,%u,%u,%u", data->satellites[6].prn, data->satellites[6].elevation, data->satellites[6].snr, data->satellites[6].azimuth);
    }
    else
    {
	offset += sprintf(t + offset, ",,,,");
    }

    if (data->satellites[7].prn != 0)
    {
	offset += sprintf(t + offset, ",%u,%u,%u,%u", data->satellites[7].prn, data->satellites[7].elevation, data->satellites[7].snr, data->satellites[7].azimuth);
    }
    else
    {
	offset += sprintf(t + offset, ",,,,");
    }

    if (data->satellites[8].prn != 0)
    {
	offset += sprintf(t + offset, ",%u,%u,%u,%u", data->satellites[8].prn, data->satellites[8].elevation, data->satellites[8].snr, data->satellites[8].azimuth);
    }
    else
    {
	offset += sprintf(t + offset, ",,,,");
    }

    if (data->satellites[9].prn != 0)
    {
	offset += sprintf(t + offset, ",%u,%u,%u,%u", data->satellites[9].prn, data->satellites[9].elevation, data->satellites[9].snr, data->satellites[9].azimuth);
    }
    else
    {
	offset += sprintf(t + offset, ",,,,");
    }

    if (data->satellites[10].prn != 0)
    {
	offset += sprintf(t + offset, ",%u,%u,%u,%u", data->satellites[10].prn, data->satellites[10].elevation, data->satellites[10].snr, data->satellites[10].azimuth);
    }
    else
    {
	offset += sprintf(t + offset, ",,,,");
    }

    if (data->satellites[11].prn != 0)
    {
	sprintf(t + offset, ",%u,%u,%u,%u\r\n", data->satellites[11].prn, data->satellites[11].elevation, data->satellites[11].snr, data->satellites[11].azimuth);
    }
    else
    {
        sprintf(t + offset, "\r\n");
    }

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
	if (!(((w <= 57) && (w >= 48)) || ((w <= 90) && (w >= 65)) || (w == '.') || (w == ',') || (w == '-')))  
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

