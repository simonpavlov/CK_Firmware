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

void Surface::clear(){
	for(int i = 0; i < buf_size; buffer[i++] = 0);
}

void Surface::draw_surf(Surface &surf, unsigned int x, unsigned int y){
	int screen_width_byte, offset_byte;
	unsigned char *cur_byte_screen, *cur_byte_surf;

	screen_width_byte = width / 8;
	offset_byte = x % 8;

	cur_byte_screen		= buffer + y * screen_width_byte + x / 8;
	cur_byte_surf		= surf.buffer;

	int i_line;
	for(i_line = 0; i_line < surf.height; i_line++){
		int i_byte;
		unsigned char output_byte;

		for(i_byte = 0; i_byte < surf.width / 8; i_byte++){
			output_byte = *(cur_byte_surf + i_byte);

			*(cur_byte_screen + i_byte)		|= output_byte >> offset_byte;
			// FIXME: проблема в следующей строке мы поподаем в бит за пределами нашей поверхности,
			// когда нижние правыйе уголы поверхностей совпадют
			*(cur_byte_screen + i_byte + 1)	|= output_byte << (8 - offset_byte);
		}

		cur_byte_screen	+= screen_width_byte;
		cur_byte_surf	+= surf.width / 8;
	}

	// output_byte = *(cur_byte_surf + i_byte + 1);
	// *(cur_byte_screen + i_byte) |= output_byte >> offset_byte;
}

void Surface::draw_pix(unsigned int x, unsigned int y){
	unsigned char *ned_byte = (buffer + y * width / 8) + x / 8;
	*ned_byte |= 1 << (7 - x % 8);
}


void Surface::draw_pargram(unsigned int x, unsigned int y, unsigned int w, unsigned int h){
	int i;

	for(i = x; i <= x + w; i++){
		draw_pix(i, y);
		draw_pix(i, y + h);
	}

	for(i = y + 1; i < y + h; i++){
		draw_pix(x, i);
		draw_pix(x + w, i);
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
