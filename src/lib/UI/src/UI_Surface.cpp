#include "../UI_Surface.h"

#include <iostream>
#include <cassert>

// Surface(Surface &surf){
// 	width		= surf.width;
// 	height		= surf.height;
// 	buf_size	= surf.buf_size;

// }

Surface::Surface(){
	buffer		= NULL;
	width		= 0;
	height		= 0;
	buf_size	= 0;

	surf_is_my	= false;
}

Surface::Surface(unsigned int w, unsigned int h){
	assert(w % 8 == 0);

	int size = (w * h + 7) / 8;

	buffer		= new unsigned char [size];
	width		= w;
	height		= h;
	buf_size	= size;

	for(int i = 0; i < size; buffer[i++] = 0);

	surf_is_my = true;
}

Surface::~Surface(){
	// std::cout << "IN Surface::~Surface()" << std::endl;

	if(surf_is_my){
		delete [] buffer;
	}
}

void Surface::clear(){
	for(int i = 0; i < buf_size; buffer[i++] = 0);
}

void Surface::draw(Surface &surf, unsigned int x, unsigned int y){
	unsigned char *cur_byte_screen, *cur_byte_surf, offset_byte;
	int screen_width_byte;

	screen_width_byte = width / 8;
	offset_byte = x % 8;

	cur_byte_screen		= buffer + y * screen_width_byte + x / 8;
	cur_byte_surf		= surf.buffer;

	for(int i_line = 0; i_line < surf.height - 1; i_line++){
		for(int i_byte = 0; i_byte < surf.width / 8; i_byte++){
			unsigned char output_byte = *(cur_byte_surf + i_byte);

				*(cur_byte_screen + i_byte)		= *(cur_byte_screen + i_byte) & (0xFF << (8 - offset_byte)) | (output_byte >> offset_byte);
			if(offset_byte)
				*(cur_byte_screen + i_byte + 1)	= *(cur_byte_screen + i_byte + 1) & (0xFF >> offset_byte) | (output_byte << (8 - offset_byte));
		}

		cur_byte_screen	+= screen_width_byte;
		cur_byte_surf	+= surf.width / 8;
	}

	for(int i_byte = 0; i_byte < surf.width / 8 - 1; i_byte++){
		unsigned char output_byte = *(cur_byte_surf + i_byte);

			*(cur_byte_screen + i_byte)		= *(cur_byte_screen + i_byte) & (0xFF << (8 - offset_byte)) | (output_byte >> offset_byte);
		if(offset_byte)
			*(cur_byte_screen + i_byte + 1)	= *(cur_byte_screen + i_byte + 1) & (0xFF >> offset_byte) | (output_byte << (8 - offset_byte));
	}
	cur_byte_screen	+= surf.width / 8 - 1;
	cur_byte_surf	+= surf.width / 8 - 1;

	*cur_byte_screen |= *cur_byte_surf >> offset_byte;

	if(cur_byte_screen != buffer + buf_size - 1){
		*(cur_byte_screen + 1) = *(cur_byte_screen + 1) & (0xFF >> offset_byte) | (*cur_byte_surf << (8 - offset_byte));
	}
}

void Surface::draw(Surface &surf){
	int x, y;
	x = (width	- surf.width)	/ 2;
	y = (height	- surf.height)	/ 2;

	draw(surf, x, y);
}

void Surface::draw(unsigned int x, unsigned int y){
	unsigned char *ned_byte = (buffer + y * width / 8) + x / 8;
	*ned_byte |= 1 << (7 - x % 8);
}


void Surface::draw(unsigned int x, unsigned int y, unsigned int w, unsigned int h){
	int i;

	for(i = x; i <= x + w; i++){
		draw(i, y);
		draw(i, y + h);
	}

	for(i = y + 1; i < y + h; i++){
		draw(x, i);
		draw(x + w, i);
	}
}

void Surface::draw_border(){
	unsigned char * cur_byte_surf;
	int i;

	cur_byte_surf = buffer + width / 8;
	for(i = 1; i < height - 1; i++){
		*cur_byte_surf						|= 128;
		*(cur_byte_surf + width / 8 - 1)	|= 1;

		cur_byte_surf += width / 8;
	}

	for (i = 0; i < width / 8; i++){
		*(buffer + i)			= 255;
		*(cur_byte_surf + i)	= 255;
	}
}
