#include "Thread.h"

Thread::Thread(std::function<void()> run){
	this->run = run;
}

Thread::~Thread(){
	delete &this->run;
}

DWORD ThreadProc(LPVOID lpdwThreadParam){
	Thread* p = static_cast<Thread*>(lpdwThreadParam);
	p->run();
	return 0;
}

void Thread::start(){
	DWORD dwThreadId;
	if (CreateThread(NULL, //Choose default security
		0, //Default stack size
		(LPTHREAD_START_ROUTINE)&ThreadProc,
		//Routine to execute
		(LPVOID)this, //Thread parameter
		0, //Immediately run the thread
		&dwThreadId //Thread Id
		) == NULL)
	{
		printf("Error Creating Thread\n");
	}
}