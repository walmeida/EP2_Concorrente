#ifndef QUEUECOND_H_
#define QUEUECOND_H_

class QueueCond {
    private:
        int size_;
    public:
        explicit QueueCond (int size) : size_(size) {};
        ~QueueCond () {};
        bool operator() (const Path* const p) {
            return p->size () == size_;
        }
        void incrementSizeCondition () {
            size_++;
        }
};

#endif
