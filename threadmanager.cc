#include "threadmanager.h"
#include <iostream>

ThreadManager::ThreadManager (int num_threads) : num_threads_(num_threads) {
    programthread_ = new pthread_t[num_threads];
    thread_ids_ = new int[num_threads_];
}

ThreadManager::~ThreadManager () {
    delete[] programthread_;
    delete[] thread_ids_;
}

void ThreadManager::createAndRunThreads (void* (*thread_function) (void*)) {
    if(!createProgramThreads (thread_function))
        return;
    joinThreads ();
}
    
bool ThreadManager::createProgramThreads (void* (*thread_function) (void*)) {
    for (int i = 0; i < num_threads_; ++i){
        thread_ids_[i] = i;
        if (pthread_create (&programthread_[i], NULL, thread_function, (void *) &(thread_ids_[i]))) {
            std::cerr << "Error creating thread." << std::endl;
            return false;
        }
    }
    return true;
}

void ThreadManager::joinThreads () {
    for (int i = 0; i < num_threads_; ++i){
        if (pthread_join (programthread_[i], NULL)) {
            std::cerr << "Error joining thread." << std::endl;
            return;
        }
    }
}
