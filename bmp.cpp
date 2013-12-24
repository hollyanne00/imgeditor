#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include "headers/bmp.h"

// Save a copy of the bmp into a new file with filename
void Bmp::saveCopy(std::string filename){

	std::string bfilename = filename + ".bmp";

	std::ofstream ofs;

	ofs.open(bfilename.c_str(), std::ios::out | std::ios::binary);
	std::ostream_iterator<char> it(ofs);

	// Copy bmp header, pixels and footer into file
	copy(this->header.begin(),this->header.end(),it);
	for(int i=0;i<height;i++){
		copy(this->pixels.at(i).begin(),this->pixels.at(i).end(),it);
	}
	copy(this->footer.begin(),this->footer.end(),it);
	
	ofs.close();
}

// Get pixel values at position i, j
// Note that pixel [0,0] is at [0,h-1]
// Red
const short int Bmp::getPixelR(int i, int j){

	// Red is the third byte value
	return (unsigned short int)((pixels.at(this->height-1-y).at((x*3)+2))&255);

}

// Green
const short int Bmp::getPixelG(int i, int j){

	// Green is the second byte value
	return (unsigned short int)((pixels.at(this->height-1-y).at((x*3)+1))&255);

}

// Blue
const short int Bmp::getPixelB(int i, int j){

	// Blue is the first byte value
	return (unsigned short int)((pixels.at(this->height-1-y).at(x*3))&255);

}