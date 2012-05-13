#include "barrier.h"

#include <stdio.h>

Barrier::Barrier (int num_threads) : num_threads_(num_threads) {
    arrive_ = new unsigned long[num_threads];
    for (int i = 0; i < num_threads; ++i)
        arrive_[i] = 0;
    num_stages_ = 0;
    for (int threads = num_threads; threads; threads >>= 1)
        ++num_stages_;
    num_stages_--;
    if (num_threads > (1 << num_stages_)) {
        num_stages_++;
    }
}
    
Barrier::~Barrier () {
    delete arrive_;
}

void Barrier::sync (int thread_id) {
    for (int stage = 0; stage < num_stages_; ++stage) {
        arrive_[thread_id]++;
        int neighbour = (thread_id + (1 << stage)) % num_threads_;
        printf ("neighbour = %d, stage %d of %d\n", neighbour, stage + 1, num_stages_);
        while (arrive_[neighbour] < arrive_[thread_id]);
            //printf ("thread %d travada: %lu < %lu\n", thread_id,
            //        arrive_[neighbour], arrive_[thread_id]);
    }
}

void Barrier::setFinished (int thread_id) {
    arrive_[thread_id] = -1;
}
