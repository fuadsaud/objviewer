#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>
#include <GLUT/GLUT.h>
#include <iostream>

#include "loader.h"
#include "scene.h"

#define BUFSIZE 512

void idle();
void display();
void toggleFullScreen();
void loadModel(const char * path);
void passiveMotion(int x, int y);
void reshapeFunc(int w, int h);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void processHits(GLint hits, GLuint buffer[]);

obj::scene scene;
obj::mesh mesh;

int width = 800, height = 600;

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OBJ Viewer");

    scene.initialize();

    loadModel(argv[1]);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(passiveMotion);
    glutPassiveMotionFunc(passiveMotion);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}

void loadModel(const char * path) {
    obj::loader(path).load(&mesh);

    scene.push_mesh(&mesh);
}

void toggleFullScreen() { glutFullScreen(); }

void idle() {
    scene.idle();

    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(.86, .98, .36);

    scene.render();

    glutSwapBuffers();
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'q': exit(0); break;
        case 'a': scene.move_camera_left(); break;
        case 's': scene.move_camera_back(); break;
        case 'd': scene.move_camera_right(); break;
        case 'w': scene.move_camera_front(); break;
        case 'h': mesh.move_selection(obj::vertex::x_neg); break;
        case 'j': mesh.move_selection(obj::vertex::y_neg); break;
        case 'k': mesh.move_selection(obj::vertex::y_pos); break;
        case 'l': mesh.move_selection(obj::vertex::x_pos); break;
        case 'u': mesh.move_selection(obj::vertex::z_pos); break;
        case 'n': mesh.move_selection(obj::vertex::z_neg); break;
        case 'r':
                  mesh.toggle_render_mode(); break;
        case 'x':
                  mesh.erase_selection(); break;
        case 'y':
                  mesh.complexify_selection(); break;
        case 'f':
                  toggleFullScreen(); break;
        case '9':
                  scene.toggle_axis(); break;
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

    GLuint select_buf[BUFSIZE];
    GLint hits;
    GLint viewport[4];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(BUFSIZE, select_buf);

    (void) glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluPickMatrix((GLdouble) x, (GLdouble) viewport[3] - y, 20.0, 20.0, viewport);
    gluPerspective(45.0, width / (double) height, .2, 200.0);

    scene.render(true);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glFlush();

    hits = glRenderMode(GL_RENDER);

    if (hits != 0) processHits(hits, select_buf);

    glutPostRedisplay();
}

void passiveMotion(int x, int y) {
    float y2 = (height - y) / (float) height;

    if (y2 != 0.5 || x != width / 2.0) {
        scene.look(x, y2);

        glutWarpPointer(width / 2.0, height / 2.0);
        glutPostRedisplay();
    }
}

void processHits(GLint hits, GLuint buffer[]) {
    GLuint names, *ptr, min_z, *ptr_names;

    ptr = (GLuint *) buffer;
    min_z = 0xffffffff;

    for (unsigned int i = 0; i < hits; i++) {
        names = *ptr;
        ptr++;
        if (*ptr < min_z) {
            min_z = *ptr;
            ptr_names = ptr + 2;
        }

        ptr += names + 2;
    }

    mesh.set_selection(ptr_names[0], ptr_names[1]);
}

void reshapeFunc(int w, int h) {
    if (h < 1) h = 1;

    width  = w;
    height = h;

    glutWarpPointer(width / 2, height / 2);

    scene.reshape();
}
