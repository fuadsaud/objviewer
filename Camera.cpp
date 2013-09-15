#include "camera.h"

Camera::Camera(float init_angle) {
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

void Camera::refresh_look_at() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(i[0], i[1], i[2],
            d[0], d[1] + i[1], d[2],
            0, 1, 0);
}

void Camera::reset_view(int width, int height) {
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0, width / (double) height, .2, 1000);

  refresh_look_at();
}

void Camera::change_angle(float angle2) {
  angle += angle2;

  if(angle > 360) {
    angle -= 360;
  } else if(angle < 0) {
    angle += 360;
  }

  refresh_direction();
  refresh_look_at();
}

void Camera::refresh_direction() {
  d[0] =  get_cos() + i[0];
  d[2] =  get_sin() + i[2];
}

void Camera::set_direction_y(float y) {
  d[1] += y;
  refresh_look_at();
}

void Camera::move(int direction) {
  i[0] += SPEED * direction * get_cos();
  i[1] += SPEED * direction * d[1];
  i[2] += SPEED * direction * get_sin();

  refresh_direction();
  refresh_look_at();
}

void Camera::move_side(int direction) {
  float auxAngle = angle / 180 * PI - (PI / 2);

  i[0] += SPEED * cos(auxAngle) * direction;
  i[2] += SPEED * sin(auxAngle) * direction;

  refresh_direction();
  refresh_look_at();
}

float Camera::get_sin() {
  return sin(angle / 180 * PI);
}

float Camera::get_cos() {
  return cos(angle / 180 * PI);
}
