#include <iostream>
#include <fstream>
#include <string>
#include "headers/bmp.h"

Bmp* loadbmp(std::string filename){

	std::ifstream ifs;
	std::string line;
	std::streampos size;
	std::ofstream ofs;

	Bmp *mybmp;

	std::cout << "Opening file " << filename << std::endl;

	ifs.open(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (ifs.is_open()){

		// gets file size and create new byte array to hold it
		size = ifs.tellg();
		char *bytes = new char[size];
		std::cout << "size of file: " << (unsigned int)size << std::endl;
		ifs.seekg(0, std::ios::beg);

		// get the image into memory
		ifs.read(bytes, size);

		// is it a bitmap? should be FF D8 ie. 255 216 
		std::cout << (char)(bytes[0]) << (char)(bytes[1]) << std::endl;

		mybmp = new Bmp(bytes, size);

		ifs.close();

	}

	return mybmp;
}