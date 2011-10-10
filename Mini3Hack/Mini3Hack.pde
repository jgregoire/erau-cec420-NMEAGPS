#include "NewSoftSerial.h"

#include "main.h"

#define GPS_TX 13
#define GPS_RX 3

#define NORMAL_SIGNALLING  false
#define INVERTED_SIGNALLING true

NewSoftSerial GPSSerial(GPS_RX, GPS_TX); // third arg enables inverted signalling. Don't think we want that.

boolean partial_sentence = true;
char NMEA_sentence[81];
int tenmil; // incremented every ~10ms

OutData out_data();

/////////////////////
//                 //
//  INITILIZATION  //
//                 //
/////////////////////
void setup()
{
  
  Serial.begin(4800);
  Serial.write("Reading GPS...\n");
  
  GPSSerial.begin(4800);
  
}

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
  if (GPSSerial.available() ) {
    
    // begin reading new NMEA sentence
    partial_sentence = true;
    
    // get every character in the sentence
    for (int i = 0; partial_sentence == true; i++) {
      
      // read a character from GPS
      NMEA_sentence[i] = GPSSerial.read();
      
      // if we're at the end of the sentence...
      if (NMEA_sentence[i] == '\n') {
        
        // let the for loop end
        partial_sentence = false;
        
      }
      
    } // end for
    
    // we now have a full NMEA sentence. Let's parse it!
    parse(out_data, NMEA_sentence);
    
    // generate strings to output to LCD
    
  } // end if GPS.avail
  
  
  /////////////////
  //             //
  //  LCD LOGIC  //
  //             //
  /////////////////
  
  // hack-tastic timing code
  delay(10);
  // increment tenmil and make sure it's in range
  tenmil = (tenmil > 100) ? 0 : tenmil++;
  
  // periodically refresh the LCD.
  if (out_data.has_lock == true) {
    
    if (tenmil == 50) {
      
      // display time and alt
      
    } else if (tenmil == 100) {
      
      tenmil = 0;
      
      // display lat and long
      
    }
    
  } // end GPS lock check
  
} // end loop()

// EOF
