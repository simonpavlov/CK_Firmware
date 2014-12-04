#include <emul/emulator.h>

#include <stdio.h>

int main(){
	if(emul_init(STORAGE_INIT) != ALL_RIGHT){
		printf("FAIL\n");
		return 0;
	}

	unsigned char *buf = malloc(512);

	storage_write("HELLO", 0, 6);
	storage_write("HELLO", 1, 6);
	storage_write("HELLO", 2, 6);
	storage_write("!!!", 3, 4);
	storage_write("HELLO", 4, 6);

	storage_read(buf, 3, 512);
	int i;
	for(i = 0; i < 512; i++){
		if(i % 16 == 0 && i != 0){
			printf("\n");
		}

		printf(" %4X", buf[i]);
	}

	return 0;
}