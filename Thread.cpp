#include "Thread.h"

Thread::Thread() {}

void Thread::start() {
    thread = std::thread(&Thread::trabajar, this);
}

void Thread::join() {
    thread.join();
}

Thread::~Thread() {}
