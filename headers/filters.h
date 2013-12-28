#ifndef FILTERS
#define FILTERS

#include "bmp.h"

void invert(Bmp*);
void fixContrast(Bmp*);

void medianFilter(Bmp*, int size);


#endif