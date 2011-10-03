#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

#include "time.h"
#include "string.h"

#include "main.h"
#include "parse.h"

// pin definitions
#define GPS_TX 13
#define GPS_RX 14

// Global vars
SoftwareSerial GPSSerial = new SoftwareSerial(GPS_RX, GPS_TX); 
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

    if ((fout == 0) || (fout2 == 0) || (fin == 0))
    {
	puts("Invalid filename");
	return 1;
    }

    struct NMEAData persistentData = EMPTY_NMEADATA;
    persistentData.date.tm_isdst = -1; // Necessary to keep hour records from being mangled by automatic DST.
    time_t rawtime = time(NULL);
    persistentData.localOffset = gmtime(&rawtime)->tm_hour - localtime(&rawtime)->tm_hour;
    struct NMEAMessage *message = 0;

    char *lineIn = 0; // Will be automatically alloc'ed by getline
    size_t messageLen = 0;

    char *outMessage = malloc(1024); // Way more memory than I'll ever need because I'm too lazy to figure out the maximum length of our output strings. No sizeof because the standard says sizeof(char) always == 1.

}

void loop()
{
  
   while(GPSSerial.available() == true) {
     
     
     
   }
  
}


