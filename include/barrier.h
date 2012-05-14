#ifndef BARRIER_H_
#define BARRIER_H_

class Barrier {
    private:
        volatile unsigned long *arrive_;
        int num_threads_;
        int num_stages_;
    public:
        Barrier (int num_threads);
        ~Barrier ();
        void sync (int thread_id);
        void setFinished (int thread_id);
};

#endif
