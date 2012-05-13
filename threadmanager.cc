#include "threadmanager.h"
#include "log.h"

extern Log l;

ThreadManager::ThreadManager (int num_threads) : num_threads_(num_threads),
        programthread_(new pthread_t[num_threads]) {};

ThreadManager::~ThreadManager () {
    delete[] programthread_;
}

void ThreadManager::createAndRunThreads (void* (*thread_function) (void*)) {
    if(!createProgramThreads (thread_function))
        return;
    joinThreads ();
}
    
bool ThreadManager::createProgramThreads (void* (*thread_function) (void*)) {
    for (int i = 0; i < num_threads_; ++i){
        if (pthread_create (&programthread_[i], NULL, thread_function, NULL)) {
            l.error ("Error creating thread.");
            return false;
        }
    }
    return true;
}

void ThreadManager::joinThreads () {
    for (int i = 0; i < num_threads_; ++i){
        if (pthread_join (programthread_[i], NULL)) {
            l.error ("Error joining thread.");
            return;
        }
    }
}
