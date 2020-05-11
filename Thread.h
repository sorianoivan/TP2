#ifndef TP2_THREAD_H
#define TP2_THREAD_H

#include <thread>

class Thread {
private:
    std::thread thread;
public:
    Thread();
    void start();
    void join();
    virtual void work() = 0;
    virtual ~Thread();
};


#endif //TP2_THREAD_H
