#include "../UI_Surface.h"

Surface::Surface(unsigned int w, unsigned int h){
	int size = (w * h + 7) / 8;

	buffer		= new unsigned char [size];
	width		= w;
	height		= h;
	buf_size	= size;

	for(int i = 0; i < size; buffer[i++] = 0);
}

Surface::~Surface(){
	delete [] buffer;
}