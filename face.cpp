#include "Face.h"

void obj::face::push_vertex(int v) {
  verts.push_back(v);
}

void obj::face::push_normal(int n) {
  norms.push_back(n);
}

std::vector<int> obj::face::get_verts(void) {
  return verts;
}

std::vector<int> obj::face::get_norms(void) {
  return norms;
}
