#include "parse.h"

bool parseGSA(OutData &message, char * sentence)
{
    char token[8], *cursor = 0;
    
    // Eat record 1
    tokenize(token, sentence, ",", &cursor);
    
    tokenize(token, sentence, ",", &cursor);
    if (token[0] = '3')
    {
	message.has_lock = true;
    }
    else
    {
      message.has_lock = false;
    }

    return true;
}
