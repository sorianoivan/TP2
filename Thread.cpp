#include "Thread.h"

Thread::Thread() {
    //ver que hacer con los constructores q no hacen nada
}

void Thread::start() {
    thread = std::thread(&Thread::work, this);
}

void Thread::join() {
    thread.join();
}

