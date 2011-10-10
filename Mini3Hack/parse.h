#ifndef PARSE_H
#define PARSE_H

#include "main.h"

class Parser 
{
  private:
    struct NMEAMessage { // Wrapper around character data to reduce defects by avoiding passing raw character arrays to parse. 
	char type[6]; // 2 + 3 +'\0'
	char data[73]; // Max length is 80, 80 - message type (5) - '$' - "*??" + '\0' == 73
    };

    struct Parser::NMEAMessage messagify(char *message);

    bool verify(char *sentence);
    bool validate(char *sentence);

  public:
    bool parse(OutData &message, char * sentence);
};

bool parseGGA(OutData &message, char * sentence);
bool parseGSV(OutData &message, char * sentence);
bool parseGSA(OutData &message, char * sentence);
bool parseZDA(OutData &message, char * sentence);

#endif
