#include "headers/bmp.h"
#include <iostream>
#include <vector>
#include <algorithm>

void invert(Bmp* bmp){

	for (int i = 0; i < bmp->getHeight(); i++){
		for (int j = 0; j < bmp->getWidth(); j++){
			short int r = bmp->getPixelR(i, j);
			short int g = bmp->getPixelG(i, j);
			short int b = bmp->getPixelB(i, j);
			bmp->setPixel(i, j, 255 - r, 255 - g, 255 - b);
		}
	}

}

// TODO: Optimise determination of neighbouring pixel values
void medianFilter(Bmp* bmp, int size){

	int width = bmp->getWidth();
	int height = bmp->getHeight();

	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){

			std::vector<short int> rvalues;
			std::vector<short int> gvalues;
			std::vector<short int> bvalues;

			int pi = i - (size / 2);
			int pj = j - (size / 2);

			// Get the values of neighbouring pixels
			for (int k = 0; k < size; k++){
				for (int l = 0; l < size; l++){

					// If we are in range of the pixels
					if ((pi + k >= 0) && (pi + k < width) && (pj + l >= 0) && (pj + l < height)){

						rvalues.push_back(bmp->getPixelR(pi+k, pj+l));
						gvalues.push_back(bmp->getPixelG(pi+k, pj+l));
						bvalues.push_back(bmp->getPixelB(pi+k, pj+l));

					}

				}
			}
			
			// Determine median and set pixel
			std::sort(rvalues.begin(), rvalues.end());
			std::sort(gvalues.begin(), gvalues.end());
			std::sort(bvalues.begin(), bvalues.end());

			int rindex = rvalues.size() / 2;
			int gindex = rvalues.size() / 2;
			int bindex = rvalues.size() / 2;

			bmp->setPixel(i, j, rvalues.at(rindex), gvalues.at(gindex), bvalues.at(bindex));

		}
	}

}