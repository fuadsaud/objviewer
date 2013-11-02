#include "mesh.h"

obj::mesh::mesh() {
    render_faces();
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
    selected_face.group_position = group;
    selected_face.face_position = face;
    selected_face.face = groups[group]->get_face_at(face);
}

void obj::mesh::set_render_mode(int rm) {
    render_mode = rm;
}

void obj::mesh::set_gl_render_mode(int gl_rm) {
    gl_render_mode = gl_rm;
}

void obj::mesh::render_faces() {
    set_render_mode(face_mode);
    set_gl_render_mode(GL_POLYGON);
}

void obj::mesh::render_verts() {
    set_render_mode(vertex_mode);
    set_gl_render_mode(GL_LINE_LOOP);
}

void obj::mesh::toggle_render_mode() {
    if (render_mode == vertex_mode) { render_faces(); }
    else { render_verts(); }
}

void obj::mesh::render() {
    int group_name = 0;

    for (obj::group * group : get_groups()) {
        int face_name = 0;

        std::string material = group->get_material();

        glLoadName(group_name++);

        if (!group->is_visible()) continue;

        for (obj::face * face : group->get_faces()) {
            if (face == selected_face.face) {
                glColor3f(1, 0, 1);
            } else {
                glColor3f(1, 1, 1);
            }

            glPushName(face_name++);
            glBegin(gl_render_mode);

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

            if (render_mode == vertex_mode) { render_verts_points(); }
        }
    }
}

void obj::mesh::render_verts_points() {
    int vertex_name = 0;

    glColor3f(0.76, 1, 0.04);

    for (obj::vertex * v : verts) {
        glLoadName(vertex_name++);

        glBegin(GL_POINTS);
        glVertex3fv(v->get_coords());
        glEnd();
    }

}

void obj::mesh::erase_selection() {
    groups[selected_face.group_position]
        ->erase_face_at(selected_face.face_position);
}

void obj::mesh::complexify(obj::mesh::face_selection fs) {
    obj::vertex * centroid = fs.face->centroid(verts);

    push_vertex(centroid);

    for (unsigned int i = 0; i < fs.face->get_verts().size(); i++) {
        obj::face * new_face = new obj::face();

        new_face->push_vertex(fs.face->get_verts()[i]);
        new_face->push_vertex(fs.face->get_verts()[(i + 1) % (fs.face->get_verts().size())]);
        new_face->push_vertex(verts.size() - 1);

        group_at(fs.group_position)->push_face(new_face);

    }

    erase_face(fs);
}

void obj::mesh::erase_face(obj::mesh::face_selection fs) {
    group_at(fs.group_position)->erase_face_at(fs.face_position);
}

void obj::mesh::clear_selection() {
    selected_face.group_position = 0;
    selected_face.face_position = 0;
    selected_face.face = NULL;
}

void obj::mesh::complexify_selection() {
    complexify(selected_face);
}

bool obj::mesh::has_selection() {
    selected_face.face == NULL;
}
