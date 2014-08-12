#ifndef CKF_FONT
#define CKF_FONT

#include <stdlib.h>

typedef struct{
    unsigned int length;        //количество символов
    unsigned int char_size;     //количество байт на символ
    unsigned int height, width; //высота, ширина символов
    unsigned int width_byte;	//байтов на строку символа
    unsigned char *glyphs;		//ссылка на начало карт символов
} CKF_Font;

/*
Считывает шрифт из файла типа psf v2 и возврашает ссылку на структуру font.
В случае неудачи вернёт NULL
*/
CKF_Font * ffont_init(const char *file_name);

/*
Считывает шрифт psf v2 из буфера buffer и возврашает ссылку на структуру font.
В случае неудачи вернёт NULL
*/
CKF_Font * bfont_init(const char *buffer);

/*
Выводит символ ch, используя шрифт font. Верхний левый угол по координатам x, y.
!!! Нет проверки на выход символа за пределы экрана.
*/
void draw_char(CKF_Font *font, unsigned char ch, int x, int y);

/*
Выводит максимальное количесто символов из строки str, используя шрифт font.
Верхний левый угол по координатам x, y.
!!!Обрабатывается выход только за правую границу.
*/
size_t draw_string(CKF_Font *font, const char *str, int x, int y);

/*
Функция для отладки, выводит шрифт в stdout
*/
void font_stdout(CKF_Font *font);

#endif