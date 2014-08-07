#ifndef FW_FONT
#define FW_FONT

struct{
    unsigned int length;        //количество символов
    unsigned int charsize;      //количество байт на символ
    unsigned int height, width; //высота, ширина символов
    unsigned char *glyphs;		//ссылка на начало карт символов
}FW_Font;

typedef enum{
	NORMAL = 0,	//Всё в порядке
	ERROR_OPEN,		//Файл не открыт
	ERROR_FILE,		//Некорректный файл
	ERROR_MEMORY	//Ошибка памяти
} FontInitStatus;

/*
Считывает шрифт из файла типа psf v2 и возврашает ссылку на структуру font.
В случае неудачи вернёт NULL
*/
FontInitStatus font_init(const char *file_name);

/*
Завершение работы со шрифтами
*/
void font_quit();

/*
Выводит символ ch, используя шрифт font. Верхний левый угол по координатам x, y.
*/
void draw_char(char ch, int x, int y);

/*
Функция для отладки, выводит шрифт в stdout
*/
void font_stdout();

#endif