#include "path.h" 

using std::list;

list<Vertex> path_;

Path::Path () {};
Path::~Path () {};

bool Path::containsVertex (Vertex v) {
  for (list<Vertex>::iterator it = path_.begin(); it != path_.end(); it++){
    if(*it == v)
      return true;
  }
  
  return false;
}

void Path::insertVertex (Vertex v) {
  path_.push_back(v);
}

int Path::size(){
  return path_.size();
}
