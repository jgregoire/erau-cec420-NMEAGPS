#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

// make a macro for tokenizing, since we always do it the same way
#define TOKENIZE "token = tokenize(sentence, ",")"
#define NONEMPTY strcmp(token, "") != 0

int parseGGA(struct NMEAData*, char*);

int parseGLL(struct NMEAData*, char*);

int parseGSV(struct NMEAData*, char*);

int parseRMC(struct NMEAData*, char*);

int parseZDA(struct NMEAData*, char*);
