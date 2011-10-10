/*
Header file for LCD display
Created by Bryce Dodds
*/

#include "LiquidCrystal.h"

#include "WProgram.h"
#ifndef Morse_h
#define Morse_h

class LCD
{
 public:
 LCD(char* Str, char* Str2);
 void displayInfo(char*, char*);
  
  private:
    char* _Str1;
    char* _Str2;
    
};

#endif
