/* File: Main.h
 * Author: Elliot Robinson
 * Date modified: 3 Sept, 2011
 * Changes:
 *   3 Sept, 2011: Inititial creation
 */

#ifndef MAIN_H
#define MAIN_H
//                       Date    UTC epoch        lat long
#define EMPTY_NMEADATA {{0, 0, 0}, 0, 0,   /*0*/, 0.0, 0.0, "", "", 0.0, 0, {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 0, 0, 0};
#define MAX_MESSAGE_LENGTH 82 // 80 char max + "\r\n"

/* I think this is obsolete
struct Date { // Contains a month, day, year date
    short month;
    short day;
    short year;
};*/

struct Time {
  
  int hour;
  int mins;
  int sec;
  
};

struct Satellite { // Contains data pertaining to a single satellite
    short prn;
    short elevation; // Degrees
    short snr;
    short azimuth;
};

struct NMEAMessage { // Wrapper around character data to reduce defects by avoiding passing raw character arrays to parse. 
    char type[6]; // 2 + 3 +'\0'
    char data[73]; // Max length is 80, 80 - message type (5) - '$' - "*??" + '\0' == 73
};

struct NMEAData { // Keeps track of pertinent data gathered from NMEA sentences
    struct Time time;
    short utcTime; // Yes, underscores would be better here…
    char epochTime[8];
    float lat; // North lat == positive, South lat == negative.
    float lon; // Same as above for East and West
    char dmsLat[16]; // (dddommm’sss.ss”\0)
    char dmsLon[16]; // Same as above.
    float altitude;
    short numSatellites;
    struct Satellite satellites[12]; // A maximum of 12 satellites can be considered in view in NMEA. I see no reason to store more than what the system can describe.
    short isDelta; // 0 if the structure has not been changed, 1 If the structure has changed and needs to be written to the output file.
    char allDataSet;
    short localOffset;
    // I think isDelta should be changed to a check to make sure ALL data is present before posting results. - James
};

// used for allDataSet
#define TIMEX 1
#define DATEX 2
#define LATX  4
#define LONGX 8
#define ALTX  16
#define SATSX 32
#define CONSTELLATIONX 64

int main(int argc, char **argv);
void parseCommandLine(int argc, char **argv, char **inFile, char **outFile, char **outFile2);
struct NMEAMessage * messagify(char *message);
int makeNMEADataString(char* toFill, struct NMEAData *data);
int verifySentence(char *sentence);
int validateChecksum(char *sentence);

#endif






