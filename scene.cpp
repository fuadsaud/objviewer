#include "scene.h"

obj::scene::scene(bool ra) {
    will_render_axis = ra;
}

void obj::scene::render() {
    if (will_render_axis) render_axis();

    mesh->render();
}

void obj::scene::push_mesh(obj::mesh * m) {
    mesh = m;
}

void obj::scene::render_axis(float size) {
    glLineStipple(1, 0x00FF);

    /* X positive and negative lines */
    glColor3f(1.0f, 0.0f, 0.0f);

    glPushMatrix();

    /* if (current_mesh->selection_type() == SELECTION_VERTEX && glMode == GL_LINE_LOOP) { */
    /* float* xyz = current_mesh->get_selected_vertex_xyz(); */
    /* glTranslatef(xyz[0], xyz[1], xyz[2]); */
    /* } else if (new_face_mode) { */
    /* glTranslatef(new_face_xyz[0], new_face_xyz[1], new_face_xyz[2]); */
    /* } else { */
    glTranslatef(0.0f, 0.0f, 0.0f);
    /* } */

    glDisable(GL_LINE_STIPPLE);

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(size, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_POINTS);
    glVertex3f(size, 0.0f, 0.0f);
    glEnd();

    glEnable(GL_LINE_STIPPLE);

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-size, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_POINTS);
    glVertex3f(-size, 0.0f, 0.0f);
    glEnd();

    /* Y positive and negative lines */
    glColor3f(0.0f, 1.0f, 0.0f);

    glDisable(GL_LINE_STIPPLE);

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, size, 0.0f);
    glEnd();

    glBegin(GL_POINTS);
    glVertex3f(0.0f, size, 0.0f);
    glEnd();

    glEnable(GL_LINE_STIPPLE);

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -size, 0.0f);
    glEnd();

    glBegin(GL_POINTS);
    glVertex3f(0.0f, -size, 0.0f);
    glEnd();

    /* Z positive and negative lines */
    glColor3f(0.0f, 0.0f, 1.0f);

    glDisable(GL_LINE_STIPPLE);

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, size);
    glEnd();

    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, size);
    glEnd();

    glEnable(GL_LINE_STIPPLE);

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -size);
    glEnd();

    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, -size);
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    glPopMatrix();
}
