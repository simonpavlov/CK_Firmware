#include "../font.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int revers_read_4_byte(FILE *f_in);

typedef struct{
        //unsigned char magic[4];
        unsigned int version;
        unsigned int headersize;    /* offset of bitmaps in file */
        unsigned int flags;
        unsigned int length;        /* number of glyphs */
        unsigned int charsize;      /* number of bytes for each character */
        unsigned int height, width; /* max dimensions of glyphs */
        /* charsize = height * ((width + 7) / 8) */
}psf2;

FontInitStatus font_init(const char *file_name){
	char psf2_magic[4] = {0x72, 0xb5, 0x4a, 0x86};

	FILE * f_in;
	psf2 font_psf2;

	f_in = fopen(file_name, "rb");
	if(!f_in) return ERROR_OPEN;
	
	char ch;
	int i;
	for(i = 0; i < 4; i++){
		ch = getc(f_in);
		if(ch != psf2_magic[i]){
			return ERROR_FILE;
		}
	}

	fread(&font_psf2.version, 4, 1, f_in);
	//Добавить чекер
	fread(&font_psf2.headersize, 4, 1, f_in);
	fread(&font_psf2.flags, 4, 1, f_in);
	//Чекер
	fread(&font_psf2.length, 4, 1, f_in);
	fread(&font_psf2.charsize, 4, 1, f_in);
	fread(&font_psf2.height, 4, 1, f_in);
	fread(&font_psf2.width, 4, 1, f_in);

#ifdef DEBUG
	printf("version:	%u\n", font_psf2.version);
	printf("headersize:	%u\n", font_psf2.headersize);
	printf("flags:		%u\n", font_psf2.flags);
	printf("length:		%u\n", font_psf2.length);
	printf("charsize:	%u\n", font_psf2.charsize);
	printf("height:		%u\n", font_psf2.height);
	printf("width:		%u\n", font_psf2.width);
#endif

	FW_Font.length		= font_psf2.length;
	FW_Font.charsize	= font_psf2.charsize;
	FW_Font.height		= font_psf2.height;
	FW_Font.width		= font_psf2.width;

	FW_Font.glyphs = malloc(FW_Font.charsize * FW_Font.length);
	if(!FW_Font.glyphs) return ERROR_MEMORY;

	fread(FW_Font.glyphs, FW_Font.charsize, FW_Font.length, f_in);
	//Ещё чекер

	fclose(f_in);

	return NORMAL;
}

void font_quit(){
	free(FW_Font.glyphs);
}

void draw_char(char ch, int x, int y){
	extern int FW_ScreenWidth;
	extern int FW_ScreenHeght;
	extern char *FW_VideoBuffer;

	int width_byte, offset_byte;

	width_byte = FW_ScreenWidth / 8;
	offset_byte = x % 8;

	int i;
	if(offset_byte){
		printf("offset_byte: %d\n", offset_byte);
	}
	else{
		for(i = 0; i < FW_Font.height; i++){
			int k;
			for(k = 0; k < FW_Font.width / 8; k++){
				*(FW_VideoBuffer + i * width_byte + x / 8 + k) =
				*(FW_Font.glyphs + ch * FW_Font.charsize + i * FW_Font.width / 8 + k);
			}
		}
	}

}

void font_stdout(){
	int i;
	for(i = 0; i < FW_Font.length; i++){
		printf("Glyphs number:%4d\n", i);

		int y;
		for(y = 0; y < FW_Font.height; y++){

			int k, width_byte;
			width_byte = (FW_Font.width + 7) / 8;
			for(k = 0; k < width_byte; k++){

				int x;
				for(x = 7; x >= 0; x--){
					char ch;

					if((*(FW_Font.glyphs + i * FW_Font.charsize + y * width_byte + k)
						>> x) & 1) ch = '#';
					else ch = '_';

					putchar(ch);
				}
			}

			printf("\n");
		}
		printf("\n");
	}
}
