#include "group.h"

obj::group::group(std::string n) {
  name = n;
  material = "";
  visible = true;
}

void obj::group::push_face(obj::face * f) {
  faces.push_back(f);
}

void obj::group::set_material(std::string m) {
    material = m;
}

std::string obj::group::get_material() {
    return material;
}

std::vector<obj::face *> obj::group::get_faces(void) {
  return faces;
}

void obj::group::hide() {
    visible = false;
}

bool obj::group::is_visible() {
    return visible;
}
