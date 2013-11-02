#include "camera.h"

obj::camera::camera(float init_angle) {
  i = new float[3];
  i[0] = 0;
  i[1] = 0;
  i[2] = 0;
  d = new float[3];
  d[1] = 0;
  angle = init_angle;
  refresh_direction();
  reset_view(800, 600);
}

void obj::camera::refresh_look_at() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(i[0], i[1], i[2],
            d[0], d[1] + i[1], d[2],
            0, 1, 0);
}

void obj::camera::reset_view(int width, int height) {
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0, width / (double) height, .2, 1000);

  refresh_look_at();
}

void obj::camera::change_angle(float angle2) {
  angle += angle2;

  if(angle > 360) {
    angle -= 360;
  } else if(angle < 0) {
    angle += 360;
  }

  refresh_direction();
  refresh_look_at();
}

void obj::camera::refresh_direction() {
  d[0] =  get_cos() + i[0];
  d[2] =  get_sin() + i[2];
}

void obj::camera::set_direction_y(float y) {
  d[1] += y;
  refresh_look_at();
}

void obj::camera::move(int direction) {
    int modifier = modifier_for_direction(direction);

    float auxAngle = angle / 180 * PI - (PI / 2);

    switch (direction) {
        case left:
        case right:
            i[0] += SPEED * cos(auxAngle) * modifier;
            i[2] += SPEED * sin(auxAngle) * modifier;

            break;
        case front:
        case back:
            i[0] += SPEED * modifier * get_cos();
            i[1] += SPEED * modifier * d[1];
            i[2] += SPEED * modifier * get_sin();

            break;
    }

    refresh_direction();
    refresh_look_at();
}

float obj::camera::get_sin() { return sin(angle / 180 * PI); } 
float obj::camera::get_cos() { return cos(angle / 180 * PI); }

int obj::camera::modifier_for_direction(int direction) {
    switch (direction) {
        case left:
        case front: return 1;
        case right:
        case back: return -1;
    }
}
