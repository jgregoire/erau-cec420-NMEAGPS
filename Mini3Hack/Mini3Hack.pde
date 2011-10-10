#include "NewSoftSerial/NewSoftSerial.h"
#include "main.h"

#define GPS_TX 13
#define GPS_RX 3

NewSoftSerial GPSSerial(GPS_RX, GPS_TX); // third arg enables inverted signalling. Don't think we want that.
OutData out_data();
Parser parser();

boolean partial_sentence = true;
boolean display_time = true;
char NMEA_sentence[83];
char last_sec;

/////////////////////
//                 //
//  INITILIZATION  //
//                 //
/////////////////////
void setup()
{
  
  // init serial to PC
  Serial.begin(4800);
  Serial.write("Reading GPS...\n");
  
  // init serial from GPS
  GPSSerial.begin(4800);
  
} // end setup()

/////////////////
//             //
//  MAIN LOOP  //
//             //
/////////////////
void loop()
{
  
  /////////////////
  //             //
  //  GPS LOGIC  //
  //             //
  /////////////////
  
  // get a line from the GPS
  readNMEASentence(NMEA_sentence, GPSSerial);
    
  // we now have a full NMEA sentence. Let's parse it!
  parser.parse(out_data, NMEA_sentence);
    
  // generate strings to output to LCD
  out_data.generate();
    
  } // end if GPS.avail
    
  /////////////////
  //             //
  //  LCD LOGIC  //
  //             //
  /////////////////
    
  // periodically refresh the LCD.
  if (out_data.has_lock == true) {
    
    // every second (aka every time the seconds value changes)
    if (last_sec != out_data.UTC_time[6]) {
      
      // alternate which data to display
      if (display_time == true) {
        
        //lcd.display(out_data.time_line, out_data.alt_line);
        display_time != display_time;
        
      } else {
        
        // display lat and long
        //lcd.display(out_data.lat_line, out_data.lon_line);
        
        display_time != display_time;
        
      }
      
    } // end if new second
    
  } else {
    
    // every second...
    if (last_sec != out_data.UTC_time[6]) {
      
      //lcd.display("No GPS fix...   ", "                ");
      
    }
    
  } // end GPS lock check
  
  last_sec = out_data.UTC_time[6];
  
} // end loop()

//////////////////////
//                  //
//  USER FUNCTIONS  //
//                  //
//////////////////////

void readNMEASentence(char* sentence, NewSoftSerial port)
{
  
  // delay until data available
  while(GPSSerial.available() == false);
  
  if (GPSSerial.available() ) {
    
    // begin reading new NMEA sentence
    partial_sentence = true;
    
    // get every character in the sentence
    for (int i = 0; partial_sentence == true; i++) {
      
      // read a character from GPS
      NMEA_sentence[i] = GPSSerial.read();
      
      // if we're at the end of the sentence...
      if (NMEA_sentence[i] == '\n' || strlen(NMEA_sentence) > 82) {
        
        // let the for loop end
        partial_sentence = false;
        
      }
      
    } // end for
    
  } // end if available
  
}

// EOF //
