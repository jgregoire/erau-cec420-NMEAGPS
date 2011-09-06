#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

// make a macro for tokenizing, since we always do it the same way

void tokenize(char *, char *, char *);

int parseGGA(struct NMEAData*, char*);

int parseGLL(struct NMEAData*, char*);

int parseGSV(struct NMEAData*, char*);

int parseRMC(struct NMEAData*, char*);

int parseZDA(struct NMEAData*, char*);
