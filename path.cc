#include "path.h" 

using std::list;
using std::stringstream;

Path::Path () : size_(0) {};
Path::Path (const Path& p) : path_(p.path_), size_(p.size_) {};
Path::~Path () {};

bool Path::containsVertex (Vertex v) const {
    for (list<Vertex>::const_iterator it = path_.begin(); it != path_.end(); ++it){
        if (*it == v)
            return true;
    }
    return false;
}

void Path::insertVertex (Vertex v) {
    path_.push_back(v);
    ++size_;
}

int Path::size () const {
    return size_;
}

Path& Path::operator= (const Path &rhs) {
    path_ = rhs.path_;
    size_ = rhs.size_;
    return *this;
}

Vertex Path::lastVertex () const {
    return path_.back ();
}

void Path::print (stringstream &ss) const {
    ss << "(" << size_ - 1 << ") 0";
    for (list<Vertex>::const_iterator it = ++(path_.begin()); it != path_.end(); ++it){
        ss << " - " << *it;
    }
}
