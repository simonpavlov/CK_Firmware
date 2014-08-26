#include "../font.h"
#include <stdio.h>
#include <string.h>
#include <emul/emulator.h>

typedef struct{
        //unsigned char magic[4];
        unsigned int version;
        unsigned int header_size;	/* offset of bitmaps in file */
        unsigned int flags;
        unsigned int length;		/* number of glyphs */
        unsigned int char_size;		/* number of bytes for each character */
        unsigned int height, width;	/* max dimensions of glyphs */
        /* char_size = height * ((width + 7) / 8) */
}psf2;

char psf2_magic[4] = {0x72, 0xb5, 0x4a, 0x86};

extern ScreenInfo *MenuScreen;

size_t bread(void *ptr, size_t size, const void *buffer){
	int i, j;

	for(j = 0; j < size; j++){
		*((unsigned char *)ptr + j) = *((unsigned char *)buffer + j);
	}

	return size;
}

//TODO: инициализация из BDF шрифта
CKF_Font * ffont_init(const char *file_name){
	FILE * f_in;
	CKF_Font * font;
	psf2 font_psf2;

	f_in = fopen(file_name, "rb");
	if(!f_in) return NULL;

	font = malloc(sizeof(CKF_Font));
	if(!font) return NULL;

	char ch;
	int i;
	for(i = 0; i < 4; i++){
		ch = getc(f_in);
		if(ch != psf2_magic[i]){
			return NULL;
		}
	}


	fread(&font_psf2.version, 4, 1, f_in);
	//Добавить чекер
	fread(&font_psf2.header_size, 4, 1, f_in);
	fread(&font_psf2.flags, 4, 1, f_in);
	//Чекер
	fread(&font_psf2.length, 4, 1, f_in);
	fread(&font_psf2.char_size, 4, 1, f_in);
	fread(&font_psf2.height, 4, 1, f_in);
	fread(&font_psf2.width, 4, 1, f_in);

	#ifdef DEBUG
	printf("version:		%u\n", font_psf2.version);
	printf("header_size:	%u\n", font_psf2.header_size);
	printf("flags:			%u\n", font_psf2.flags);
	printf("length:			%u\n", font_psf2.length);
	printf("char_size:		%u\n", font_psf2.char_size);
	printf("height:			%u\n", font_psf2.height);
	printf("width:			%u\n", font_psf2.width);
	#endif

	font->length		= font_psf2.length;
	font->char_size		= font_psf2.char_size;
	font->height		= font_psf2.height;
	font->width			= font_psf2.width;
	font->width_byte	= (font_psf2.width + 7) / 8;

	font->glyphs = malloc(font_psf2.char_size * font_psf2.length);
	if(!font->glyphs) return NULL;

	fread(font->glyphs, font_psf2.char_size, font_psf2.length, f_in);
	//Ещё чекер

	fclose(f_in);

	return font;
}

CKF_Font * bfont_init(const char *buffer){
	CKF_Font * font;
	psf2 font_psf2;

	font = malloc(sizeof(CKF_Font));
	if(!font) return NULL;

	int i;
	for(i = 0; i < 4; i++){
		if(buffer[i] != psf2_magic[i]){
			return NULL;
		}
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

	font->length		= font_psf2.length;
	font->char_size		= font_psf2.char_size;
	font->height		= font_psf2.height;
	font->width			= font_psf2.width;
	font->width_byte	= (font_psf2.width + 7) / 8;

	font->glyphs = (unsigned char *) buffer + font_psf2.header_size;

	return font;
}

//TODO: проверка на выход за границцы экрана
void draw_char(CKF_Font *font, unsigned char ch, int x, int y){
	CKF_Font local_font;
	int screen_width_byte, offset_byte;
	unsigned char *cur_byte_screen, *cur_byte_glyph;

	local_font = *font;

	screen_width_byte = MenuScreen->width / 8;
	offset_byte = x % 8;

	cur_byte_screen		= MenuScreen->buffer + y * screen_width_byte + x / 8;
	cur_byte_glyph		= local_font.glyphs + ch * local_font.char_size;

	int i_line;
	for(i_line = 0; i_line < local_font.height; i_line++){
		int i_byte;

		for(i_byte = 0; i_byte < local_font.width_byte; i_byte++){
			unsigned char output_byte = *(cur_byte_glyph + i_byte);

			*(cur_byte_screen + i_byte)		|= output_byte >> offset_byte;
			*(cur_byte_screen + i_byte + 1)	|= output_byte << (8 - offset_byte);
		}

		cur_byte_screen += screen_width_byte;
		cur_byte_glyph	+= local_font.width_byte;
	}
}

//TODO: проверка на выход за границцы экрана
size_t draw_string(CKF_Font *font, const char *str, int x, int y){
	int max_ch, len_str, i, max_i, font_width;

	font_width = font->width;

	max_ch = (MenuScreen->width - x) / font_width;
	len_str = strlen(str);
	if(max_ch < len_str) max_i = max_ch;
	else max_i = len_str;

	for(i = 0; i < max_i; i++){
		draw_char(font, str[i], x + i * font_width, y);
	}

	return max_i;
}

void font_stdout(CKF_Font *font){
	int i;
	for(i = 0; i < font->length; i++){
		printf("Glyphs %c number %4d:\n", i, i);

		int y;
		for(y = 0; y < font->height; y++){

			int k;
			for(k = 0; k < font->width_byte; k++){

				int x;
				for(x = 7; x >= 0; x--){
					char ch;

					if((*(font->glyphs + i * font->char_size + y * font->width_byte + k) >> x) & 1) ch = '#';
					else ch = '_';

					putchar(ch);
				}
			}

			printf("\n");
		}
		printf("\n");
	}
}
