#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>
#include <GLUT/GLUT.h>
#include <iostream>
#include "OBJ.h"
#include "Camera.h"

void initOpenGL();
void display();
void keyboard(unsigned char key, int x, int y);
void passiveMotionFunc(int x, int y);

Mesh * mesh;
Camera * camera;

int width = 800, height = 600;

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Mesh");

    initOpenGL();

    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(passiveMotionFunc);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

void initOpenGL() {
    glClearColor(0.8, 0.8, 0.8, 0);
    glClearDepth(1.0);

    /* GLfloat lightpos[] = {.5, 1., 1., 0.}; */
    /* glLightfv(GL_LIGHT0, GL_POSITION, lightpos); */

    glEnable(GL_DEPTH_TEST | GL_LIGHTING | GL_LIGHT0);

    camera = new Camera(90);
    camera->resetView(width, height);

    mesh = new Mesh();

    OBJ("fixtures/teapot1.obj").load(mesh);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(.86, .98, .36);

    std::vector<Vertex *> verts = mesh->get_verts();
    std::vector<Vertex *> norms = mesh->get_norms();

    for (Group * group : mesh->get_groups()) {
      for (Face * face : group->get_faces()) {
        glBegin(GL_POLYGON);

        for (int i : face->get_verts()) {
            glVertex3fv(verts[i]->get_coords());
        }

        for (int i : face->get_norms()) {
            glNormal3fv(norms[i]->get_coords());
        }

        glEnd();
      }
    }

    glutSwapBuffers();
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  if(key == 'q' || key == 'Q'){
    exit(0);
  }
  else {
    switch(key){
      case 'a':
      case 'A':
        camera->moveSide(1);
        break;
      case 's':
      case 'S':
        camera->move(-1);
        break;
      case 'd':
      case 'D':
        camera->moveSide(-1);
        break;
      case 'w':
      case 'W':
        camera->move(1);
        break;
    }

    glutPostRedisplay();
  }
}

void passiveMotionFunc(int x, int y) {
  float y2 = (height - y) / (float) height;

  if (y2 != 0.5 || x != width / 2) {
    if(y2 != 0.5) {
      camera->setDirectionY(y2 - 0.5);
    }

    if(x != width/2) {
      camera->changeAngle((x - width / 2) / 10);
    }

    glutWarpPointer(width / 2, height / 2);
    glutPostRedisplay();
  }
}
