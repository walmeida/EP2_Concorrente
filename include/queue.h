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
        unsigned long atomicInsert (T elem);
        template<class B>
        T* atomicRemove (B& condition);
        unsigned long size ();
        bool empty ();
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
unsigned long Queue<T>::atomicInsert (T elem) {
    unsigned long new_size;
    pthread_mutex_lock (&mutex_);
    items_.push_back (elem);
    new_size = size_++;
    pthread_mutex_unlock (&mutex_);
    return new_size;
}

template<class T>
template<class B>
T* Queue<T>::atomicRemove (B& condition) {
    pthread_mutex_lock (&mutex_);
    T* elem = &(items_.front ());
    if (condition (*elem)) {
        items_.pop_front ();
        size_--;
    } else {
        elem = NULL;
    }
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

template<class T>
bool Queue<T>::empty () {
    bool empty;
    pthread_mutex_lock (&mutex_);
    empty = items_.empty();
    pthread_mutex_unlock (&mutex_);
    return empty;
}

#endif // QUEUE_H_
