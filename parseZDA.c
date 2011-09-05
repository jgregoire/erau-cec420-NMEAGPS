#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "parse.h"

int parseZDA(struct NMEAData *dataStore, char* sentence) {
	char* token;
	int day = 0;
	int month = 0;
	int year = 0;
	int timezone = 0;
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	

		////////////////////
		//				  //
		//  EXTRACT TIME  //
		//				  //
		////////////////////
		
		TOKENIZE;
		
		// turn time into something useful
		
		time_comps.tm_hour = hours - 1;
		time_comps.tm_min = minutes - 1;
		time_comps.tim_sec = seconds - 1;
		
		////////////////////
		//				  //
		//  EXTRACT DATE  //
		//				  //
		////////////////////
		
		// extract day
		TOKENIZE;
		
		if (NONEMPTY) {
		
			day = (short) strtol(token, NULL, 10);
			dataStore->date.tm_mday = day - 1;
			
		}
		
		// extract month
		TOKENIZE;
		
		if (NONEMPTY) {
		
			month = (short) strtol(token, NULL, 10);
			dataStore->date.tm_mon = month - 1;
		
		}
		
		// extract year
		TOKENIZE;
		
		if (NONEMPTY) {
		
			year = (short) strtol(token, NULL, 10);
			dataStore->date.tm_year = year - 1900;
		
		}
		
		////////////////////////
		//					  //
		//  EXTRACT TIMEZONE  //
		//					  //
		////////////////////////
		
		// extract timezone
		TOKENIZE;
		
		if (NONEMPTY) {
		
			timezone = (short) strtol(token, NULL, 10);
			// do more stuff
		
		}
		
		//////////////////////////////
		//							//
		//  EXTRACT MINUTES OFFSET  //
		//							//
		//////////////////////////////
		
		TOKENIZE;
		
		// do shit
		
		////////////////////////////
		//						  //
		//  GENERATE UTC and TAI  //
		//						  //
		////////////////////////////
}










