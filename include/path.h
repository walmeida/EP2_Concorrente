#ifndef PATH_H_
#define PATH_H_

#include <list>
#include "graph.h"

class Path {
    private:
        std::list<Vertex> path_;
        unsigned long size_;
    public:
        Path ();
        Path (const Path& p);
        ~Path ();
        bool containsVertex (Vertex v) const;
        void insertVertex (Vertex v);
        int size () const;
        Path& operator= (const Path &rhs);
        Vertex lastVertex () const;

        void print () const {
            for (std::list<Vertex>::const_iterator it = path_.begin(); it != path_.end(); ++it){
            printf ("%d ", *it);
            }
            printf ("\n");
        }
};

#endif // PATH_H_
