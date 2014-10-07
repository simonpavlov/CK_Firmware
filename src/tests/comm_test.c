#include <emul/emulator.h>
#include <IO/serial.h>
#include <app/app.h>

int main(){
    network_init();
    storage_init();
    application();
    return 0;
}
