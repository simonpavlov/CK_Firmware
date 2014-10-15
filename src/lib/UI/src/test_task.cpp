#include "../test_task.h"
#include <iostream>

test_task::test_task(UI &stk, int x): Task(stk){
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

void test_task::draw(){
	std::cout << "IN test_task::draw()" << std::endl;
	std::cout << X << std::endl;
}
