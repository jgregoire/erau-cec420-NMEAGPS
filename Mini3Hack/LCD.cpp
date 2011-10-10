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

//setup pins and display
void init(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6){
  
  //set up pins
  LiquidCrystal lcd(pin1, pin2, pin3, pin4, pin5, pin6);
  
}


//function to display 
void LCD::displayInfo(char* str1, char* str2){
  
  //displays the lcd information while GPS has a fix
  while (true){
    lcd.println(str1);
    lcd.println(str2);
     
  }
  
}





