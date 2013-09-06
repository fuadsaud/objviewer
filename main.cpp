#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>
#include <GLUT/GLUT.h>
#include <iostream>

void initOpenGL();
void display();

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Mesh");

    initOpenGL();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

void initOpenGL() {
    glClearColor(0.8, 0.8, 0.8, 0);
    glClearDepth(1.0);

    glEnable(GL_LIGHTING | GL_LIGHT0);
    GLfloat lightpos[] = {.5, 1., 1., 0.};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_WIDTH));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 800 / 600, 0.2, 200);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(-10, 8, -10, 0, 0, 0, 0, 1, 0);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSwapBuffers();
    glFlush();
}
