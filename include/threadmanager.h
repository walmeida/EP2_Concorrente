#ifndef THREADMANAGER_H_
#define THREADMANAGER_H_

#include <pthread.h>

class ThreadManager {
    private:
        int num_threads_;
        pthread_t* programthread_;
        bool createProgramThreads (void* (*thread_function) (void*));
        void joinThreads ();
    public:
        ThreadManager (int num_threads);
        ~ThreadManager ();
        void createAndRunThreads (void* (*thread_function) (void*));
};

#endif // THREADMANAGER_H_
