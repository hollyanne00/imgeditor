#include <iostream>
#include <fstream>
#include <string>

int loadpixels(int argc, char *argv[]){

	std::ifstream ifs;
	std::string line;
	std::streampos size;
	std::ofstream ofs;

	if (argc < 2) {
		std::cout << "Usage: <file>" << std::endl; 
		return 0; 
	}

	std::string filename = (std::string)argv[1];

	std::cout << "Opening file " << filename << std::endl;

	ifs.open(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
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

		unsigned int size = *((unsigned int*)&bytes[2]);
		unsigned int pixoff = *((unsigned int*)&bytes[10]);
		unsigned int headsz = *((unsigned int*)&bytes[14]);
		unsigned int width = *((unsigned int*)&bytes[18]);
		unsigned int height = *((unsigned int*)&bytes[22]);
		short int planes = *((short int*)&bytes[26]);
		short int bpp = *((short int*)&bytes[28]);
		unsigned int compression = *((unsigned int*)&bytes[30]);
		unsigned int imgsize = *((unsigned int*)&bytes[34]);
		unsigned int padding;
		unsigned int rowsize; 

		// If it is a BMP
		if(bytes[0]=='B'&&bytes[1]=='M'){

			// Output file information
			std::cout << "Size of file: " << size << std::endl;
			std::cout << "Pixel offset: " << pixoff << std::endl;
			std::cout << "Header size: " << headsz << std::endl;
			std::cout << "Width: " << width << std::endl;
			std::cout << "Height: " << height << std::endl;
			std::cout << "Number of colour planes: " << planes << std::endl;
			std::cout << "Bits per pixel: " << bpp << std::endl;
			std::cout << "Compression method: " << compression << std::endl;
			std::cout << "Image size: " << imgsize << std::endl;

			// Process 24 bpp
			if(bpp==24){
				padding = (width*3)%4;
				rowsize = (3*width) + padding;
				std::cout << "Padding: " << padding << std::endl;
				std::cout << "Row size: " << rowsize << std::endl;

			}

			// Output an inverted copy of the image
			std::string ifilename = "inverted_" + filename;
			ofs.open(ifilename.c_str(), std::ios::out | std::ios::binary);
			int k = 0; 
			while(k<pixoff){
				ofs << bytes[k];
				k++;
			}
			int i = 0;
			int p = pixoff;
			while(i<height){
				int j = 0;
				while(j<width){
					ofs << (char) (255-(unsigned short int)(bytes[p+(j*3)]&255));
					ofs << (char) (255-(unsigned short int)(bytes[p+(j*3)+1]&255));
					ofs << (char) (255-(unsigned short int)(bytes[p+(j*3)+2]&255));
					j++;
				}
				p = p + rowsize;
				i++;
			}			
			k = k+(rowsize*3*height);
			while(k<size){
				ofs << bytes[i];
				k++;
			}
			ofs.close();

		}

		ifs.close();

	}

	return 0;
}