#ifndef PATH_H_
#define PATH_H_

#include <list>
#include "graph.h"

#include <sstream>
#include <iostream>

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

        std::stringstream* print () const {
            std::stringstream *ss = new std::stringstream ();
            for (std::list<Vertex>::const_iterator it = path_.begin(); it != path_.end(); ++it){
                *ss << *it << " ";
            }
            return ss;
        }
};

#endif // PATH_H_
