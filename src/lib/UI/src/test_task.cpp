#include "../test_task.h"
#include <iostream>
#include <string>
#include <sstream>

test_task::test_task(UI &stk, int x, int y): Task(stk), font(stk.get_default_font()), surf(192, 80){
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

void test_task::up(){
	#ifdef DEBUG_TEST_TASK
	std::cout << "IN test_task::up()" << std::endl;
	#endif

	Y--;
}

void test_task::down(){
	#ifdef DEBUG_TEST_TASK
	std::cout << "IN test_task::down()" << std::endl;
	#endif

	Y++;
}

void test_task::select(){
	#ifdef DEBUG_TEST_TASK
	std::cout << "IN test_task::select()" << std::endl;
	#endif

	suicide();
}

Surface & test_task::draw(){
	#ifdef DEBUG_TEST_TASK
	std::cout << "IN test_task::draw()" << std::endl;
	std::cout << Y << std::endl;
	#endif

	surf.clear();

	std::string str_message("IT IS A LAST TASK");

	std::stringstream sstr_data;
	sstr_data << Y;
	std::string str_data = sstr_data.str();

	Surface message_surf	= font.gen_surf(str_message, surf.get_width());
	Surface data_surf		= font.gen_surf(str_data);

	surf.draw(message_surf);
	surf.draw(data_surf, 2, 2);

	surf.draw_border();

	return surf;
}
