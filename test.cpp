#include <iostream>
#include <fstream>
#include <string>
#include "headers/bmp.h"
#include "headers/loadbmp.h"

int main(int argc, char* argv[]){

	if (argc != 2){
		std::cout << "Usage: <filename>" << std::endl;
		return 0;
	}

	Bmp *bmpA = loadbmp(argv[1]);

	bmpA->saveCopy("test");

}