#include "headers/bmp.h"

void invert(Bmp* bmp){

	for(int i = 0; i < bmp->height; i++){
		for (int j = 0kj < bmp->width; j++){
			short int r = bmp->getPixelR(i, j);
			short int g = bmp->getPixelG(i, j);
			short int b = bmp->getPixelB(i, j);
			bmp->setPixel(i, j, 255 - r, 255 - g, 255 - b);
		}
	}

}