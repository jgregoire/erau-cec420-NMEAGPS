#include "NewSoftSerial.h"
#include "main.h"
#include "parse.h"
#include "lcd.h"

// uncomment this line to enable debug output to PC
#define _DEBUG
#define _DEBUG2

#define GPS_TX 6
#define GPS_RX 7

#define BLANK_LINE "                "

NewSoftSerial GPSSerial(GPS_RX, GPS_TX); // third arg enables inverted signalling. Don't think we want that.
OutData out_data;
Parser parser;
LCD screen;

boolean display_time = true;
char NMEA_sentence[83];
char last_sec;
int i;

/////////////////////
//                 //
//  INITILIZATION  //
//                 //
/////////////////////
void setup()
{
  #ifdef _DEBUG2
  // init serial to PC
  Serial.begin(9600);
  Serial.write("\n\nReading GPS...\n");
  #endif
  
  // init serial from GPS
  GPSSerial.begin(4800);
  
  // initialize LCD
  screen.init();
  
  screen.displayInfo("Initilizating...", "Panda Bears!");
  
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
  

  #ifdef _DEBUG
  Serial.print("Beginning main loop...");
  #endif
  
  // get a line from the GPS
  readNMEASentence();
  
  #ifdef _DEBUG
 // Serial.println(NMEA_sentence);
  //Serial.println("\nParsing sentence...");
  #endif  
  
  // we now have a full NMEA sentence. Let's parse it!
  parser.parse(out_data, NMEA_sentence);
  
  #ifdef _DEBUG
  //Serial.println("Generating LCD output strings...");
  #endif
    
  // generate strings to output to LCD
  out_data.generate();
  
  #ifdef _DEBUG
  Serial.print(out_data.lat_line);
  Serial.print(", ");
  Serial.print(out_data.lon_line);
  Serial.print(", ");
  Serial.print(out_data.alt_line);
  Serial.print(", ");
  Serial.print(out_data.num_sats);
  Serial.print(", ");
  Serial.println(out_data.UTC_time);
  #endif
  

  /////////////////
  //             //
  //  LCD LOGIC  //
  //             //
  /////////////////
    
  // periodically refresh the LCD.
  if (out_data.has_lock == true) {
    
    // every second (aka every time the seconds value changes)
    if (last_sec != out_data.UTC_time[6]) {
      
      #ifdef _DEBUG
      //Serial.println("New second");
      #endif
      
      // alternate which data to display
      if (display_time == true) {
        
        // display time and alt
        screen.displayInfo(out_data.time_line, out_data.alt_line);
        
        // toggle which message to display
        display_time != display_time;
        
      } else {
        
        // display lat and long
        screen.displayInfo(out_data.lat_line, out_data.lon_line);
        
        // toggle which message to display
        display_time != display_time;
      }
      
    } // end if new second
    
  } else {
    
    // every second...
    if (last_sec != out_data.UTC_time[6]) {
      
      #ifdef _DEBUG          
      //Serial.println("No GPS fix.");
      #endif
      
      // output "No fix" to LCD
      screen.displayInfo("No GPS fix", out_data.time_line);//out_data.sat_line);
      
    }
    
  } // end GPS lock check
  
  last_sec = out_data.UTC_time[6];  
} // end loop()

//////////////////////
//                  //
//  USER FUNCTIONS  //
//                  //
//////////////////////

void readNMEASentence()
{
  
    #ifdef _DEBUG
    //Serial.println("Reading sentence from GPS...");
    #endif
    
    // begin reading new NMEA sentence
    // get every character in the sentence
    i = 0;
    do
    {
      if (GPSSerial.available() > 0)
      {
        NMEA_sentence[i] = '\0';
        // read a character from GPS
        NMEA_sentence[i] = GPSSerial.read();
          
        if ((NMEA_sentence[i] == -1) || NMEA_sentence[i] > 92)
        {
          NMEA_sentence[i] = 0;
        }
        else
        {  
          //Serial.print(NMEA_sentence[i]);
          ++i;
        }
      }
    } while ((NMEA_sentence[i-4] != '*') && (i < 81));
    
    // null terminate string
    NMEA_sentence[i-1] = '\r';
    NMEA_sentence[i] = '\n';
    NMEA_sentence[i+1] = '\0';
    
    #ifdef _DEBUG2
    Serial.println(NMEA_sentence);
    #endif 
    
    #ifdef _DEBUG
    //Serial.println("Received NMEA sentence.");
    #endif
}

// EOF //
