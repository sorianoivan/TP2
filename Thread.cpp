#include "Thread.h"

Thread::Thread() {}

void Thread::start() {
    thread = std::thread(&Thread::work, this);
}

void Thread::join() {
    thread.join();
}

Thread::~Thread() {}
