#include "../UI_Surface.h"

#include <iostream>

Surface::Surface(ScreenInfo &scr){
	width		= scr.width;
	height		= scr.height;
	buf_size	= scr.len_byte;
	buffer		= (unsigned char *) scr.buffer;

	memory_is_my = false;
}

Surface::Surface(unsigned int w, unsigned int h){
	int size = (w * h + 7) / 8;

	buffer		= new unsigned char [size];
	width		= w;
	height		= h;
	buf_size	= size;

	for(int i = 0; i < size; buffer[i++] = 0);

	memory_is_my = true;
}

Surface::~Surface(){
	if(memory_is_my){
		delete [] buffer;
	}
}