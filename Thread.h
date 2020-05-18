#ifndef TP2_THREAD_H
#define TP2_THREAD_H

#include <thread>

class Thread {
private:
    std::thread thread;
public:
    /* Constructor */
    Thread();

    /* Ejecuta el thread con el metodo abstracto trabajar, que sera
     * implementado por las clases hijas */
    void start();
    /* Bloquea el thread hasta que los otros completen su trabajo */
    void join();

    virtual void trabajar() = 0;

    /* Destructor */
    virtual ~Thread();
};


#endif //TP2_THREAD_H
