#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <math.h>

class OutData
{
  
private:
  

  
public:
  // attributes
  char UTC_time[8]; //"hhmm.ss"
  double alt;
  double lat;
  double lon;
  char time_line[16];
  char alt_line[16];
  char lat_line[16];
  char lon_line[16];
  char sat_line[16];
  
  bool has_lock;
  int num_sats;
  
  // functions
  void generate() // generate 4 string to be outputted to the LCD
  {
    float temp, temp1;
    time_line[0] = 'T';
    time_line[1] = 'i';
    time_line[2] = 'm';
    time_line[3] = 'e';
    time_line[4] = ':';
    time_line[5] = ' ';
    strncpy(time_line + 6, UTC_time, 16);
    
    temp = alt;
    temp1 = (temp - floor(temp)) * 100;
    sprintf(alt_line, "Alt:  %4d.%02d", (int)temp, (int)temp1%100); 
    
    temp = ((int)(lat/100)) + ((lat - (float)(((int)(lat/100)) * 100.0))/60.0);
    temp1 = (temp - floor(temp)) * 10000;
    sprintf(lat_line, "Lat:  %02d.%04d", (int)temp, (int)temp1%1000);
    
    temp = ((int)(lon/100)) + ((lon - (float)(((int)(lon/100)) * 100.0))/60.0);
    temp1 = fabs((temp - floor(temp))) * 10000;
    sprintf(lon_line, "Lon: %03d.%04u", (int)temp, (int)temp1%1000);
    
    sprintf(sat_line, "%02u Satellites", num_sats);
  } // end generate
  
  // constructors
  OutData()
  {
    
    strncpy(UTC_time, "0000.00", 7);
    alt = 0.0;
    lat = 0.0;
    lon = 0.0;
    
  } // end OutData()
  
  OutData(char* new_time, int new_alt, double new_lat, double new_lon)
  {
    
    strncpy(UTC_time, new_time, 16);
    alt = new_alt;
    lat = new_lat;
    lon = new_lon;
    
  } // end OutData(args)
  
}; // end class OutData

#endif
