#include "path.h" 

using std::list;

Path::Path () : size_(0) {};
Path::~Path () {};

bool Path::containsVertex (Vertex v) {
    for (list<Vertex>::iterator it = path_.begin(); it != path_.end(); ++it){
        if (*it == v)
            return true;
    }
    return false;
}

void Path::insertVertex (Vertex v) {
    path_.push_back(v);
    ++size_;
}


int Path::size () {
    return size_;
}

Path& Path::operator= (const Path &rhs) {
    path_ = rhs.path_;
    size_ = rhs.size_;
    return *this;
}
