#include "../test_task.h"
#include <iostream>
#include <string>
#include <sstream>

#define DEBUG_TEST_TASK

test_task::test_task(UI &stk, int x, int y, Callback *cb):
	Task(stk),
	font(stk.get_default_font()),
	m_callback(cb),
	surf(192, 80)
{
	#ifdef DEBUG_TEST_TASK
	std::cout << "IN test_task::test_task()" << std::endl;
	#endif

	X = x;
	Y = y;
}

test_task::~test_task(){
	#ifdef DEBUG_TEST_TASK
	std::cout << "IN test_task::~test_task()" << std::endl;
	#endif
}

bool test_task::up(){
	#ifdef DEBUG_TEST_TASK
	std::cout << "IN test_task::up()" << std::endl;
	#endif

	Y -= 1;

	return true;
}

bool test_task::down(){
	#ifdef DEBUG_TEST_TASK
	std::cout << "IN test_task::down()" << std::endl;
	#endif

	Y += 1;

	return true;
}

bool test_task::select(){
	#ifdef DEBUG_TEST_TASK
	std::cout << "IN test_task::select()" << std::endl;
	#endif

	if(m_callback){
		m_callback->exec(X);
	}
	else{
		suicide();
	}

	return false;
}

bool test_task::back(){
	#ifdef DEBUG_TEST_TASK
	std::cout << "IN test_task::back()" << std::endl;
	#endif

	return false;
}

Surface & test_task::draw(){
	#ifdef DEBUG_TEST_TASK
	std::cout << "IN test_task::draw()" << std::endl;
	std::cout << Y << std::endl;
	#endif

	surf.clear();

	std::string str_message("IT IS A DEBUG TASK");

	std::stringstream sstr_data;
	sstr_data << Y * 100;
	std::string str_data = sstr_data.str();

	Surface message_surf	= font.gen_surf(str_message, surf.get_width());
	Surface data_surf		= font.gen_surf(str_data);

	surf.draw(message_surf);
	surf.draw(data_surf, 2, 2);

	surf.draw_border();

	Surface new_surf(16, 20);
	new_surf.draw_border();

	surf.draw(new_surf, Y, 23);
	surf.clear(Y + 16, 23, 16, 20);

	// for(int i = 0; i < surf.get_height(); i++){
	// 	for(int j = 0; j < surf.get_width(); j++){
	// 		surf.draw(j, i);
	// 	}
	// }


	return surf;
}
