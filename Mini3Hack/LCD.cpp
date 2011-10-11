/*
  LiquidCrystal Library - display() and noDisplay()
 
 Class to display LCD information
 Created by Bryce Dodds
 
 */

#include "WProgram.h"
#include "LCD.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);



//setup pins and display
void LCD::init()
{
  
  lcd.begin(16, 2);
  
}
/*
void init(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6){
  
  //set up pins
  LiquidCrystal lcd(pin1, pin2, pin3, pin4, pin5, pin6);
  
}
*/

//function to display 
void LCD::displayInfo(char* str1, char* str2){
  
  //displays the lcd information while GPS has a fix
  lcd.print(str1);
  lcd.setCursor(0,1);
  lcd.print(str2);
  lcd.home();
  
}





