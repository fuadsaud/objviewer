#include "mesh.h"

std::vector<obj::vertex *> obj::mesh::get_verts() {
  return verts;
}

std::vector<obj::vertex *> obj::mesh::get_norms() {
  return norms;
}

std::vector<obj::group *> obj::mesh::get_groups() {
  return groups;
}

void obj::mesh::push_group(obj::group * g) {
  groups.push_back(g);
}

void obj::mesh::push_vertex(obj::vertex * v) {
  verts.push_back(v);
}

void obj::mesh::push_normal(obj::vertex * n) {
  norms.push_back(n);
}

void obj::mesh::set_material_library(std::string path) {
    materials = new obj::material_library(path);
}

void obj::mesh::render() {
    for (obj::group * group : get_groups()) {
        std::string material = group->get_material();

        glColor3f(1, 1, 1);
        for (obj::face * face : group->get_faces()) {
            glBegin(GL_POLYGON);

            if (!material.empty()) {
                obj::material * m = (*materials)[group->get_material()];

                std::cout << m->get_specular()[0] << std::endl;
                glMaterialfv(GL_FRONT, GL_SPECULAR, m->get_specular());
                glMaterialfv(GL_FRONT, GL_AMBIENT,  m->get_ambient());
                glMaterialfv(GL_FRONT, GL_DIFFUSE,  m->get_diffuse());
                glMaterialf(GL_FRONT, GL_SHININESS, m->get_shininess());
            }

            std::vector<int> face_verts = face->get_verts();
            std::vector<int> face_norms = face->get_norms();

            for(unsigned int x = 0; x < face_verts.size(); ++x) {
                if (face_norms.size()) {
                    std::cout << norms.size() << std::endl;
                    std::cout << "entrou" << std::endl;
                    glNormal3fv(norms[face_norms[x]]->get_coords());
                }
                std::cout << "fechou" << std::endl;
                glVertex3fv(verts[face_verts[x]]->get_coords());
            }

            glEnd();
        }
    }
}
