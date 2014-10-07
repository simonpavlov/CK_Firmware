#include <emul/emulator.h>
#include <storage/storage.h>

int main(){
    storage_init();
    storage_clean();

    Password p, *l;

    p.login = "akru";
    p.password = "123";
    save_password(&p);

    p.login = "user1";
    p.password = "154325";
    save_password(&p);

    p.login = "example";
    p.password = "2345232";
    save_password(&p);

    l = load_password("user1");
    printf("Login: %s\nPassword: %s\n", l->login, l->password);
	return 0;
}
