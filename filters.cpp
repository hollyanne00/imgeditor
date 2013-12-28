#include "headers/bmp.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

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

// Currrently puts difference result in bmp1
void difference(Bmp* bmp1, Bmp* bmp2){

	if (bmp1->getHeight() != bmp2->getHeight() || bmp1->getWidth() != bmp2->getWidth()){
		// Both images must be the same size
		return;
	}

	if (bmp1->getBpp() != bmp2->getBpp()){
		// Both images must have same bpp
		return;
	}

	for (int i = 0; i < bmp1->getHeight(); i++){
		for (int j = 0; j < bmp1->getWidth(); j++){

			// bmp 1 values
			short int r1 = bmp1->getPixelR(i, j);
			short int g1 = bmp1->getPixelG(i, j);
			short int b1 = bmp1->getPixelB(i, j);

			// bmp 2 values
			short int r2 = bmp2->getPixelR(i, j);
			short int g2 = bmp2->getPixelG(i, j);
			short int b2 = bmp2->getPixelB(i, j);

			int rdiff = std::abs(r1 - r2);
			int gdiff = std::abs(g1 - g2);
			int bdiff = std::abs(b1 - b2);

			int diff = rdiff + gdiff + bdiff;

			if (diff > 255) diff = 255;

			bmp1->setPixel(i, j, diff, diff, diff);
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