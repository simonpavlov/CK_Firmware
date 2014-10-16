#include "../test_task.h"
#include <iostream>

test_task::test_task(UI &stk, int x): Task(stk), surf(160, 120){
	std::cout << "IN test_task::test_task()" << std::endl;
	// my_stack = &stk;
	X = x;
}

test_task::~test_task(){
	std::cout << "IN test_task::~test_task()" << std::endl;
}

void test_task::up(){
	std::cout << "IN test_task::up()" << std::endl;
	X--;
}

void test_task::down(){
	std::cout << "IN test_task::down()" << std::endl;
	X++;
}

void test_task::select(){
	std::cout << "IN test_task::select()" << std::endl;
	suicide();
}

Surface & test_task::draw(){
	surf.clear();

	std::cout << "IN test_task::draw()" << std::endl;
	std::cout << X << std::endl;

	#include <Uni3_Terminus20x10_psf.h>
	Font font1((const unsigned char *) Uni3_Terminus20x10_psf);
	char ch_a = 'a';
	surf.draw_surf(font1.gen_char_surf(ch_a), 10, X);

	surf.draw_pix(2, 2);
	surf.draw_pix(3, 3);
	surf.draw_pix(4, 4);
	surf.draw_pix(5, 5);

	surf.draw_pargram(7, 2, 3, 6);

	surf.draw_border();

	return surf;
}
