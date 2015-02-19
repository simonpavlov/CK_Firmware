#include <Storage/ff.h>
#include <iostream>
#include <emul/emulator.h>

using namespace std;

int main(){
	emul_init(STORAGE_SYS);

	FATFS fs;			/* Рабочая область (file system object) для логических дисков */
	FIL fsrc, fdst;		/* файловые объекты */
	BYTE buffer[4096];	/* буфер для копирования данных фала */
	FRESULT res;		/* общий код возврата функций FatFs */
	UINT br, bw;		/* счетчик чтения/записи файла */

	/* Регистрирование рабочей области для каждого тома (всегда закончится успешно,
 независимо от состояния диска) */
	cout << "Trying f_mount(&fs, \"\", 0)" << endl;
	if(f_mount(&fs, "", 0) != FR_OK){
		cerr << "FAIL" << endl;
		return 1;
	}
	cout << "OK" << endl;

	// Отформатировать пространство
	/*
	cout << "Trying mkfs" << endl;
	if(f_mkfs("", 0, 0) != FR_OK){
		cerr << "FAIL" << endl;
		return 1;
	}
	cout << "OK" << endl;
	*/

	/* Открыть файл источника на диске 0 */
	cout << "Trying f_open(&fsrc, \"Hello.txt\", FA_OPEN_EXISTING | FA_READ)" << endl;
	res = f_open(&fsrc, "Hello.txt", FA_OPEN_EXISTING | FA_READ);
	if (res) cout << "Hello.txt not opend: " << res << endl;
	else cout << "OK" << endl;

	/* Открыть файл-копию на диске 0 */
	cout << "Trying f_open(&fdst, \"2Hello.txt\", FA_CREATE_ALWAYS | FA_WRITE)" << endl;
	res = f_open(&fdst, "2Hello.txt", FA_CREATE_ALWAYS | FA_WRITE);
	if (res) cout << "2Hello.txt not created: " << res << endl;
	else cout << "OK" << endl;

	// Записать в файл буффер в 15 байт
	/*
	f_write(&fdst, buffer, 15, &bw);
	cout << "bw: " << bw << endl;
	*/
	
	// Прочитать из файла в буффер и вывисти на экран как символы
	/*
	f_read(&fsrc, buffer, sizeof(buffer), &br);
	for(UINT i = 0; i < br; cout << (char)buffer[i++]);
	cout << endl;
	*/

	/* Копирование данных из файла-источника в файл-копию */
	for (;;) {
		res = f_read(&fsrc, buffer, sizeof(buffer), &br);	// Чтение куска из файла src
		if (res || br == 0) break;							// ошибка или eof (конец данных файла)
		res = f_write(&fdst, buffer, br, &bw);				// Запись куска в файл dst
		if (res || bw < br) break;							// ошибка, если диск переполнен
	}

	/* Закрытие открытых файлов */
	f_close(&fsrc);
	f_close(&fdst);

	/* Дерегистрация и отмена рабочих областей */
	f_mount(NULL, "", 0);

	emul_quit(NETWORK_SYS);
}
