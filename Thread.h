//
// Created by mathi on 22/01/2023.
//

#ifndef RELOGIOPONTO_THREAD_H
#define RELOGIOPONTO_THREAD_H

#include <iostream>
#include <pthread.h>
#include <string>

using std::cout;
using std::endl;
using std::string;

// Class utilizada para gerenciar threads orientadas a objetos;
class Thread {
private:
    pthread_t _threadID{}; // pthread;
    // atributo da thread, pode conter informações sobre o funcionamento da thread;
    pthread_attr_t _tAttribute{};

    // método que inicia as thread;
    static void *runThread(void *pThread);

    // código para execução;
    virtual void run();
    static void printError(const string &msg);

public:
    Thread();

    virtual ~Thread();

    void start();   // cria a thread;
    void join();    // espera a thread acabar;
    void yield();   // libera o processador;
};


#endif //RELOGIOPONTO_THREAD_H
