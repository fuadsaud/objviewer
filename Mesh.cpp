#include "Mesh.h"

std::vector<Vertex *> Mesh::get_verts() {
  return verts;
}

std::vector<Vertex *> Mesh::get_norms() {
  return norms;
}

std::vector<Group *> Mesh::get_groups() {
  return groups;
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
