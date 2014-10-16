#include <iostream>

#include <emul/emulator.h>
#include <UI/UI.h>
#include <UI/test_task.h>

#include <Uni3_Terminus20x10_psf.h>

int main(){
	emul_init(320, 240);
	atexit(emul_quit);

	// Surface surf(80, 20);
	UI main_UI(*get_screen_info());

	// main_UI.push(new test_task(main_UI, 10));
	// delete main_UI.top();
	// main_UI.pop();

	main_UI.push(new test_task(main_UI, 10));
	main_UI.push(new test_task(main_UI, 20));
	main_UI.push(new test_task(main_UI, 20));


	main_UI.draw();

	while(!main_UI.empty()){ //Зацикливание до тех пор пока не закроем эмулятор
		// Графическая часть
		switch(get_event()){
			case EVT_EXIT:
				std::cout << "Goodbye!" << std::endl;
				return 0;
				break;

			case EVT_PRESS_UP:
				main_UI.up();
				main_UI.clear_scr();
				main_UI.draw();
				break;

			case EVT_PRESS_DOWN:
				main_UI.down();
				main_UI.clear_scr();
				main_UI.draw();
				break;

			case EVT_PRESS_ENTER:
				main_UI.select();
				main_UI.clear_scr();
				if(!main_UI.empty()) main_UI.draw();
				break;
		}

		refresh_video_buffer();
		SDL_Delay(10);
	}

	std::cout << "Goodbye!" << std::endl;
}
