#include "Group.h"

Group::Group(std::string n) {
  name = n;
}

void Group::push_face(Face * f) {
  faces.push_back(f);
}

void Group::set_material(std::string m) {
    material = m;
}

std::string Group::get_material() {
    return material;
}

std::vector<Face *> Group::get_faces(void) {
  return faces;
}
