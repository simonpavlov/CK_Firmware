#ifndef CKF_FONT
#define CKF_FONT

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
CKF_Font * font_init(const char *file_name);

/*
Выводит символ ch, используя шрифт font. Верхний левый угол по координатам x, y.
!!! Нет проверки на выход символа за пределы экрана.
*/
void draw_char(CKF_Font *font, char ch, int x, int y);

/*
Функция для отладки, выводит шрифт в stdout
*/
void font_stdout(CKF_Font *font);

#endif