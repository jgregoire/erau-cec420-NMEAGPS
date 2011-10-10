/*
  LiquidCrystal Library - display() and noDisplay()
 
 Class to display LCD information
 Created by Bryce Dodds
 
 */

#include "WProgram.h"
#include "LCD.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/*
Constructor to accpet all information to display onto the LCD
*/
//LCD::LCD() {}

/*LCD::LCD(char* Str1, char* Str2)
{
    _Str1 = Str1;
    
    _Str2 = Str2;
}*/

//function to display 
void LCD::displayInfo(char* str1, char* str2){
  
  //displays the lcd information while GPS has a fix
  while (true){
    lcd.println(str1);
    lcd.println(str2);
     
  }
  
  
}
