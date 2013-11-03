#include "vertex.h"

obj::vertex::vertex(float c[3]) {
  coords[0] = c[0];
  coords[1] = c[1];
  coords[2] = c[2];
}

obj::vertex::vertex(float x, float y, float z) {
  coords[0] = x;
  coords[1] = y;
  coords[2] = z;
}

float * obj::vertex::get_coords(void) { return coords; }

obj::vertex * obj::vertex::move(int dirextion, int amount) {
    float * c = get_coords();

    switch (dirextion) {
        case x_pos: c[0] += amount; break;
        case x_neg: c[0] -= amount; break;
        case y_pos: c[1] += amount; break;
        case y_neg: c[1] -= amount; break;
        case z_pos: c[2] += amount; break;
        case z_neg: c[2] -= amount; break;
    }

    return new obj::vertex(c);
}
