#include "../UI_Font.h"

#include <cassert>
#include <iostream>

struct psf2{
        //unsigned char magic[4];
        unsigned int version;
        unsigned int header_size;	/* offset of bitmaps in file */
        unsigned int flags;
        unsigned int length;		/* number of glyphs */
        unsigned int char_size;		/* number of bytes for each character */
        unsigned int height, width;	/* max dimensions of glyphs */
        /* char_size = height * ((width + 7) / 8) */
};

const static unsigned char MAGIC_PSF2[4] = {0x72, 0xb5, 0x4a, 0x86};

size_t bread(void *ptr, size_t size, const void *buffer){
	int i, j;

	for(j = 0; j < size; j++){
		*((unsigned char *)ptr + j) = *((unsigned char *)buffer + j);
	}

	return size;
}

Font::Font(const unsigned char *buffer){
	psf2 font_psf2;

	int i;
	for(i = 0; i < 4; i++){
		assert(buffer[i] == MAGIC_PSF2[i]);
	}

	bread(&font_psf2.version,		4, buffer + 4);
	//Добавить чекер
	bread(&font_psf2.header_size,	4, buffer + 8);
	bread(&font_psf2.flags,			4, buffer + 12);
	//Чекер
	bread(&font_psf2.length,		4, buffer + 16);
	bread(&font_psf2.char_size,		4, buffer + 20);
	bread(&font_psf2.height,		4, buffer + 24);
	bread(&font_psf2.width,			4, buffer + 28);

	#ifdef DEBUG
	printf("version:		%u\n", font_psf2.version);
	printf("header_size:	%u\n", font_psf2.header_size);
	printf("flags:			%u\n", font_psf2.flags);
	printf("length:			%u\n", font_psf2.length);
	printf("char_size:		%u\n", font_psf2.char_size);
	printf("height:			%u\n", font_psf2.height);
	printf("width:			%u\n", font_psf2.width);
	#endif

	length		= font_psf2.length;
	char_size	= font_psf2.char_size;
	height		= font_psf2.height;
	width		= font_psf2.width;
	width_byte	= (font_psf2.width + 7) / 8;

	glyphs = (unsigned char *) buffer + font_psf2.header_size;
}

void Font::stdout(){
	int i;
	for(i = 0; i < length; i++){
		std::cout << "Glyphs " << (char) i << "number: " << (int) i << std::endl;

		int y;
		for(y = 0; y < height; y++){

			int k;
			for(k = 0; k < width_byte; k++){

				int x;
				for(x = 7; x >= 0; x--){
					char ch;

					if((*(glyphs + i * char_size + y * width_byte + k) >> x) & 1) ch = '#';
					else ch = '_';

					std::cout << ch;
				}
			}

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

Surface & Font::gen_char_surf(char &ch){
	//TODO: удалить лишнее

	Surface &res_surf = * new Surface(width, height);

	int surf_width_byte, offset_byte;
	unsigned char *cur_byte_surf, *cur_byte_glyph;

	surf_width_byte = res_surf.get_width() / 8;

	cur_byte_surf		= res_surf.get_buffer();
	cur_byte_glyph		= glyphs + ch * char_size;

	int i_line;
	for(i_line = 0; i_line < height; i_line++){
		int i_byte;

		for(i_byte = 0; i_byte < width_byte; i_byte++){
			unsigned char output_byte = *(cur_byte_glyph + i_byte);

			*(cur_byte_surf + i_byte)		|= output_byte;
		}

		cur_byte_surf	+= surf_width_byte;
		cur_byte_glyph	+= width_byte;
	}

	return res_surf;
}

Surface & Font::gen_string_surf(std::string &str){
	// Surface &res_surf = * new Surface(, );
	// return res_surf;
}