#include <iostream>
#include <fstream>
#include <string>
#include "headers/bmp.h"
#include "headers/loadbmp.h"
#include "headers/filters.h"

int main(int argc, char* argv[]){

	if (argc != 2){
		std::cout << "Usage: <filename>" << std::endl;
		return 0;
	}

	Bmp *bmpA = loadbmp(argv[1]);
	Bmp *bmpB = loadbmp(argv[1]);
	Bmp *bmpC = loadbmp(argv[1]);

	bmpA->saveCopy("img/testcopy");

	invert(bmpA);

	bmpA->saveCopy("img/invert");

	medianFilter(bmpB, 3);

	bmpB->saveCopy("img/median3x3");

	medianFilter(bmpC, 7);

	bmpC->saveCopy("img/median7x7");

	return 0;

}