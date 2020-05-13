#ifndef TP2_THREAD_H
#define TP2_THREAD_H

#include <thread>

class Thread {
private:
    std::thread thread;
public:
    Thread(); //ver q hacer con los constr q no hacen nada
    void start();
    void join();
    virtual void work() = 0;
    virtual ~Thread() = default;
};


#endif //TP2_THREAD_H
