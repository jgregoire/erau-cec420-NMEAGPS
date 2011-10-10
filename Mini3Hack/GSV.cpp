#include "parse.h"

bool parseGSV(OutData &message, char * sentence)
{
    char token[256], *cursor = 0;

    //////////////////////////////////////////////////
    //                                                //
    //  Extract Number of sentences for full data   //
    //                                                //
    //////////////////////////////////////////////////
    
    tokenize(token, sentence, ",", &cursor);
    
    // We don't need this value so moving on...
    
    
    //////////////////////////////////////
    //                                    //
    //  Extract what sentence (1 or 2)  //
    //                                    //
    //////////////////////////////////////
    
    // extract what sentence (1 or 2)
    tokenize(token, sentence, ",", &cursor);

    ////////////////////////////////////////////
    //                                          //
    //  Extract number of satellites in view  //
    //                                          //
    ////////////////////////////////////////////
    
    // extract # of satellites
    tokenize(token, sentence, ",", &cursor);
    
    message.num_sats = (short)strtol(token, NULL, 10);

    return true;
}
