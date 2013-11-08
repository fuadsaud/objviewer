#include "scene.h"

obj::scene::scene(bool hud, bool fps, bool axis) {
    current_time = frames = timebase = 0;

    set_hud_visibility(hud);
    set_fps_visibility(fps);
    set_axis_visibility(axis);
}

void obj::scene::initialize() {
    glClearColor(.1, .16, .19, 0);
    glClearDepth(1.0);

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glLineWidth(3);
    glPointSize(20);

    glScalef(2, 2, 5);

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);

    current_time = timebase = elapsed_time();

    camera = new obj::camera(90);

    reset_camera();
}

void obj::scene::reset_camera() {
    camera->reset_view(width(), height());
}

int obj::scene::elapsed_time() {
    return glutGet(GLUT_ELAPSED_TIME);
}

void obj::scene::push_mesh(obj::mesh * m) { mesh = m; }

void obj::scene::idle() { refresh_fps(); }

void obj::scene::render() {
    /* if (will_render_hud) render_hud(); */
    if (will_render_axis) render_axis();

    mesh->render();
}

void obj::scene::render_hud() {
    go2d();

    if (will_render_fps) render_fps();
}


void obj::scene::render_fps() {
    char * s = "";

    std::cout << fps() << std::endl;
    sprintf(s, "FPS: %4.2f", fps());

    render_string(s, 10, 8, 1, .85, .95);
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

void obj::scene::refresh_fps() {
    current_time = glutGet(GLUT_ELAPSED_TIME);
    frames++;

    if (current_time - timebase > 1000) {
        timebase = current_time;
        frames = 0;
    }
}

void obj::scene::render_string(char * string, float x, float y, float r, float g, float b) {
    for (unsigned int i = 0; i < strlen(string); i++) {
        glRasterPos2f(x, y);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);

        x += 14;
    }
}

void obj::scene::go2d() {
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width(), 0, height(), 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}

void obj::scene::set_hud_visibility(bool v) { will_render_hud  = v; }
void obj::scene::set_fps_visibility(bool v) { will_render_fps  = v; }
void obj::scene::set_axis_visibility(bool v) { will_render_axis = v; }

void obj::scene::toggle_hud() { set_hud_visibility(!will_render_hud); }
void obj::scene::toggle_fps() { set_fps_visibility(!will_render_fps); }
void obj::scene::toggle_axis() { set_axis_visibility(!will_render_axis); }

float obj::scene::fps() {
    return frames * 1000.0f / (current_time - timebase);
}

void obj::scene::move_camera_left() { camera->move(obj::camera::left); }
void obj::scene::move_camera_right() { camera->move(obj::camera::right); }
void obj::scene::move_camera_front() { camera->move(obj::camera::front); }
void obj::scene::move_camera_back() { camera->move(obj::camera::back); }

void obj::scene::look(float x, float y) {
    if(y != 0.5) { camera->set_direction_y(y - 0.5); }

    if(x != width() / 2) { camera->change_angle((x - width() / 2) / 10); }
}

int obj::scene::width() { return glutGet(GLUT_WINDOW_WIDTH); }
int obj::scene::height() { return glutGet(GLUT_WINDOW_HEIGHT); }
