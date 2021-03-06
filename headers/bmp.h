#ifndef BMP
#define BMP

#include <iostream>
#include <vector>

class Bmp{
	std::vector<char> header;
	std::vector< std::vector<char> > pixels;
	std::vector<char> footer;
	int size, width, height, padding, rowsize;
	short int bpp;
	public:
		Bmp(char filedata[], int size) { 

			this->size = size;

			// Check it is a bmp
			if(filedata[0]=='B'&&filedata[1]=='M'){

				// Parse width, height and bpp info
				width = *((unsigned int*)&filedata[18]);
				height = *((unsigned int*)&filedata[22]);
				bpp = *((short int*)&filedata[28]);

				int pixoff = *((unsigned int*)&filedata[10]);
				int headersize = *((unsigned int*)&filedata[14]);				
				unsigned int imgsize;

				std::cout << "Size of file: " << size << std::endl;
				std::cout << "Pixel offset: " << pixoff << std::endl;
				std::cout << "Width: " << width << std::endl;
				std::cout << "Height: " << height << std::endl;
				std::cout << "Bits per pixel: " << bpp << std::endl;

				// Process 24 bpp
				if(bpp==24){
					padding = (width*3)%4;
					rowsize = (3*width) + padding;
					imgsize = rowsize*height;
					std::cout << "Padding: " << padding << std::endl;
					std::cout << "Row size: " << rowsize << std::endl;
				}

				// Store bmp bytes in respective vectors
				header.insert(header.begin(),filedata,filedata+pixoff);
				pixels.resize(height);
				for(int i=0;i<height;i++){
					pixels.at(i).insert(pixels.at(i).begin(),
						filedata+pixoff+(i*rowsize)+(i*padding),filedata+pixoff+((i+1)*rowsize)+((i+1)*padding));
				}
				footer.insert(footer.begin(),filedata+pixoff+imgsize,filedata+size);

			}

		}
		//TODO: Copy constructor, destructor
		void saveCopy(std::string filename);
		const short int getPixelR(int x, int y);
		const short int getPixelG(int x, int y);
		const short int getPixelB(int x, int y);
		void setPixel(int x, int y, short int r, short int g, short int b);

		// Getters/setters
		const int getSize() { return size; }
		const int getWidth() { return width; }
		const int getHeight() { return height; }
		const int getBpp() { return bpp;  }

};

#endif