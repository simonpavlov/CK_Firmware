#include <iostream>
#include <string>
#include <vector>

#include <emul/emulator.h>
#include <UI/UI.h>
#include <UI/test_task.h>

#include <Uni3_Terminus20x10_psf.h>

using namespace std;

int main(){
	emul_init(320, 240);
	atexit(emul_quit);

	UI main_UI(*get_screen_info(), *(new Font(Uni3_Terminus20x10_psf)));

	// main_UI.push(new test_task(main_UI, 10));
	// delete main_UI.top();
	// main_UI.pop();

	vector<string> str_mass;
	str_mass.push_back(string("first"));
	str_mass.push_back(string("second"));
	str_mass.push_back(string("1"));
	str_mass.push_back(string("12"));
	str_mass.push_back(string("123"));
	str_mass.push_back(string("1234"));
	str_mass.push_back(string("12345"));
	str_mass.push_back(string("123456"));
	str_mass.push_back(string("1234567"));
	str_mass.push_back(string("12345678"));
	str_mass.push_back(string("1234567912345679123456791234567912345679"));
	str_mass.push_back(string("last"));


	main_UI.push(new test_task(main_UI, 10, 10));
	main_UI.push(new MessageBox(main_UI, "MESSAGE!"));
	main_UI.push(new MessageBox(main_UI, "123456789101112131415161718192021"));
	main_UI.push(new SelectBox(main_UI, str_mass, NULL));
	// main_UI.push(new test_task(main_UI, 20, 20));
	// main_UI.push(new test_task(main_UI, 30, 30));

	// Test for surface
	// Surface surf_a(17, 20), surf_b(10, 20);
	// for(int i = 0; i <= surf_a.get_height() - surf_b.get_height(); i++){
	// 	for(int j = 0; j <= surf_a.get_width() - surf_b.get_width(); j++){
	// 		surf_a.draw(surf_b, j, i);
	// 	}
	// }

	main_UI.draw();

	while(!main_UI.empty()){ //Зацикливание до тех пор пока не закроем эмулятор
		// Графическая часть
		switch(get_event()){
			case EVT_EXIT:
				cout << "Goodbye!" << endl;
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
