#include "Mesh.h"

std::vector<Vertex *> Mesh::get_verts() {
  return verts;
}

void Mesh::push_group(Group * g) {
  groups.push_back(g);
}

void Mesh::push_vertex(Vertex * v) {
  verts.push_back(v);
}

void Mesh::push_normal(Vertex * n) {
  norms.push_back(n);
}
