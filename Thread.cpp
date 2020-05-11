#include "Thread.h"

Thread::Thread() {
    //do nothing
}

void Thread::start() {
    thread = std::thread(&Thread::work, this);
}

Thread::~Thread() {
    //do nothing
}

void Thread::join() {
    thread.join();
}

