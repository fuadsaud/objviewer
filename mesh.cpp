#include "mesh.h"

obj::mesh::mesh() {
    render_mode = GL_POLYGON;
}

obj::group * obj::mesh::group_at(int i) {
    return groups.at(i);
}

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

void obj::mesh::push_texture(obj::vertex2 * t) {
    texts.push_back(t);
}

void obj::mesh::set_material_library(std::string path) {
    materials = new obj::material_library(path);
}

void obj::mesh::set_selection(int group, int face) {
    selection = groups[group]->get_face_at(face);

    selection->average_vertex(verts);
}

void obj::mesh::set_render_mode(int rm) {
    render_mode = rm;
}

void obj::mesh::render_faces() {
    set_render_mode(GL_POLYGON);
}

void obj::mesh::render_verts() {
    set_render_mode(GL_LINE_LOOP);
}

void obj::mesh::toggle_render_mode() {
    if (render_mode == GL_LINE_LOOP) {
        render_faces();
    } else {
        render_verts();
    }
}

void obj::mesh::render() {
    int group_name = 0;
    for (obj::group * group : get_groups()) {
        int face_name = 0;

        std::string material = group->get_material();

        glLoadName(group_name++);

        if (!group->is_visible()) continue;

        for (obj::face * face : group->get_faces()) {
            if (face == selection) {
                glColor3f(1, 0, 1);
            } else {
                glColor3f(1, 1, 1);
            }

            glPushName(face_name++);
            glBegin(render_mode);

            if (!material.empty()) {
                obj::material * m = (*materials)[group->get_material()];

                glMaterialfv(GL_FRONT, GL_SPECULAR, m->get_specular());
                glMaterialfv(GL_FRONT, GL_AMBIENT,  m->get_ambient());
                glMaterialfv(GL_FRONT, GL_DIFFUSE,  m->get_diffuse());
                glMaterialf(GL_FRONT, GL_SHININESS, m->get_shininess());

                if (m->has_texture()) {
                    glBindTexture(GL_TEXTURE_2D, m->get_texture_id());
                } else {
                    glBindTexture(GL_TEXTURE_2D, 0);
                }
            }

            std::vector<int> face_verts = face->get_verts();
            std::vector<int> face_norms = face->get_norms();
            std::vector<int> face_texts = face->get_texts();

            for (unsigned int x = 0; x < face_verts.size(); ++x) {
                if (!face_norms.empty()) {
                    glNormal3fv(norms[face_norms[x]]->get_coords());
                }

                if (!face_texts.empty()) {
                    glTexCoord2fv(texts[face_texts[x]]->get_coords());
                }

                glVertex3fv(verts[face_verts[x]]->get_coords());
            }

            glEnd();
            glPopName();
        }
    }
}
