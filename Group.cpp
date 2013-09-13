#include "Group.h"

Group::Group(std::string n) {
  name = n;
}

void Group::push_face(Face * f) {
  faces.push_back(f);
}

std::vector<Face *> Group::get_faces(void) {
  return faces;
}
