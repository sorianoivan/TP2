#ifndef _BLOCKINGQUEUE_H
#define _BLOCKINGQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

#include "Recursos.h"


class BlockingQueue {
private:
    bool done_pushing;
    std::mutex mtx;
    std::condition_variable cond_var;
    std::queue<Recurso> queue;

public:
    BlockingQueue() : done_pushing(false) {}
    void push(const Recurso recurso);
    Recurso pop();
    bool canPop();
    void close();
    ~BlockingQueue();
};


#endif //_BLOCKINGQUEUE_H
