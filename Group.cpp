#include "Group.h"

Group::Group(std::string n) {
  name = n;
}

void Group::push_face(int f) {
  faces.push_back(f);
}

std::vector<int> Group::get_faces(void) {
  return faces;
}
