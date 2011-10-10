#ifndef MAIN_H
#define MAIN_H

#include <string.h>

class OutData
{
  
private:
  
  // attributes
  char UTC_time[8]; //"hhmm.ss"
  float alt;
  float lat;
  float lon;
  
public:
  
  // attributes
  char time_line[16];
  char alt_line[16];
  char lat_line[16];
  char lon_line[16];
  
  boolean has_lock;
  int num_sats;
  
  // functions
  void generate() // generate 4 string to be outputted to the LCD
  {
    
    strncpy(time_line, UTC_time, 16);
    sprintf(alt_line, "%5.2f", alt);
    sprintf(lat_line, "%2.4f", lat);
    sprintf(lon_line, "%3.4f", lon);
    
  }
  
  // constructors
  OutData()
  {
    
    strncpy(UTC_time, "0000.00", 7);
    alt = 0.0;
    lat = 0.0;
    lon = 0.0;
    
  }
  
  OutData(char* new_time, int new_alt, double new_lat, double new_lon)
  {
    
    strncpy(UTC_time, new_time, 16);
    alt = new_alt;
    lat = new_lat;
    lon = new_lon;
    
  }
  
}; // end class OutData

#endif