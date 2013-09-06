#include "Face.h"

void Face::push_vertex(int v) {
  verts.push_back(v);
}

void Face::push_normal(int n) {
  norms.push_back(n);
}

std::vector<int> Face::get_verts(void) {
  return verts;
}

std::vector<int> Face::get_norms(void) {
  return norms;
}
