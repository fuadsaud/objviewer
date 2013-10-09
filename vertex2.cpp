#include "vertex2.h"

obj::vertex2::vertex2(float c[2]) {
  coords[0] = c[0];
  coords[1] = c[1];
}

obj::vertex2::vertex2(float x, float y) {
  coords[0] = x;
  coords[1] = y;
}

float * obj::vertex2::get_coords(void) {
  return coords;
}
