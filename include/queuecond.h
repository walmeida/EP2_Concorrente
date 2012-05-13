#ifndef QUEUECOND_H_
#define QUEUECOND_H_

class QueueCond {
    private:
        int size_;
    public:
        explicit QueueCond (int size) : size_(size) {};
        ~QueueCond () {};
        bool operator() (const Path* const p) const {
            return p->size () == size_;
        }
        void incrementSizeCondition () {
            size_++;
        }
        int getSizeCondition () const {
            return size_;
        }
};

#endif
