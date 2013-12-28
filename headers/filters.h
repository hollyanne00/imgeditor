#ifndef FILTERS
#define FILTERS

#include "bmp.h"

void invert(Bmp*);
void fixContrast(Bmp*);
void difference(Bmp*, Bmp*);

void medianFilter(Bmp*, int);


#endif