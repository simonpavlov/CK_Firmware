#include <iostream>
#include <string>
#include <vector>

#include <emul/emulator.h>
#include <UI/UI.h>
#include <UI/test_task.h>

#include <Uni3_Terminus20x10_psf.h>

using namespace std;

class message_callback: public MessageBox::Callback{
	public:
		void exec(){
			cout << "ok" << endl;
		}
};

class question_callback: public QuestionBox::Callback{
	public:
		void exec(bool answer){
			cout << "answer: ";
			if(answer) cout << "TRUE" << endl;
			else cout << "FALSE" << endl;
		}
};

class select_callback: public SelectBox::Callback{
	public:
		void exec(int number){
			cout << "number: " << number << endl;
		}
};

class input_callback: public InputBox::Callback{
	public:
		void exec(const string &str){
			cout << "string: " << str << endl;
		}
};

class test_callback: public test_task::Callback{
	public:
		void exec(int x){
			cout << "X: " << x << endl;
		}
};

int main(){
	set_screen_res(320, 240);
	emul_init(VIDEO_INIT);
	atexit(emul_quit);

	Font f(Uni3_Terminus20x10_psf);
	// f.stdout();
	UI main_UI(*get_screen_info(), f);

	vector<string> str_mass;

	test_callback		cb_test_task;
	message_callback	cb_message_box;
	question_callback	cb_question_box;
	select_callback		cb_select_box;
	input_callback		cb_input_box;

	str_mass.push_back(string(" 1 The wondrous moment of our meeting..."));
	str_mass.push_back(string(" 2 I well remember you appear"));
	str_mass.push_back(string(" 3 Before me like a vision fleeting,"));
	str_mass.push_back(string(" 4 A beauty's angel pure and clear."));
	str_mass.push_back(string(" 5 In hopeless ennui surrounding"));
	str_mass.push_back(string(" 6 The worldly bustle, to my ear"));
	str_mass.push_back(string(" 7 For long your tender voice kept sounding,"));
	str_mass.push_back(string(" 8 For long in dreams came features dear."));
	str_mass.push_back(string(" 9 Time passed. Unruly storms confounded"));
	str_mass.push_back(string("10 Old dreams, and I from year to year"));
	str_mass.push_back(string("11 Forgot how tender you had sounded,"));
	str_mass.push_back(string("12 Your heavenly features once so dear."));
	str_mass.push_back(string("13 My backwoods days dragged slow and quiet -"));
	str_mass.push_back(string("14 Dull fence around, dark vault above -"));
	str_mass.push_back(string("15 Devoid of God and uninspired,"));
	str_mass.push_back(string("16 Devoid of tears, of fire, of love."));
	str_mass.push_back(string("17 Sleep from my soul began retreating,"));
	str_mass.push_back(string("18 And here you once again appear"));
	str_mass.push_back(string("19 Before me like a vision fleeting,"));
	str_mass.push_back(string("20 A beauty's angel pure and clear."));

	main_UI.push(new MessageBox(main_UI, "This is MessageBox", &cb_message_box));
	main_UI.push(new QuestionBox(main_UI, "This is QuestionBox?", &cb_question_box));
	main_UI.push(new SelectBox(main_UI, str_mass, &cb_select_box));
	main_UI.push(new InputBox(main_UI, "This is InputBox:", &cb_input_box));
	main_UI.push(new test_task(main_UI, 10, 10, &cb_test_task));

	// Test for surface
	// Surface surf_a(17, 20), surf_b(10, 20);
	// for(int i = 0; i <= surf_a.get_height() - surf_b.get_height(); i++){
	// 	for(int j = 0; j <= surf_a.get_width() - surf_b.get_width(); j++){
	// 		surf_a.draw(surf_b, j, i);
	// 	}
	// }

	main_UI.draw();

	while(!main_UI.empty()){
		// Графическая часть
		switch(get_event()){
			case EVT_EXIT:
				cout << "Goodbye!" << endl;
				return 0;
				break;

			case EVT_PRESS_UP:
				main_UI.up();
				break;

			case EVT_PRESS_DOWN:
				main_UI.down();
				break;

			case EVT_PRESS_ENTER:
				cout << "main_UI.select()" << endl;
				main_UI.select();
				cout << "OK" << endl;
				break;

			case EVT_PRESS_BACK:
				main_UI.back();
				break;
		}

		if(main_UI.empty()){
			break;
		}

		main_UI.draw();
		SDL_Delay(10);
	}

	std::cout << "Goodbye!" << std::endl;
}
