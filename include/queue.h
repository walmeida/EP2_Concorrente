#ifndef QUEUE_H_
#define QUEUE_H_

#include <list>
#include <pthread.h>

/* FIFO queue */
template<class T>
class Queue {
    private:
        std::list<T> items_;
        unsigned long size_;
        pthread_mutex_t mutex_;
    public:
        Queue ();
        ~Queue ();
        void atomicInsert (T elem);
        T atomicRemove ();
        unsigned long size ();
};

template<class T>
Queue<T>::Queue () : size_(0) {
    pthread_mutex_init (&mutex_, NULL);
}

template<class T>
Queue<T>::~Queue () {
    pthread_mutex_destroy (&mutex_);
}

template<class T>
void Queue<T>::atomicInsert (T elem) {
    pthread_mutex_lock (&mutex_);
    items_.push_back (elem);
    size_++;
    pthread_mutex_unlock (&mutex_);
}

template<class T>
T Queue<T>::atomicRemove () {
    pthread_mutex_lock (&mutex_);
    T elem = items_.pop_front ();
    size_--;
    pthread_mutex_unlock (&mutex_);
    return elem;
}

template<class T>
unsigned long Queue<T>::size () {
    unsigned long size;
    pthread_mutex_lock (&mutex_);
    size = size_;
    pthread_mutex_unlock (&mutex_);
    return size;
}

#endif // QUEUE_H_
