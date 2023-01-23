//
// Created by mathi on 22/01/2023.
//

#include "Thread.h"

Thread::Thread() = default;

Thread::~Thread() = default;

void Thread::run() {}

void Thread::yield() {
    sched_yield();
}

void Thread::start() {
    // inicia o atributo;
    int status = pthread_attr_init(&_tAttribute);
    status = pthread_attr_setscope(&_tAttribute, PTHREAD_SCOPE_SYSTEM);
    if (status != 0)
        printError("falha ao iniciar atributo da thread.");

    // cria uma thread;
    status = pthread_create(&_threadID, &_tAttribute, Thread::runThread, (void *) this);
    if (status != 0)
        printError("falha ao iniciar a thread.");

    // destrói o atributo;
    status = pthread_attr_destroy(&_tAttribute);
    if (status != 0)
        printError("falha ao destruir atributo da thread.");
}

void Thread::join() {
    int status = pthread_join(_threadID, nullptr);
    if (status != 0)
        printError("comando join falhou.");
}

void *Thread::runThread(void *pThread) {
    auto *sThread = static_cast<Thread *> (pThread);

    if (nullptr == sThread) { std::cout << "thread falhou." << std::endl; }
    else { sThread->run();  /* executa a thread; */            }
    return nullptr;
}

void Thread::printError(const string &msg) {
    std::cout << "Erro: " << msg << std::endl;
}
