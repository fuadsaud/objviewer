#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>
#include <GLUT/GLUT.h>
#include <iostream>

#include "loader.h"
#include "camera.h"

#define BUFSIZE 512

void initOpenGL();
void loadModel(const char * path);
void display();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void passiveMotionFunc(int x, int y);
void processHits(GLint hits, GLuint buffer[]);

obj::mesh mesh;
obj::camera * camera;

int width = 800, height = 600;

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OBJ Viewer");

    initOpenGL();
    loadModel(argv[1]);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passiveMotionFunc);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

void initOpenGL() {
    glClearColor(.0, .79, .31, 0);
    glClearDepth(1.0);

    GLfloat light_position[] = { 10.0, 1.0,  1.0,  .0 };
    GLfloat light_specular[] = {  1.0, 1.0,   .0, 1.0 };
    GLfloat light_diffuse[]  = {   .5,  .5,   .5, 1.0 };
    glShadeModel (GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    camera = new obj::camera(90);
    camera->reset_view(width, height);
}

void loadModel(const char * path) {
    obj::loader(path).load(&mesh);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(.86, .98, .36);

    mesh.render();

    glutSwapBuffers();
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'q' || key == 'Q') {
        exit(0);
    } else {
        switch(key) {
            case 'a':
            case 'A':
                camera->move_side(1); break;
            case 's':
            case 'S':
                camera->move(-1); break;
            case 'd':
            case 'D':
                camera->move_side(-1); break;
            case 'w':
            case 'W':
                camera->move(1); break;
        }

        glutPostRedisplay();
    }
}

void passiveMotionFunc(int x, int y) {
    float y2 = (height - y) / (float) height;

    if (y2 != 0.5 || x != width / 2) {
        if(y2 != 0.5) {
            camera->set_direction_y(y2 - 0.5);
        }

        if(x != width/2) {
            camera->change_angle((x - width / 2) / 10);
        }

        glutWarpPointer(width / 2, height / 2);
        glutPostRedisplay();
    }
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

    gluPickMatrix (x, viewport[3] - y, 5.0, 5.0, viewport);
    gluPerspective(45.0, width / (double) height, 0.2, 200.0);

    mesh.render();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glFlush();

    hits = glRenderMode(GL_RENDER);

    if (hits != 0) processHits(hits, select_buf);

    glutPostRedisplay();
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

    mesh.group_at(*ptr_names)->hide();
}
