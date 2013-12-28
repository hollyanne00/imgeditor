#include <iostream>
#include <fstream>
#include <string>
#include "headers/bmp.h"
#include "headers/loadbmp.h"
#include "headers/filters.h"

int main(int argc, char* argv[]){

	Bmp *bmpA = loadbmp("img/hello.bmp");

	// Save a copy
	bmpA->saveCopy("img/hellocopy");

	// Invert filter
	invert(bmpA);
	bmpA->saveCopy("img/helloinvert");

	Bmp *bmpB = loadbmp("img/rainbow.bmp");
	Bmp *bmpC = loadbmp("img/rainbow2.bmp");

	// Difference filter
	difference(bmpB, bmpC);
	bmpB->saveCopy("img/rainbowdifference.bmp");

	//medianFilter(bmpB, 3);

	//bmpB->saveCopy("img/median3x3");

	//medianFilter(bmpC, 7);

	//bmpC->saveCopy("img/median7x7");

	return 0;

}