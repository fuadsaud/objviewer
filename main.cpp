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

    /* glEnable(GL_LIGHTING | GL_LIGHT0); */
    /* GLfloat lightpos[] = {.5, 1., 1., 0.}; */
    /* glLightfv(GL_LIGHT0, GL_POSITION, lightpos); */

    glEnable(GL_DEPTH_TEST);

    camera = new Camera(90);
    camera->resetView(width, height);

    mesh = new Mesh();

    /* OBJ("fixtures/cone.obj").load(mesh); */
    OBJ("fixtures/pyramid.obj").load(mesh);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1, 0, 0);

    std::vector<Group *> groups = mesh->get_groups();
    std::vector<Vertex *> verts = mesh->get_verts();
    std::cout << groups.size() << std::endl;

    for (int i = 0; i < groups.size(); i++) {
      std::vector<Face *> faces = groups[i]->get_faces();

      std::cout << "1" << std::endl;
      for (int j = 0; j < faces.size(); j++) {
        Face * face = faces[j];
        std::cout << "2" << std::endl;

        std::vector<int> v = face->get_verts();
        std::vector<int> n = face->get_norms();

        glBegin(GL_POLYGON);
        for (int k = 0; k < v.size(); k++) {
          std::cout << "3" << std::endl;
          glVertex3fv(verts[v[k]]->get_coords());
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
