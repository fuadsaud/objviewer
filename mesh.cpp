#include "mesh.h"

obj::mesh::mesh() {
    enter_faces_render_mode();
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

void obj::mesh::set_selection(int group_or_vertex, int face) {
    if (render_mode == vertex_mode) {
        selected_vertex.vertex_position = group_or_vertex;
        selected_vertex.vertex = verts[group_or_vertex];
    } else {
        selected_face.group_position = group_or_vertex;
        selected_face.face_position = face;
        selected_face.face = groups[group_or_vertex]->get_face_at(face);
    }
}

void obj::mesh::set_render_mode(int rm) {
    render_mode = rm;
}

void obj::mesh::set_gl_render_mode(int gl_rm) {
    gl_render_mode = gl_rm;
}

void obj::mesh::enter_faces_render_mode() {
    set_render_mode(face_mode);
    set_gl_render_mode(GL_POLYGON);
}

void obj::mesh::enter_verts_render_mode() {
    set_render_mode(vertex_mode);
    set_gl_render_mode(GL_LINE_LOOP);
}

void obj::mesh::toggle_render_mode() {
    if (render_mode == vertex_mode) { enter_faces_render_mode(); }
    else { enter_verts_render_mode(); }
}

void obj::mesh::render() {
    if (render_mode == vertex_mode) render_verts_points();

    int group_name = 0;

    for (obj::group * group : get_groups()) {
        int face_name = 0;

        std::string material = group->get_material();

        if (render_mode == face_mode) glLoadName(group_name++);

        if (!group->is_visible()) continue;

        for (obj::face * face : group->get_faces()) {
            if (render_mode == face_mode) {
                if (face == selected_face.face) glColor3f(.78, .29, .15);

                glPushName(face_name++);
            }

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
                    /* glTexCoord2fv(texts[face_texts[x]]->get_coords()); */
                }

                glVertex3fv(verts[face_verts[x]]->get_coords());
            }

            glEnd();
            glPopName();

            if (render_mode == face_mode &&
                    face == selected_face.face) glColor3f(.4, .57, .59);
        }
    }
}

void obj::mesh::render_verts_points() {
    int vertex_name = 0;

    for (obj::vertex * v : verts) {
        glLoadName(vertex_name++);

        if (selected_vertex.vertex == v) glColor3f(0.41, .58, .19);

        glBegin(GL_POINTS);
        glVertex3fv(v->get_coords());
        glEnd();

        if (selected_vertex.vertex == v) glColor3f(0.72, .53, 0.17);
    }

}

void obj::mesh::erase_selection() {
    if (render_mode == vertex_mode) {
        erase_vertex(selected_vertex);
    } else {
        group_at(selected_face.group_position)
            ->erase_face_at(selected_face.face_position);
    }
}

void obj::mesh::erase_vertex(obj::mesh::vertex_selection vs) {
    if (verts.empty()) return;

    std::set<int> affected_verts;

    for (obj::group * group : groups) {
        std::vector<int> faces_to_erase;

        unsigned int faces_count = group->get_faces().size();

        for (unsigned int i = 0; i < faces_count; i++) {
            obj::face * face = group->get_faces()[i];
            std::vector<int> face_verts = face->get_verts();

            if (std::find(face_verts.begin(), face_verts.end(), vs.vertex_position) != face_verts.end()) {
                for (int vertex : face_verts) {
                    affected_verts.insert(vertex);
                }

                faces_to_erase.push_back(i);
            }
        }

        std::reverse(faces_to_erase.begin(), faces_to_erase.end());

        for (int face_to_erase : faces_to_erase) {
            group->erase_face_at(face_to_erase);
        }
    }

    affected_verts.erase(vs.vertex_position);
    verts.erase(verts.begin() + vs.vertex_position);

    obj::face * new_face = new obj::face();

    for (int v : affected_verts) new_face->push_vertex(v);

    groups.back()->push_face(new_face);
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

void obj::mesh::move(int direction, obj::mesh::vertex_selection vs) {
    verts[vs.vertex_position] =
        verts[vs.vertex_position]->move(direction);
}

void obj::mesh::erase_face(obj::mesh::face_selection fs) {
    group_at(fs.group_position)->erase_face_at(fs.face_position);
}

void obj::mesh::clear_selection() {
    selected_face.group_position = 0;
    selected_face.face_position = 0;
    selected_face.face = NULL;
}

void obj::mesh::complexify_selection() { complexify(selected_face); }

void obj::mesh::move_selection(int direction) {
    move(direction, selected_vertex);
}

bool obj::mesh::has_selection() {
    selected_face.face == NULL;
}
