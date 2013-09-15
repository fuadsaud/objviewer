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

void Mesh::set_material_library(std::string path) {
    materials = new MaterialLibrary(path);
}

void Mesh::render() {
    for (Group * group : get_groups()) {
        Material * m = (*materials)[group->get_material()];

        glMaterialf(GL_FRONT, GL_SPECULAR, *(m->get_specular()));
        glMaterialf(GL_FRONT, GL_AMBIENT,  *(m->get_ambient()));
        glMaterialf(GL_FRONT, GL_DIFFUSE,  *(m->get_diffuse()));
        glMaterialf(GL_FRONT, GL_SHININESS, m->get_shininess());

        for (Face * face : group->get_faces()) {
            glBegin(GL_POLYGON);

            std::vector<int> face_verts = face->get_verts();
            std::vector<int> face_norms = face->get_norms();

            for(unsigned int x = 0; x < face_verts.size(); ++x) {
                glNormal3fv(norms[face_norms[x]]->get_coords());
                glVertex3fv(verts[face_verts[x]]->get_coords());
            }

            glEnd();
        }
    }
}
