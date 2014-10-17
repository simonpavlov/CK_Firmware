#include "../test_task.h"
#include <iostream>
#include <string>

test_task::test_task(UI &stk, int x, int y): Task(stk), surf(320, 240){
	std::cout << "IN test_task::test_task()" << std::endl;
	// my_stack = &stk;
	X = x;
	Y = y;
}

test_task::~test_task(){
	std::cout << "IN test_task::~test_task()" << std::endl;
}

void test_task::up(){
	std::cout << "IN test_task::up()" << std::endl;
	Y--;
}

void test_task::down(){
	std::cout << "IN test_task::down()" << std::endl;
	Y++;
}

void test_task::select(){
	std::cout << "IN test_task::select()" << std::endl;
	suicide();
}

Surface & test_task::draw(){
	surf.clear();

	std::cout << "IN test_task::draw()" << std::endl;
	std::cout << Y << std::endl;

	#include <Uni3_Terminus20x10_psf.h>
	Font font1(Uni3_Terminus20x10_psf);
	// std::cout << "font: " << font1.get_width() << "x" << font1.get_height() << std::endl;

	std::string str("Hello!");
	Surface message_surf = font1.gen_surf(str, 10);
	message_surf.draw_border();
	surf.draw(message_surf, X, Y);

	surf.draw(7, 2, 3, 6);

	surf.draw_border();

	return surf;
}
