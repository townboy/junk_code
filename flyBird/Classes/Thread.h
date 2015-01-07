#pragma once

#include <functional>
#include <windows.h>

class Thread{

public:
	Thread(std::function<void()> run);

	~Thread();

	void start();

	std::function<void()> run;

};