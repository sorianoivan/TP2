#include "BlockingQueue.h"

void BlockingQueue::push(const Recurso recurso) {
    std::unique_lock<std::mutex> lock(mtx);
    queue.push(recurso);
    cond_var.notify_all();
}

Recurso BlockingQueue::pop() {
    std::unique_lock<std::mutex> lock(mtx);

    while (queue.empty()){
        cond_var.wait(lock);
    }
    Recurso recurso = queue.front();
    queue.pop();
    return recurso;
}

bool BlockingQueue::canPop() {
    return !(queue.empty() && done_pushing);
}

void BlockingQueue::close() {
    std::unique_lock<std::mutex> lock(mtx);
    done_pushing = true;
    cond_var.notify_all();
}

BlockingQueue::~BlockingQueue() {
    //do nothing
}

