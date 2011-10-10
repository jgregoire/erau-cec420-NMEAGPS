#include <string.h>
#include "parse.h"

bool parseGGA(OutData &message, char *sentence)
{
    char token[32];
    char* cursor = 0;

    ////////////////////
    //                //
    //  EXTRACT TIME  //
    //                //
    ////////////////////
    
    tokenize(token, sentence, ".", &cursor); // "hhmmss"
    
    strncpy(message.UTC_time, token, 4);
    message.UTC_time[4] = '.';
    strncpy(messate.UTC_time + 5, token + 4, 2);
    message.UTC_time[8] = '\0';

    return true;
}
